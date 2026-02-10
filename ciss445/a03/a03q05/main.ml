(* Author: Oladayo Oyedeji
   File: main.ml *)

exception IgnoreCase;;
exception NotImplemented;;

let head list = match list with
  [] -> failwith "empty list"
  | x::xs -> x;;


print_int(head [1]);;
print_string "\n";;
print_int(head [2; 1]);;
print_string "\n";;
print_int(head [3; 2; 1]);;
print_string "\n";;
print_float(head [1.1; 2.2]);;
print_string "\n";;
