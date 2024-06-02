open Base_satsolver;;
open Valuation;;
open Satsolver;;
open Variable_priority;;


let simpl_time = ref 0.;;
(* simplifie au maximum la formule f et renvoie la formule simplifiée
   compte le temps de simplification et l'ajoute à la variable simpl_time *)
let simpl_full (f:formule) : formule =
  let rec simpl_step (f:formule) : formule * bool =
    match f with
    | And (f2, Bot) | And (Bot, f2) -> Bot, true
    | Or (Top, f2) | Or (f2, Top) -> Top, true
    | Not Top -> Bot, true
    | Not Bot -> Top, true
    | And (Top, f2) | And (f2, Top) | Or (Bot, f2) | Or (f2, Bot) -> simpl_step f2
    | Not Not f2 -> simpl_step f2
    | And (f1, f2) ->
      begin 
        let f1, b1 = simpl_step f1 in
        let f2, b2 = simpl_step f2 in
        if b1 || b2 then
          simpl_step (And(f1, f2))
        else
          And(f1, f2), false
      end
    | Or (f1, f2) ->
      begin 
        let f1, b1 = simpl_step f1 in
        let f2, b2 = simpl_step f2 in
        if b1 || b2 then
          simpl_step (Or(f1, f2))
        else
          Or(f1, f2), false
      end
    | Not f1 ->
      begin
        let f1, b = simpl_step f1 in
        if b then
          simpl_step (Not f1)
        else 
          Not f1, b
      end
    | Top -> Top, true
    | Bot -> Bot, true
    | Var x -> f, false
    in 
  let time0 = Sys.time() in 
  let a, _ = simpl_step f in
  let end0 = Sys.time () in
  simpl_time := !simpl_time +. end0 -. time0;
  a
;;

(* affiche les variables de la valuation qui sont a true *)
let rec print_val (v:valuation) : unit =
  match v with
  | [] -> ();
  | (s, true)::q -> print_string s; print_string " <- 1"; print_newline(); print_val q
  | _::q -> print_val q
;;

(* remplace dans la formule f toutes les occurences de la varible var par la formule g *)
let rec subst (f:formule) (var:string) (g:formule) : formule =
  match f with
  | Var name -> if name = var then g else f
	| Top | Bot -> f
	| And (f1, f2) -> And (subst f1 var g, subst f2 var g)
	| Or (f1, f2) -> Or (subst f1 var g, subst f2 var g)
	| Not f1 -> Not (subst f1 var g)
;;

(* variables utilisées pour la barre de chargement *)
let subst_time = ref 0.;;
let total = ref 0.;;
let progress_string = ref "" ;;
let count = ref 0;;

(* affiche une barre de chargement pour voir où en est le programme *)
let progress_bar () : unit =
  progress_string := "";
  for i = 0 to 40 do if (float_of_int i)*.0.025 <= !total then progress_string := !progress_string^"#" else progress_string := !progress_string^"." done;
  Printf.printf "%c[%s] %d %f%%" '\r' !progress_string !count (!total*.100.)
;;

(* algorithme de quine, détermine une valuation pour la formule f et détermine si elle est satisfiable ou non *)
let quine (f:formule) : sat_result =
  let v = flatten (generate_prority f) in

  let rec quine_aux (f: formule) (l: string list) (v: valuation) (value: float) (inc:float): sat_result =
    progress_bar();
    count := !count + 1;
    match l with
    | [] -> if simpl_full f = Top then begin total := 1.; progress_bar(); print_newline(); Some v end else None
    | x::q -> 
      match simpl_full f with
      | Top -> total := 1.; progress_bar(); print_newline(); Some v
      | Bot ->None
      | f2 -> 
        begin
          match quine_aux (subst f2 x Top) q ((x, true)::v) (value-.inc) (inc/.2.) with
          | None -> total := value; quine_aux (subst f2 x Bot) q ((x, false)::v) (value+.inc) (inc/.2.)
          | Some v -> Some v
        end
  in progress_bar(); quine_aux f v [] 0.5 0.25
;;


