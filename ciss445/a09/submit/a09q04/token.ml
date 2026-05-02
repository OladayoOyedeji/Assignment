(* File: token.ml *)


exception Error;;

let count_spaces s =
  String.fold_left
    (fun count char ->
      if char = ' ' then count + 1 else count)
    0 (* Initial value of the counter *)
    s

let int_pow x n =
  let rec f squares n p =
    if n = 0 then p
    else if n mod 2 = 1 then
      f (squares * squares) (n/2) (p * squares)
    else
      f (squares * squares) (n/2) p
  in
  f x n 1
;;

type token = Int_tok of int
           | Float_tok of float
           | Bool_tok of bool
           | String_tok of string
           | Id_tok of string
           | Indent_tok of int
           | Plus_tok
           | Minus_tok
           | Mul_tok
           | Div_tok
           | Exp_tok
           | Is_Equ_tok
           | Is_Neq_tok
           | Equ_tok
           | If_tok
           | Else_tok
           | Lcomment_tok
           | Rcomment_tok
           | Lparen_tok
           | Rparen_tok
;;

exception IgnoreCase;;

(* Write a print_token function. For instance print_token (Int_tok 5)
   prints
   Int_tok 5
   in the console window.
*)
let print_token t = match t with
    Int_tok (x) -> let _ = Printf.printf "%d" x in
    ()
  | Float_tok (x) -> let _ = Printf.printf "%f" x in
    ()
  | Bool_tok (x) -> let _ = Printf.printf "%b" x in
    ()
  | String_tok x -> let _ = Printf.printf "String_tok %s" x in
    ()
  | Id_tok x -> let _ = Printf.printf "Id tok %s" x in
    ()
  | Indent_tok x -> let _ = Printf.printf "Indent %d" x in
    ()
  | Plus_tok -> print_string "Plus_tok +"
  | Minus_tok -> print_string "Minus_tok -"
  | Mul_tok -> print_string "Mul_tok *"
  | Div_tok -> print_string "Div_tok /"
  | Exp_tok -> print_string "Exp_tok **"
  | Is_Equ_tok -> print_string "Is_Equ_tok =="
  | Is_Neq_tok -> print_string "Is_Neq_tok !="
  | Equ_tok -> print_string "Eq_tok ="
  | If_tok -> print_string "If_tok if"
  | Else_tok -> print_string "Else_tok else"
  | Lcomment_tok -> print_string "comment (*"
  | Rcomment_tok -> print_string "comment *)"
  | Lparen_tok -> print_string "LParen_tok ("
  | Rparen_tok -> print_string "RParen_tok )"
;;

(* Write a print_tokens function. For instance print_tokens [Int_tok 5;
   Float 3.1; Id_tok "num_heads"; Plus_tok] prints
   [Int_tok 5, Float 3.1, Id_tok "num_heads", Plus_tok]
   on the console window.
*)
let print_tokens tokens =
  let rec f tokens delim = match tokens with
      [] -> "]"
    | x::xs -> let _ = print_string delim in
      let _ = print_token x in
      f xs ", "
  in
  f tokens "["
;;

let evaluate token = let x,op,y = token in
      match (x, y) with
        Float_tok (x), Float_tok (y) ->  (match op with
            Plus_tok -> Float_tok(x +. y)
          | Minus_tok -> Float_tok(x -. y)
          | Mul_tok -> Float_tok(x *. y)
          | Div_tok -> Float_tok(x /. y)
          | Exp_tok -> Float_tok(x ** y)
          | _ -> Bool_tok (false))

      | Float_tok (x), Int_tok (y) ->  (match op with
            Plus_tok -> Float_tok(x +. (float_of_int y))
          | Minus_tok -> Float_tok(x -. (float_of_int y))
          | Mul_tok -> Float_tok(x *. (float_of_int y))
          | Div_tok -> Float_tok(x /. (float_of_int y))
          | Exp_tok -> Float_tok(x ** (float_of_int y))
          | _ -> Bool_tok (false))

      | Int_tok (x), Float_tok (y) ->  (match op with
            Plus_tok -> Float_tok((float_of_int x) +. y)
          | Minus_tok -> Float_tok((float_of_int x) -. y)
          | Mul_tok -> Float_tok((float_of_int x) *. y)
          | Div_tok -> Float_tok((float_of_int x) /. y)
          | Exp_tok -> Float_tok((float_of_int x) ** y)
          | _ -> Bool_tok (false))

      | Int_tok (x), Int_tok (y) -> (match op with
            Plus_tok -> Int_tok (x + y)
          | Minus_tok -> Int_tok (x - y)
          | Mul_tok -> Int_tok (x * y)
          | Div_tok -> Int_tok (x / y)
          | Exp_tok -> Int_tok(int_pow x y)
          | _ -> Bool_tok (false))
      | _, _ -> Bool_tok (false)
  
;;

let prec tok = match tok with
    Plus_tok | Minus_tok -> 1
  | Div_tok | Mul_tok -> 2
  | Exp_tok -> 3
  | _ -> raise Error
;;

let rec evaluate_tokens op_stack t_stack op_prec = match op_stack with
  [] -> (op_stack, t_stack)
  | x::xs -> 
    if op_prec <= (prec x) then
      (match t_stack with 
         [] -> raise Error
       | y::z::ys -> evaluate_tokens xs ((evaluate (z, x, y))::ys) op_prec
       | _ -> raise Error)
    else
      (op_stack, t_stack)
  (* match op_stack with *)
  (*   [] -> (op_stack, t_stack) *)
  (* | x::xs -> (match x with *)
  (*     Mul_tok | Div_tok -> (match t_stack with *)
  (*         [] -> raise Error *)
  (*       | y::z::ys -> evaluate_tokens xs ((evaluate (y, x, z))::ys) *)
  (*       | _ -> raise Error) *)
  (*   | Plus_tok | Minus_tok -> (op_stack, t_stack) *)
  (*   | _ -> raise Error) *)
  
;;

let infix_evaluate tokens symmtable =
  
  let rec g op_stack t_stack = match op_stack with
      [] -> (match t_stack with
          x::[] -> x
        | _ -> raise Error)
    | y::ys -> (match t_stack with
          x::z::xs -> g ys ((evaluate (z, y, x))::xs)
        | _ -> raise Error)
  in
  let rec f tokens op_stack t_stack = match tokens with
      [] -> (op_stack, t_stack, tokens)
    | x::xs -> (match x with
          Int_tok (y) -> f xs op_stack (x::t_stack)
        | Float_tok (y) -> f xs op_stack (x::t_stack)
        | Id_tok (y) -> let x = (Hashtbl.find symmtable y) in
          f xs op_stack (x::t_stack)
        | Mul_tok | Div_tok | Plus_tok | Minus_tok | Exp_tok -> (match op_stack with
            [] -> f xs (x::op_stack) t_stack
          | top::stack -> let op_stack, t_stack = evaluate_tokens op_stack t_stack (prec x) in
            f xs (x::op_stack) t_stack)
        | Lparen_tok -> let (y, z, token) = f xs [] [] in
          let res = g y z in
          f token op_stack (res::t_stack)
        | Rparen_tok -> (op_stack, t_stack, xs)
        | _ -> raise Error)
  in
  let op_stack, t_stack, _ = f tokens [] [] in

  g op_stack t_stack
  
;;
