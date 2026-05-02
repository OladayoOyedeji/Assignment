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

let index list target =
  let rec f list i target = match list with
  [] -> -1
  | x::xs ->
    if
      x = target
    then
      i
    else
      f xs (i+1) target
  in
  f list 0 target;;

print_int (index [6; 7; 8; 9] 3);;
print_string "\n";;

print_int (index [6; 7; 8; 9] 10);;
print_string "\n";;

print_int (index [9; 8; 7; 6] 9);;
print_string "\n";;

print_int (index [9; 7; 6; 8] 7);;
print_string "\n";;

print_int (index [9; 8; 6; 7] 7);;
print_string "\n";;

print_int (index [] 1);;
print_string "\n";;

print_int (index [1; 2; 3; 3; 3] 3);;
print_string "\n";;

print_int (index [1.1; 2.2; 3.3; 3.3; 3.3] 3.3);;
print_string "\n";;
