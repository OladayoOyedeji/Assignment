(*
   Author: Oladayo Oyedeji
   File: main.ml
*)

exception IgnoreCase;;
exception NotImplemented;;

let comp_func f g x = f(g(x));;

let f x = x +. 1.0;;
let g x = x -. 1.0;;
let h x = x *. x;;

print_float ((comp_func f g) 0.0);;
print_string "\n";;
print_float ((comp_func f g) 1.0);;
print_string "\n";;
print_float ((comp_func g f) 2.0);;
print_string "\n";;
print_float ((comp_func g f) 3.0);;
print_string "\n";;
print_float ((comp_func f h) 0.0);;
print_string "\n";;
print_float ((comp_func f h) 1.0);;
print_string "\n";;
print_float ((comp_func h f) 2.0);;
print_string "\n";;

