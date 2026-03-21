#use "lexer.mml.ml";;

let s = read_line ();;
let token_list = tokenize s;;
print_tokens (token_list);;
print_string ("\n");;

let ans = infix_evaluate token_list;;
print_token(ans);;
print_string ("\n");;
