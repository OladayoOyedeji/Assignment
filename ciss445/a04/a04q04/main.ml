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

let rec pop list y =
  match list with
    [] -> []
  | _::xs -> if y <= 0 then list
      else
        pop xs (y-1);;

let rec aux list y i =
  match list with
    [] -> []
  | x::xs -> if y <= 0 then []
      else
        x :: aux (pop xs (i-1)) (y-i) i;;

let slice list a b c = 
let list = pop list a
in
aux list (b - a) c;;

print_int_list (slice [6;7;8;9] 0 2 1);;
print_string "\n";;

print_int_list (slice [6;7;8;9] 0 3 2);;
print_string "\n";;

print_int_list (slice [6;7;8;9] 1 3 2);;
print_string "\n";;

print_int_list (slice [6;7;8;9] 1 100 100);;
print_string "\n";;

print_int_list (slice [6;7;8;9] 3 1 1);;
print_string "\n";;
