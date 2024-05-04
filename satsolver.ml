open Base_satsolver;;
let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  Base_satsolver.test_parse();
  print_string "tous les tests ont réussi\n"
;;

let main () =
  test ();
  print_int (Array.length Sys.argv); print_string "\n\n";
  print_string Sys.argv.(0); print_string "\n\n";
  print_string Sys.argv.(1); print_string "\n\n";
;;

let _ = main()