open Satsolver
open Base_satsolver
open Valuation

(* algorithme naif qui teste toutes les valuations jusqu'a trouver la solution *)
let satsolver_naif (f:formule): sat_result = 
	let rec satsolver_naif_inner (f1:formule) (v:valuation option): sat_result = 
		match v with
		| None -> None
		| Some v1 -> if interpret f1 v1 then Some v1 else satsolver_naif_inner f1 (valuation_next v1)
	
	in satsolver_naif_inner f (Some(valuation_init (calculate_var f) ))
;;

(* tests sur des petites formules *)
let test_satsolver_naif () = 
	assert(satsolver_naif (And (Var "a" ,Var "a")) == Some [("a", true)]);
	assert(satsolver_naif (Top) = Some []);
	assert(satsolver_naif (Bot) = None);
;;