(* Author: Oladayo Oyedeji
   File: main.ml *)

let print_list print_elem lst =
  print_string "[";
  let rec aux = function
    | [] -> ()
    | [x] -> print_elem x
    | x :: xs ->
        print_elem x;
        print_string "; ";
        aux xs
  in
  aux lst;
  print_string "]";;

let rec range x y = 
  if x >= y then []
  else x :: range (x+1) y;;

print_list print_int (range 1 3);;
print_string "\n";;

print_list print_int (range 1 1);;
print_string "\n";;

print_list print_int (range (-3) 2);;
print_string "\n";;

print_list print_int (range 6 3);;
print_string "\n";;
