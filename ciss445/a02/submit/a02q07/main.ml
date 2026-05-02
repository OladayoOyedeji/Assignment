(*
   Author: Oladayo Oyedeji
   File: main.ml
*)

exception IgnoreCase;;
exception NotImplemented;;

let max_func f g x =
  if f(x) >= g(x)
     then
       if f(x) >= x
          then
            f(x)
       else
           x
  else if g(x) > x
          then g(x)
       else
         x;;

let f x = x +. 1.0;;
let g x = x -. 1.0;;
let h x = x *. x;;

print_float ((max_func f g) 0.0);;
print_string "\n";;
print_float ((max_func f g) 1.0);;
print_string "\n";; 
print_float ((max_func g f) 2.0);;
print_string "\n";;
print_float ((max_func g f) 3.0);;
print_string "\n";;
print_float ((max_func f h) 0.0);;
print_string "\n";;
print_float ((max_func f h) 1.0);;
print_string "\n";;
print_float ((max_func h f) 2.0);;
print_string "\n";;

