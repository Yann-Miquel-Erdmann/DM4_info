open Satsolver
open Base_satsolver
open Algo_naif
open Algo_quine
open Valuation

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
        print_valuation (Algo_naif.satsolver_naif (Base_satsolver.from_file Sys.argv.(2)))
      else
      print_string "file: "; print_string Sys.argv.(1);print_newline(); print_newline();
      let formule = from_file Sys.argv.(1) in
      print_string "done\n"; print_newline ();
      print_string "testing valuations..."; print_newline();
      let time0 = Sys.time() in
      print_valuation (quine formule);
      let end0 = Sys.time() in
      print_newline ();
      print_string "Solution found in "; print_float (end0-.time0); print_string " seconds"; print_newline();
      print_string "Simplification time: "; print_float !simpl_time; print_string " seconds"; print_newline();
;; 

let _ = main()
