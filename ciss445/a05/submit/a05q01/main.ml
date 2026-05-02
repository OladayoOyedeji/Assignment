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

let rec subseteq list1 list2 = match list1 with
  [] -> true
  | x::xs ->
    if elementof x list2 then
      subseteq xs list2
    else
      false;;

let seteq list1 list2 = subseteq list1 list2 && subseteq list2 list1;;

let print_bool x = Printf.printf "%B" x;;

print_bool (seteq [] []);;
print_string "\n";;
print_bool (seteq [1] []);;
print_string "\n";;
print_bool (seteq [] [1]);;
print_string "\n";;
print_bool (seteq [1] [1; 1]);;
print_string "\n";; 
print_bool (seteq [1; 1] [1]);;
print_string "\n";;
print_bool (seteq [1; 2] [2; 1]);;
print_string "\n";;
print_bool (seteq [2; 1] [1; 2]);;
print_string "\n";;
print_bool (seteq [1; 2] [3; 2; 1]);;
print_string "\n";;
print_bool (seteq [1; 2] [3;3;2; 1]);;
print_string "\n";;
