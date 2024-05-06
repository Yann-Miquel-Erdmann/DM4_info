open Base_satsolver;;


type sat_result = valuation option

let rec simpl_step (f:formule) : formule * bool =
  match f with
  | And (Top, f2) | And (f2, Top) | Or (Bot, f2) | Or (f2, Bot) -> f2,true
  | And (f2, Bot) | And (Bot, f2) -> Bot, true
  | Or (Top, f2) | Or (f2, Top) -> Top, true
  | Not Not f2 -> f2,true
  | Not Top -> Bot, true
  | Not Bot -> Top, true
  | And (f1, f2) ->
    begin 
      let f1, b1 = simpl_step f1 in
      let f2, b2 = simpl_step f2 in
      And(f1, f2), b1||b2
    end
  | Or (f1, f2) ->
    begin 
      let f1, b1 = simpl_step f1 in
      let f2, b2 = simpl_step f2 in
      Or(f1, f2), b1||b2
    end
  | Not f1 ->
    begin
      let f1, b = simpl_step f1 in
      Not f1, b
    end
  | _ -> f, false
;;

let rec simpl_step_2 (f:formule) : formule * bool =
  match f with
  | And (Top, f2) | And (f2, Top) | Or (Bot, f2) | Or (f2, Bot) -> f2,true
  | And (f2, Bot) | And (Bot, f2) -> Bot, true
  | Or (Top, f2) | Or (f2, Top) -> Top, true
  | Not Not f2 -> f2,true
  | Not Top -> Bot, true
  | Not Bot -> Top, true
  | And (f1, f2) ->
    begin 
      let f1, b1 = simpl_step_2 f1 in
      let f2, b2 = simpl_step_2 f2 in
      if b1 || b2 then
        simpl_step_2 (And(f1, f2))
      else
        And(f1, f2), b1||b2
    end
  | Or (f1, f2) ->
    begin 
      let f1, b1 = simpl_step_2 f1 in
      let f2, b2 = simpl_step_2 f2 in
      if b1|| b2 then
        simpl_step_2 (Or(f1, f2))
      else 
        Or(f1, f2), false
    end
  | Not f1 ->
    begin
      let f1, b = simpl_step_2 f1 in
      if b then
        simpl_step_2 (Not f1)
      else 
        Not f1, b
    end
  | _ -> f, false
;;

let rec subst (f:formule) (var:string) (g:formule) : formule=
  match f with
  | Var name -> if name = var then g else f
	| Top | Bot -> f
	| And (f1, f2) -> And (subst f1 var g, subst f2 var g)
	| Or (f1, f2) -> Or (subst f1 var g, subst f2 var g)
	| Not f1 -> Not (subst f1 var g)
;;


let rec simpl_full (f:formule) : formule =
  let a, b = simpl_step f in
  if b then simpl_full a
  else f
;;

let rec quine_aux (f: formule)(l: string list )(v: valuation) : sat_result =
  match l with
  | [] -> if simpl_full(f) = Top then Some v else None
  | x::q -> if quine_aux(simpl_full(subst(f,x,Top)),q) =  then

let quine (f: formule) : sat_result =

let rec print_true (v: valuation): unit =
  match v with
  | [] -> ()
  | (x,true)::q -> print_string(x);print_string "\n";print_true(q)
  | (x,false)::q -> print_true(q)
