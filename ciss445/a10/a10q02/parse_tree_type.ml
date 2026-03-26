(* file: parse_tree_type.ml *)
type assign = Not_Assign of expr
            | Assign of (string * expr)
and
  expr = Term_Expr of term
       | Plus_Expr of (term * expr)
       | Minus_Expr of (term * expr)
and
  term = Factor_Term of factor
       | Mul_Term of (factor * term)
       | Div_Term of (factor * term)
and
  factor = Int_Factor of int
         | Variable of string
         | Paren_Expr_Factor of expr
;;

