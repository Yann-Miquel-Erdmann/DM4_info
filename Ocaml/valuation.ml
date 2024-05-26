open Base_satsolver

type valuation = (string*bool) list
type sat_result = valuation option

let rec interpret (f: formule) (v: valuation): bool = 
	match f with
	| Var var -> List.assoc var v;
	| Top -> true
	| Bot -> false
	| And (f1,f2) -> (interpret f1 v) && (interpret f2 v)
	| Or (f1,f2) -> (interpret f1 v) || (interpret f2 v)
	| Not f1 -> not (interpret f1 v)
;;

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

let rec add_one (l: bool list): bool list = 
	match l with	
	| [] -> []
	| true::q -> false::(add_one q)
	| false::q -> true::q
;;

let test_add_one () = 
  assert(add_one [false; false] = [true; false]);
  assert(add_one [true; false] = [false; true]);
  assert(add_one [false; true] = [true; true]);
  assert(add_one [true; true] = [false; false])
;;


let valuation_next (v: valuation) : valuation option =
	if List.for_all (fun (x,y)-> y) v then
		None
	else
		let rec new_val (v:valuation) (l:bool list): valuation =
			match (v,l) with
			| ([],[]) -> []
			| ((x,y1)::v2, y2::l2) -> (x,y2)::(new_val v2 l2) 
			| _ ->  failwith "Le nombre de booléens n'est pas égal au nombre de variables"
		in Some (new_val v (add_one (List.map (fun (x,y)->y) v)))
;;	

let test_valuation_next () = 

  assert(valuation_next [("a", false); ("b", false)] = (Some [("a", true); ("b", false)]));
  assert(valuation_next [("a", true); ("b", false)] = Some [("a", false); ("b", true)]);
  assert(valuation_next [("a", false); ("b", true)] = Some [("a", true); ("b", true)]);
  assert(valuation_next [("a", true); ("b", true)] = None)
;;

let valuation_init (l: string list) : valuation = 
	List.map (fun x -> (x,false)) l
;;

let test_valuation_init () = 
	assert(valuation_init ["a"; "b"] = [("a", false); ("b", false)]);
	assert(valuation_init ["a"; "b"; "c"] = [("a", false); ("b", false); ("c", false)]);
	assert(valuation_init ["a"] = [("a", false)])
;;

let rec print_valuation (v:valuation option): unit = 
	match v with
	| None -> print_string "La formule n'a pas de solutions\n"
	| Some [] -> ()
	| Some ((name,true)::q) -> print_string (name); print_string " = true\n"; print_valuation (Some q) 
	| Some (_::q) -> print_valuation (Some q)
;;
