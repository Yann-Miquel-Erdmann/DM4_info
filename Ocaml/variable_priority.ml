open Base_satsolver

(* insère l'élément elem dans la liste à l'index index de la liste l et l'ajoute au contenu de out qui est renvoyé *)
let rec insert_list (elem: 'a) (l:'a list list) (index:int) (out: 'a list list): 'a list list=
  match l, (List.length l - index -1) with
  | [], x -> if x > 0 then failwith "index invalide" else List.rev out
  | l2::q, 0 -> insert_list elem q index ((elem::l2)::out)
  | l2::q, _ -> insert_list elem q index (l2::out)
;;

(* teste si l'élément elem est dans la liste l *)
let rec in_list (elem: 'a) (l: 'a list) : bool =
  match l with
  | [] -> false
  | x::q -> if x = elem then true else in_list elem q
;;

(* génère la liste de priorité de la formule f
   i.e. plus la variable est "profonde" dans la formule plus elle est loin dans la liste
   c'est-à-dire plus elle on rencontre d'inversions
   de And et de Or, plus elle est profonde
   chaque profondeur possède une sous liste *)
let generate_prority (f: formule) : string list list =
  let rec generate_prority_aux (f: formule list) (encountered: string list) (depht: int) (list_type: bool) (to_visit : formule list) (out:string list list): (string list list* string list*formule list) =
    match f, list_type with
    | [], _ -> 
      begin
      match to_visit with
      | [] -> List.map (fun l -> List.rev l) (List.rev out), encountered, to_visit
      | _ -> generate_prority_aux to_visit encountered (depht+1) (not list_type) [] ([]::out)
      end
    | (And (f1, f2))::q, true | (Or (f1, f2))::q, false -> generate_prority_aux (f1::f2::q) encountered depht list_type to_visit out
    | (And (f1, f2))::q, false | (Or (f1, f2))::q, true -> generate_prority_aux q encountered depht list_type (f1::f2::to_visit) out (*let out0 = if List.length out-1 <= depht then ([]::out) else out in let out2, encountered2 = generate_prority_aux f1 encountered (depht+1) (not list_type) out0 in generate_prority_aux f2 encountered2 (depht+1) (not list_type) out2*)
    | (Var x)::q, _ -> let out1, encountered1 = if in_list x encountered then out, encountered else (insert_list x out depht []), (x::encountered) in generate_prority_aux q encountered1 depht list_type to_visit out1
    | (Not f1)::q, _ -> generate_prority_aux (f1::q) encountered depht list_type to_visit out
    | (Top)::q, _ | (Bot)::q, _ -> generate_prority_aux q encountered depht list_type to_visit out
  in let l, _, _ = generate_prority_aux [f] [] 0 true [] [[]] in l
;;

(* transforme la liste l pour convertir les sous-listes en une unique liste *)
let flatten (l: 'a list list) : ('a list) =
  let rec flatten_aux (l: 'a list list) (curr_list: 'a list) (out:'a list) : ('a list) =
    match curr_list, l with
    | [], [] -> List.rev out
    | [], x::q -> flatten_aux q x out
    | x::q, _ -> flatten_aux l q (x::out)
  in flatten_aux l [] []
;;