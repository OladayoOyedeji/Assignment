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

let print_bool x = Printf.printf "%B" x;;

print_bool (subseteq [] [1; 3; 5]);;
print_string "\n";;
print_bool (subseteq [] []);;
print_string "\n";;
print_bool (subseteq [2; 2; 2] [1; 2; 3]);;
print_string "\n";;
print_bool (subseteq [3; 2; 1] [1; 2; 3]);;
print_string "\n";;
print_bool (subseteq [1; 3; 5] [3; 1; 5; 7]);;
print_string "\n";;
print_bool (subseteq [1; 3; 5] [1; 3]);;
print_string "\n";;
