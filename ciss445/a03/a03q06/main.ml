(* Author: Oladayo Oyedeji
   File: main.ml *)

exception IgnoreCase;;
exception NotImplemented;;

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
  print_string "]\n";;

let tail list = match list with
  [] -> []
  | _::xs -> xs;;

print_list print_int (tail []);;
print_list print_int (tail [1]);;
print_list print_int (tail [3; 1]);;
print_list print_int (tail [4; 5; 1]);;
