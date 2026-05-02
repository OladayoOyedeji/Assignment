#use "lexer.mml.ml";;

let symmtable = Hashtbl.create 10;;

let rec loop tokens =
  let eval =
    match tokens with
      [] -> raise Error
    | (Indent_tok ind)::tokens -> 
      if ind > 0 then
        print_string "IndentationError: unexpected indent\n"
      else
        (match tokens with
           [] -> ()
         | (Id_tok (key))::Equ_tok::xs ->
           let _ = Hashtbl.add symmtable key (infix_evaluate xs symmtable) in
           ()
         | (Id_tok (key))::[] -> let _ = print_token (Hashtbl.find symmtable key) in
           let _ = print_string "\n" in
           ()
         | xs -> let _ = print_token (infix_evaluate tokens symmtable) in
           let _ = print_string "\n" in
           ())
    | _ -> raise Error
  in

  let _ = print_string ">> " in
  let s = read_line () in
  let s = "\n" ^ s in
  let token_list = tokenize s in
  (* let _ = print_tokens token_list in *)
  
  let _ = eval in
  loop token_list
;;

print_string ">> ";;
let s = read_line ();;
let s = "\n" ^ s;;
let tokens = tokenize s;;
(* print_tokens tokens;; *)
loop tokens;;
