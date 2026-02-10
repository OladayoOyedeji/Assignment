(* Author: Oladayo Oyedeji
   File: main.ml *)

let rec sum_to n =
  if n <= 0 then
    0
  else
    n + sum_to (n-1);;

print_int (sum_to 0);;
print_string "\n";;
print_int (sum_to (-1));;
print_string "\n";;
print_int (sum_to 1);;
print_string "\n";;
print_int (sum_to 2);;
print_string "\n";;
print_int (sum_to 3);;
print_string "\n";;
print_int (sum_to 4);;
print_string "\n";;
