(* file: parse_tree_type.ml *)
type expr = Term_Expr of term
          | Plus_Expr of (term * expr)
          | Minus_Expr of (term * expr)
and
  term = Factor_Term of factor
       | Mul_Term of (factor * term)
       | Div_Term of (factor * term)
and
  factor = Id_Factor of int
         | Paren_Expr_Factor of expr
;;

