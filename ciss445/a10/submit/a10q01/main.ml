#use "lexer.mml.ml";;
#use "parser.ml";;

let s = read_line ();;
let token_list = tokenize s;;
print_tokens (token_list);;
print_string ("\n");;

let e = expr token_list;;

let rec eval_expr expr = match expr with
    Plus_Expr (t, e) -> (eval_term t) + (eval_expr e)
  | Minus_Expr (t, e) -> (eval_term t) - (eval_expr e)
  | Term_Expr t -> eval_term t
and eval_term term = match term with
    Mul_Term (f, t) -> (eval_factor f) * (eval_term t)
  | Div_Term (f, t) -> (eval_factor f) / (eval_term t)
  | Factor_Term f -> eval_factor f
and eval_factor factor = match factor with
    Id_Factor i -> i
  | Paren_Expr_Factor e -> eval_expr e
;;

let exp, _ = e;;
print_int (eval_expr exp);;
print_string "\n";;

(* let ans = infix_evaluate token_list;; *)
(* print_token(ans);; *)
(* print_string ("\n");; *)
