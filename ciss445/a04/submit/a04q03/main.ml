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

let rec range2 a b c =
  let break = if c > 0 then a >= b else a <= b
  in
  if break then []
  else a :: range2 (a + c) b c;;

print_list print_int (range2 1 3 1);;
print_string "\n";;

print_list print_int (range2 1 7 2);;
print_string "\n";;

print_list print_int (range2 1 6 2);;
print_string "\n";;

print_list print_int (range2 1 1 2);;
print_string "\n";;

print_list print_int (range2 3 (-2) (-1));;
print_string "\n";;

print_list print_int (range2 3 (-2) (-2));;
print_string "\n";;
