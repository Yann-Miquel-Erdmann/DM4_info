open Valuation;;

let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  Base_satsolver.test_parse();
  Valuation.test_interpret();
  Valuation.test_add_one();
  Valuation.test_valuation_next();
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
    | x::q1, y::q2 -> if x<y then union_aux q1 l2 (x::l3) else union_aux l1 q2 (y::l3)
    | [], x::q | x::q, [] -> union_aux q [] (x::l3)
    | [], [] -> List.rev l3
  in union_aux l1 l2 []
;;

let rec in_list (v: 'a) (l:'a list) =
  match l with
  | [] -> false
  | x::q -> if x == v then true else in_list v q
;;

let calculate_var (f:formule) : formule list =
  let rec calc_var_aux (f:formule) (l:formule list) : formule list =
    match f with
	| Or (g, d) | And (g, d) -> calc_var_aux d (calc_var_aux g l)
	| Not e -> calc_var_aux e l
	| Top | Bot -> l
  | Var x -> if not (in_list (Var x) l) then (Var x)::l else l
  
  in calc_var_aux f []
;;

let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  assert (calculate_var (parse "T | (T & ~F)") == []);
  Base_satsolver.test_parse();
  print_string "tous les tests ont réussi\n"
;;

let main () =
  if Array.length Sys.argv = 1 then failwith "Aucun argument" 
  else
    print_int (Array.length Sys.argv); print_string "\n\n";
    print_string Sys.argv.(0); print_string "\n\n";
    if Sys.argv.(1)="test" then 
      test()
    else 
      print_string (read_file(Sys.argv.(1))); print_string "\n\n";
;;

let _ = main()