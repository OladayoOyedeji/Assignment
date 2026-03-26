#use "lexer.mml.ml";;
#use "parser.ml";;

let symmtable = Hashtbl.create 10;;

print_string ">> ";;
let s = read_line ();;

let run_tree parse_tree symmtable = 
  let rec eval_assign assign = match assign with
      Not_Assign expr -> let ret = eval_expr expr in
      let _ = print_int ret in
      print_string "\n"
    | Assign (v, e) -> Hashtbl.add symmtable v (eval_expr e)
  and eval_expr expr = match expr with
      Plus_Expr (t, e) -> (eval_term t) + (eval_expr e)
    | Minus_Expr (t, e) -> (eval_term t) - (eval_expr e)
    | Term_Expr t -> eval_term t
  and eval_term term = match term with
      Mul_Term (f, t) -> (eval_factor f) * (eval_term t)
    | Div_Term (f, t) -> (eval_factor f) / (eval_term t)
    | Factor_Term f -> eval_factor f
  and eval_factor factor = match factor with
      Int_Factor i -> i
    | Variable name -> Hashtbl.find symmtable name
    | Paren_Expr_Factor e -> eval_expr e
  in
  let _ = eval_assign parse_tree in
  ()
;;

let rec loop s =
  let token_list = tokenize s in
  let e, t = assign token_list in
  let _ = 
    (match t with
       [] -> run_tree e symmtable
     | xs -> print_string "Error")
  in
  
  let _ = print_string ">> " in
  let s = read_line () in
  loop s
;;

loop s;;

(* let exp, _ = e;; *)
(* print_int (eval_expr exp);; *)
(* print_string "\n";; *)

(* let ans = infix_evaluate token_list;; *)
(* print_token(ans);; *)
(* print_string ("\n");; *)
