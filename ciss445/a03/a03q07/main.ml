(* Author: Oladayo Oyedeji
   File: main.ml *)

exception IgnoreCase;;
exception NotImplemented;;

let second list = match list with
  [] -> failwith "empty list"
  | [x] -> failwith "short list"
  | _::x::_ -> x;;


print_int(second [1; 2]);;
print_string "\n";;
print_int(second [3; 1; 2]);;
print_string "\n";;
print_int(second [4; 3; 2; 1]);;
print_string "\n";;
print_float(second [3.3; 4.4; 5.5]);;
print_string "\n";;
