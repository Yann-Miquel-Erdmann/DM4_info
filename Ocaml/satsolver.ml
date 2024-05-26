open Valuation;;
open Base_satsolver;;

let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  Base_satsolver.test_parse();
  Valuation.test_interpret();
  Valuation.test_add_one();
  Valuation.test_valuation_next();
  Base_satsolver.test_from_file();
  print_string "tous les tests ont réussi\n"
;;

(* Renvoie le contenu du fichier fn sous forme de string. 
   Le fichier ne doit contenir qu'une seule ligne *)
let read_file (fn: string) : string =
  let ic = open_in fn in
  let res =input_line ic in
  close_in ic; res
;;

let rec liste_est_triee_sans_doublon (l:'a list) : bool =
  match l with
  | x::y::q -> if x < y then liste_est_triee_sans_doublon (y::q) else false
  | _ -> true
;;

let union (l1:'a list) (l2: 'a list): 'a list =
  let rec union_aux (l1:'a list) (l2: 'a list) (l3:'a list) : 'a list =
    match l1, l2 with
    | x::q1, y::q2 -> if x<y then union_aux q1 l2 (x::l3) else if x > y then union_aux l1 q2 (y::l3) else union_aux q1 q2 (y::l3)
    | [], x::q | x::q, [] -> union_aux q [] (x::l3)
    | [], [] -> List.rev l3
  in union_aux l1 l2 []
;;

let rec in_list (v: 'a) (l:'a list) : bool =
  match l with
  | [] -> false
  | x::q -> if x = v then true else in_list v q
;;

let calculate_var (f:formule) : string list =
  let rec calc_var_aux (f:formule) (l:string list) : string list =
    match f with
    | Or (g, d) | And (g, d) -> calc_var_aux d (calc_var_aux g l)
    | Not e -> calc_var_aux e l
    | Top | Bot -> l
    | Var x -> if not (in_list x l) then x::l else l
  in calc_var_aux f []
;;




