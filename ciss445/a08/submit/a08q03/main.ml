#use "lexer.mml.ml";;

let s = read_line ();;
print_tokens (tokenize s);;
print_string ("\n");;
