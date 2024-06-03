open Satsolver
open Base_satsolver
open Algo_naif
open Algo_quine
open Valuation

(* lance les tests *)
let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  assert (calculate_var (Base_satsolver.parse "T | (T & ~F)") == []);
  Base_satsolver.test_parse();
  Base_satsolver.test_from_file();
  Valuation.test_interpret();
  Valuation.test_add_one();
  Valuation.test_valuation_next();
  Valuation.test_valuation_init();
  Algo_naif.test_satsolver_naif();

  print_string "tous les tests ont réussi\n"
;;

let main () =
  if Array.length Sys.argv = 1 then failwith "Aucun argument" 
  else
    if Sys.argv.(1)="test" then 
      test()
    else
      if Sys.argv.(1)= "naif" then
        (* cherche la valuation sur l'algoruthme naif *)
        print_valuation (Algo_naif.satsolver_naif (Base_satsolver.from_file Sys.argv.(2)))
      else begin
        (* cherche la valuation sur l'algorithme de quine *)
        print_string "fichier: "; print_string Sys.argv.(1);print_newline(); print_newline();
        let formule = from_file Sys.argv.(1) in
        print_string "fait\n"; print_newline ();
        print_string "test des valuations..."; print_newline();
        let time0 = Sys.time() in
        let v = quine formule in 
        print_newline();
        print_valuation v;
        let end0 = Sys.time() in
        print_newline ();
        print_string "Solution trouvée en "; print_float (end0-.time0); print_string " secondes"; print_newline();
        print_string "Temps de simplification: "; print_float !simpl_time; print_string " secondes"; print_newline();
      end
;; 

let _ = main()
