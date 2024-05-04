open Base_satsolver;;

let test () =
  assert ((Array.length Sys.argv) > 1);
  assert (1 == 1);
  Base_satsolver.test_parse();
  print_string "tous les tests ont réussi\n"
;;

(* Renvoie le contenu du fichier fn sous forme de string. 
   Le fichier ne doit contenir qu'une seule ligne *)
let read_file (fn: string) : string =
  let ic = open_in fn in
  let res =input_line ic in
  close_in ic; res
;;



let main () =
  test ();
  if Array.length Sys.argv = 1 then failwith "Aucun argument" 
  else
    print_int (Array.length Sys.argv); print_string "\n\n";
    print_string Sys.argv.(0); print_string "\n\n";
    if Sys.argv.(1)="test" then test() 
    else 
      print_string (read_file(Sys.argv.(1))); print_string "\n\n";
;;

let _ = main()