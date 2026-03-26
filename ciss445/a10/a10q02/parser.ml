#use "parse_tree_type.ml";;

let rec assign toks =
  match toks with
  Id_tok name::Equ_tok::toks2 ->
  (
    let (e, toks3) = expr toks2 in
    (Assign(name, e), toks3)
  )
  
  | xs -> let exp, tok = expr xs in
    (Not_Assign exp, tok)
and
  expr toks =
  let (t, toks1) = term toks in
  match toks1 with
    Plus_tok::toks2 ->
    (
      let (e, toks3) = expr toks2 in
      (Plus_Expr(t, e), toks3)
    )
  | Minus_tok::toks2 ->
    (
      let (e, toks3) = expr toks2 in
      (Minus_Expr(t, e), toks3)
    )
  | _ -> (Term_Expr t, toks1)
and
  term toks =
  let (f, toks1) = factor toks in
  match toks1 with
    Mul_tok::toks2 ->
    (
      let (t, toks3) = term toks2 in
      (Mul_Term(f, t), toks3)
    )
  | Div_tok::toks2 ->
    (
      let (t, toks3) = term toks2 in
      (Div_Term(f, t), toks3)
    )
  | _ -> (Factor_Term f, toks1)
and
  factor toks = match toks with
    Int_tok name::toks -> (Int_Factor name, toks)
  | Id_tok name::toks -> (Variable name, toks)
  | Lparen_tok::toks1 ->
    (
      let (e, toks2) = expr toks1 in
      match toks2 with
        Rparen_tok::toks3 -> (Paren_Expr_Factor(e), toks3)
      | _ -> raise (Failure "Missing Rparen")
    )
  | _ -> raise (Failure "Missing Id_tok or Lparen")
;;
