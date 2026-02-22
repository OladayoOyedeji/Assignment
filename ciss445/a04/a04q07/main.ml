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

let print_int_list = print_list print_int;;
let print_float_list = print_list print_float;;

let rec elementof x list = match list with
  [] -> false
  | y::xs ->
    if y <> x then
      elementof x xs
    else
      true;;

let print_bool x = Printf.printf "%B" x;;

print_bool (elementof 1 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 3 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 5 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 0 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 2 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 4 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 6 [1; 3; 1; 5; 3; 5]);;
print_string "\n";;
print_bool (elementof 3.4 [1.2; 3.4; 5.6]);;
print_string "\n";;
print_bool (elementof 7.8 [1.2; 3.4; 5.6]);;
print_string "\n";;
