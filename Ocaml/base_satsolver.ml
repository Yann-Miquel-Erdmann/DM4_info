type formule =
| Var of string
| Top
| Bot
| And of formule * formule
| Or of formule * formule
| Not of formule
;;


let implique (f1, f2) = Or(Not f1, f2)
let equivalence (f1, f2) = And(implique (f1, f2), implique (f2, f1))

let non_equivalence (f1, f2) = Not (equivalence (f1, f2);)

(*** PARSER ***)

exception Erreur_syntaxe
exception Fichier_invalide

(* Symboles:
	'T' -> true
	'F' -> false
	'&' -> And
	'|' -> Or
	'~' -> Not
	'>' -> implication
	'=' -> equivalence
	'!' -> non équivalence
 *)

(* Détermine si c correspond à un opérateur binaire logique *)
let is_binop (c: char) : bool = match c with 
	| '&' | '|' | '>' | '=' | '!' -> true
	| _ -> false 
;;

(* Priorité de l'opérateur c. Permet de déterminer
	comment interpréter une formule sans parenthèses.
	Par exemple, "x&y|z" sera interprété comme "(x&y)|z"
	car & est plus prioritaire que | *)
let priority (c: char) : int = match c with
	| '&' -> 5
	| '|' -> 4
	| '!' -> 3
	| '=' -> 2
	| '>' -> 1
	| _ -> raise Erreur_syntaxe (* c n'est pas un opérateur *)
;;

(* indice de l'opérateur le moins prioritaire parmis ceux
   qui ne sont pas entre parenthèses entre s.[i] et s.[j] 
   inclus *)
 let find_op_surface (s: string) (i: int) (j: int) : int =
 	(* 
 	   Renvoie l'indice de l'opérateur le moins prioritaire entre
 	   i et j, sachant que res est l'indice du meilleur opérateur
 	   entre i et k-1.
 	   paren_lvl: niveau d'imbrication actuel des parenthèses *)
 	let rec find_op_paren (k:int) (res:int) (paren_lvl: int) : int  =
 		if k=j+1 then
			res
		else
			if s.[k] = '(' then
				find_op_paren (k+1) res (paren_lvl+1)
			else
				if s.[k] = ')' then
					find_op_paren (k+1) res (paren_lvl-1) 

			(* Le caractère lu est pris si l'on est hors des parenthèses,
				que le caractère est bien un opérateur, et qu'il est moins
				prioritaire que le meilleur résultat jusqu'ici *)
				else
					if (paren_lvl = 0) && (is_binop s.[k]) && (res = -1 || priority s.[k] < priority s.[res]) then 
						find_op_paren (k+1) k (paren_lvl)
					else 
						find_op_paren (k+1) res (paren_lvl)
 	in find_op_paren i (-1) 0;;
;;

(* Renvoie une formule construite à partir de la chaîne s.
   Lève une exception Erreur_syntaxe si la chaîne ne représente pas une formule valide. *)
let parse (s: string) : formule =
	print_string "parse du fichier..."; print_newline ();
	let n = String.length s in
	(* construit une formule à partir de s[i..j] *)
	let rec parse_aux (i: int) (j:int) =
		if (i < 0 || i >= n || j < 0 || j >= n || i > j) then
			raise Erreur_syntaxe
		else if s.[i] = ' ' then
			parse_aux (i+1) j
		else if s.[j] = ' ' then
			parse_aux i (j-1)
		else
			let k = find_op_surface s i j in
				if k = -1 then
					if s.[i] = '~' then
						Not (parse_aux (i+1) j)
					else if s.[i] = '(' then
						begin 
							if (s.[j] != ')') then
								(print_int j; failwith "mauvais parenthésage")
							else
								parse_aux (i+1) (j-1)
						end
					else if (i = j && s.[i] = 'T') then 
						Top
					else if (i = j && s.[i] = 'F') then 
						Bot
					else 
						Var(String.sub s i (j-i+1))
				else match s.[k] with
						| '&' -> And(parse_aux i (k-1), parse_aux (k+1) j)
						| '|' -> Or(parse_aux i (k-1), parse_aux (k+1) j)
						| '=' -> equivalence(parse_aux i (k-1), parse_aux (k+1) j)
						| '>' -> implique(parse_aux i (k-1), parse_aux (k+1) j)
						| '!' -> non_equivalence(parse_aux i (k-1), parse_aux (k+1) j)
						| _ -> raise Erreur_syntaxe
	in parse_aux 0 (n -1)
;;

(* Renvoie une formule construire à partir du contenu du fichier fn.
   Lève une exception Erreur_syntaxe si le contenu du fichier n'est pas une formule valide.
   Lève une exception Sys_error(message_erreur) si le nom du fichier n'est pas valide. *)
let from_file (filename: string) : formule = 
	(* concatène toutes les lignes de f en une seule chaîne *)
	let rec read_lines f = 
		try 
			let next_line = input_line f in
			let s = read_lines f in
			next_line ^ s
		with 
			| End_of_file -> ""
	in
	let f = open_in filename in 
	let s = print_string "lecture du fichier..."; print_newline (); read_lines f in
	print_string "fait\n"; print_newline ();
	parse s
;;

let rec compte_ops (f: formule) : int	=
	match f with
	| Or (g, d) | And (g, d) -> compte_ops g + compte_ops d + 1
	| Not e -> compte_ops e + 1
	| Top | Bot | Var _ -> 0
;;

let print_bool (b:bool) =
	if b then
		begin
			print_string "true";
		end
	else begin print_string "false" end
;;

(* fonctions de tests *)
let test_parse () =
	assert (parse "a|(b&~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
	assert (parse "(a & ~a) = T" = And(Or(Not(And(Var "a",Not(Var "a"))),Top),Or(Not(Top),And(Var "a",Not(Var "a")))));
	print_bool (try (let _ = parse "a = = " in false ) with Erreur_syntaxe -> true);
	assert (compte_ops (parse "x | (y &  ~z)") = 3);
;;

let test_from_file () =
	assert(from_file("Ocaml/tests/test1.txt") = And(Var "a", Top));
	assert(from_file("Ocaml/tests/test2.txt") = And(Or(Var "a",Var "b"),Or(Not(Var "a"),Not(Var "b"))));
	assert(try (let _ = from_file("Ocaml/tests/test3.txt") in false ) with Erreur_syntaxe -> true);
;;