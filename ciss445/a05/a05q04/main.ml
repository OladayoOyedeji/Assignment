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


let rev list =
  let rec f list revlist = match list with
      [] -> revlist
    | x::xs -> f xs (x::revlist)
  in
  f list []
;;

let rec elementof x list = match list with
  [] -> false
  | y::xs ->
    if y <> x then
      elementof x xs
    else
      true;;

let setsimplify list =
  let rec f list acc =
      match list with
        [] -> acc
      | x::xs ->
        if elementof x acc then
          f xs acc
        else
          f xs (x::acc)
  in
  rev (f list [])
;;

let setunion list1 list2 = setsimplify (list1@list2);;

let print_bool x = Printf.printf "%B" x;;

print_int_list (setunion [] []);;
print_string "\n";;
print_int_list (setunion [] [1]);;
print_string "\n";;
print_int_list (setunion [1;2;3] [3;2;1]);;
print_string "\n";;
print_int_list (setunion [1;2;2;3;1] [1;5;5;6]);;
print_string "\n";;
print_int_list (setunion [3;3;2;1] [2;3]);;
print_string "\n";;
