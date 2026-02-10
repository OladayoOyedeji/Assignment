(* Author: Oladayo Oyedeji
   File: main.ml *)

let rec pow x n =
  if n = 0 then
    1
  else if n mod 2 = 0 then
    pow x (n/2) * pow x (n/2)
  else
    x * pow x ((n-1)/2) * pow x ((n-1)/2);;

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
