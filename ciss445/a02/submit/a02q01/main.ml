(* Author: Oladayo Oyedeji
   File: main.ml
*)

exception IgnoreCase;;
exception NotImplemented;;

let max x y z =
  if x >= y
     then
       if x >= z
          then
            x
       else
           z
  else if y > z
          then y
       else
         z;;
            
max 1 2 3;;
(* Tests:              Expected value*)
print_int (max 1 2 3);;        (*  3 *)
print_string "\n";;
print_int (max 1 3 2);;        (*  3 *)
print_string "\n";;
print_int (max 2 1 3);;        (*  3 *)
print_string "\n";;
print_int (max 2 3 1);;        (*  3 *)
print_string "\n";;
print_int (max 3 1 2);;        (*  3 *)
print_string "\n";;
print_int (max (-3) (-2) (-1));;(*-1 *)
print_string "\n";;
