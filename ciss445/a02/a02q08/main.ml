(*
   Author: Oladayo Oyedeji
   File: main.ml
*)

exception IgnoreCase;;
exception NotImplemented;;

let d f h x = (f(x +. h) -. f(x)) /. h;;

print_float (d (fun x -> x +. 3.0) 2.0 5.0);;
print_string "\n";;
print_float (d (fun x -> x *. x) 0.001 1.0);;
print_string "\n";;
