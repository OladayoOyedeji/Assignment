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

let powerset list =
  let rec f list acc1 = match list with
    [] -> [acc1]
    | x::xs -> (f xs (acc1 @ [x])) @ (f xs (acc1))
  in

  (f list []);;

let print_bool x = Printf.printf "%B" x;;

print_list print_int_list (powerset []);;
print_string "\n";;
print_list print_int_list (powerset [1]);;
print_string "\n";;
print_list print_int_list (powerset [1;2]);;
print_string "\n";;
print_list print_int_list (powerset [1;2;3]);;
print_string "\n";;
print_list print_int_list (powerset [1;2;3;4]);;
print_string "\n";;

