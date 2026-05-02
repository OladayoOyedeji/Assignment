#use "lexer.mml.ml";;

let symmtable = Hashtbl.create 10;;

let rec loop tokens =
  let eval =
    match tokens with
      [] -> ()
    | (Id_tok (key))::Equ_tok::xs -> let _ = Hashtbl.add symmtable key (infix_evaluate xs symmtable) in
      ()
    | (Id_tok (key))::[] -> let _ = print_token (Hashtbl.find symmtable key) in
      let _ = print_string "\n" in
      ()
    | xs -> let _ = print_token (infix_evaluate tokens symmtable) in
      let _ = print_string "\n" in
      ()
  in
  
  let _ = print_string ">> " in
  let s = read_line () in
  let token_list = tokenize s in
  (* let _ = print_tokens token_list in *)
  
  let _ = eval in
  loop token_list
;;

let x = (Lexing.from_string "\n123\n 234\n  345\n   456\n        567 \n678");;
print_tokens (lexer x);;
