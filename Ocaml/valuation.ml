open Base_satsolver

(* définition du type valuation qui va permetter de stocker la valeur de chaque variables à la fin de l'éxécution du programme *)
type valuation = (string*bool) list
type sat_result = valuation option

(* applique la valuation c à la formule f et renvoie le résultat *)
let rec interpret (f: formule) (v: valuation): bool = 
	match f with
	| Var var -> List.assoc var v;
	| Top -> true
	| Bot -> false
	| And (f1,f2) -> (interpret f1 v) && (interpret f2 v)
	| Or (f1,f2) -> (interpret f1 v) || (interpret f2 v)
	| Not f1 -> not (interpret f1 v)
;;

(* test de l'interprétation *)
let test_interpret () = 
	assert (interpret Top [] == true);
	assert (interpret Bot [] == false);
	assert (interpret (Var ("v")) [("v", true)] == true);
	assert (interpret (Var ("v")) [("v", false)] == false);
	assert (interpret (Not (Var ("v"))) [("v", false)] == true);
	assert (interpret (And (Var ("v"), Top)) [("v", false)] == false);
	assert (interpret (And (Var ("v"), Top)) [("v", true)] == true);
	assert (interpret (Or (Var ("v"), Bot)) [("v", false)] == false);
	assert (interpret (Or (Var ("v"), Top)) [("v", false)] == true);
	assert (interpret (And (Var ("v"), Top)) [("v", true)] == true)
;;

(* renvoie la liste booléen suivante:
	 i.e. si on considère la liste comme un nombre binaire, renvoie le nombre binaire + 1*)
let rec add_one (l: bool list): bool list = 
	match l with	
	| [] -> []
	| true::q -> false::(add_one q)
	| false::q -> true::q
;;

(* tests *)
let test_add_one () = 
  assert(add_one [false; false] = [true; false]);
  assert(add_one [true; false] = [false; true]);
  assert(add_one [false; true] = [true; true]);
  assert(add_one [true; true] = [false; false])
;;

(* renvoie la valuation suivante de la valuation v donnée *)
let valuation_next (v: valuation) : valuation option =
	if List.for_all (fun (x,y)-> y) v then
		(* si toutes les varibales sotn a true, toutes les valuations ont été testées, on renvoie None *)
		None
	else
		(* sinon remplace la valuation par la suivante *)
		let rec new_val (v:valuation) (l:bool list): valuation =
			match (v,l) with
			| ([],[]) -> []
			| ((x,y1)::v2, y2::l2) -> (x,y2)::(new_val v2 l2) 
			| _ ->  failwith "Le nombre de booléens n'est pas égal au nombre de variables"
		in Some (new_val v (add_one (List.map (fun (x,y)->y) v)))
;;	

(* fonction de test de la valuation suivante*)
let test_valuation_next () =
  assert(valuation_next [("a", false); ("b", false)] = (Some [("a", true); ("b", false)]));
  assert(valuation_next [("a", true); ("b", false)] = Some [("a", false); ("b", true)]);
  assert(valuation_next [("a", false); ("b", true)] = Some [("a", true); ("b", true)]);
  assert(valuation_next [("a", true); ("b", true)] = None)
;;

(* créée une valuation avec les noms de variable de la liste l que des booléen à false *)
let valuation_init (l: string list) : valuation = 
	List.map (fun x -> (x,false)) l
;;

(* fonction de test *)
let test_valuation_init () = 
	assert(valuation_init ["a"; "b"] = [("a", false); ("b", false)]);
	assert(valuation_init ["a"; "b"; "c"] = [("a", false); ("b", false); ("c", false)]);
	assert(valuation_init ["a"] = [("a", false)])
;;

(* affiche les variables de la valuation v qui sont a true *)
let rec print_valuation (v:valuation option): unit = 
	match v with
	| None -> print_newline(); print_string "La formule n'a pas de solutions\n"
	| Some [] -> ()
	| Some ((name,true)::q) -> print_string (name); print_string " = true\n"; print_valuation (Some q) 
	| Some (_::q) -> print_valuation (Some q)
;;

(* affiche l'entièreté des valeurs de la valuation v *)
let rec print_valuation2 (v:valuation option): unit = 
	match v with
	| None -> print_newline(); print_string "La formule n'a pas de solutions\n"
	| Some [] -> ()
	| Some ((name,true)::q) -> print_string (name); print_string " = true\n"; print_valuation (Some q) 
	| Some ((name,false)::q) -> print_string (name); print_string " = false\n"; print_valuation (Some q) 
;;
