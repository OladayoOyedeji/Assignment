(* Author: Oladayo Oyedeji
   File: main.ml *)

(* print list *)
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

(* duplicate list *)
let rec duplicate x n = match n with
0 -> []
| n -> x :: duplicate x (n-1);;

print_list print_int (duplicate 1 3);;
print_string "\n";;

print_list print_float (duplicate 1.23 0);;
print_string "\n";;

print_list print_float (duplicate 3.1 4);;
print_string "\n";;

print_list print_int_list (duplicate [1;2;3] 2);;
print_string "\n";;
