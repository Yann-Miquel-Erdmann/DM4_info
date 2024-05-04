let test () =
  assert (1 = 1);
  print_string "tous les tests ont réussi\n"
;;

let main () =
  test ();
  print_int (Array.length Sys.argv); print_string "\n\n";
  print_string Sys.argv.(0); print_string "\n\n";
  print_string Sys.argv.(1); print_string "\n\n";
;;

let _ = main()