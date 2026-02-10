(* Author: Oladayo Oyedeji
   File: main.ml *)

let rec pow x n =
  if n = 0 then
    1
  else
    x * pow x (n-1);;

print_int (pow 2 0);;
print_string "\n";;
print_int (pow 0 5);;
print_string "\n";;
print_int (pow 0 1);;
print_string "\n";;
print_int (pow 2 2);;
print_string "\n";;
print_int (pow (-3) 3);;
print_string "\n";;
