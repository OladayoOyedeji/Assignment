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

let at list target =
  let rec f list i target = match list with
  [] -> -1
  | x::xs ->
    if
      i = target
    then
      x
    else
      f xs (i+1) target
  in
  f list 0 target;;

print_int (at [5;3;1] 0);;
print_string "\n";;

print_int (at [2;4;6] 1);;
print_string "\n";;

print_int (at [1;3;5;7] 3);;
print_string "\n";;
