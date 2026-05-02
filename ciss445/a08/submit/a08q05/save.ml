

  let rec prec op_stack t_stack = match op_stack with
      [] -> (match t_stack with
          x::[] -> x
        | _ -> raise Error)
    | y::ys -> (match t_stack with
          x::z::xs -> g ys ((evaluate (x, y, z))::xs)
        | _ -> raise Error)
  in
;;
let rec prec op_stack t_stack = match op_stack with
    [] -> (op_stack, t_stack)
  | x::xs -> (match x with
      Plus_tok | Minus_tok -> (match t_stack with
          [] -> raise Error
        | y::z::ys -> evaluate_tokens xs ((evaluate (y, x, z))::ys)
        | _ -> raise Error)
    | Mul_tok | Div_tok -> (op_stack, t_stack)
    | _ -> raise Error)
  
;;
  
let infix_evaluate tokens =
  
  let rec g op_stack t_stack = match op_stack with
      [] -> (match t_stack with
          x::[] -> x
        | _ -> raise Error)
    | y::ys -> (match t_stack with
          x::z::xs -> g ys ((evaluate (x, y, z))::xs)
        | _ -> raise Error)
  in
  let rec f tokens op_stack t_stack = match tokens with
      [] -> (op_stack, t_stack)
    | x::xs -> (match x with
          Int_tok (y) -> f xs op_stack (x::t_stack)
        | Float_tok (y) -> f xs op_stack (x::t_stack)
        | Plus_tok | Minus_tok -> (match op_stack with
              [] -> f xs (x::op_stack) t_stack
            | top::stack -> (match top with
                  Mul_tok | Div_tok -> f xs (x::op_stack) t_stack
                | Plus_tok | Minus_tok -> 
                  let t = prec op_stack t_stack in
                  f xs (x::[]) (t::t_stack)
                | _ -> raise Error))
        | _ -> raise Error)
  in
  let op_stack, t_stack = f tokens [] [] in

  g op_stack t_stack
;;
