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

let setintersect list1 list2 =
  let rec f list1 list2 acc =
    match list1 with
    [] -> acc
    | x::xs ->
      if elementof x list2 && not (elementof x acc) then
        f xs list2 (x::acc)
      else
        f xs list2 acc
  in
  rev (f list1 list2 [])
;;
  

let print_bool x = Printf.printf "%B" x;;

print_int_list (setintersect [1;2] []);;
print_string "\n";;
print_int_list (setintersect [1;2] [3;4]);;
print_string "\n";;
print_int_list (setintersect [5;2;1] [2;6;9]);;
print_string "\n";;
print_int_list (setintersect [5;2;5] [2;5;6]);;
print_string "\n";;
print_int_list (setintersect [5;2;7] [2;3;5;5;6]);;
print_string "\n";;
print_int_list (setintersect [1;3;5;7] [7;5;9]);;
print_string "\n";;

