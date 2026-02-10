(* Author: Oladayo Oyedeji
   File: main.ml *)

let rec isprime x =
  if x < 2 then
    false
  else
    isprime_pass x 2
and
  isprime_pass n d =
    if (d * d) > n then
      true
    else if n mod d == 0 then
      false
    else
      isprime_pass n (d+1);;

Printf.printf "0 %B\n" (isprime 0);;
Printf.printf "1 %B\n" (isprime 1);;
Printf.printf "2 %B\n" (isprime 2);;
Printf.printf "3 %B\n" (isprime 3);;
Printf.printf "4 %B\n" (isprime 4);;
Printf.printf "5 %B\n" (isprime 5);;
Printf.printf "6 %B\n" (isprime 6);;
Printf.printf "7 %B\n" (isprime 7);;
Printf.printf "8 %B\n" (isprime 8);;
Printf.printf "9 %B\n" (isprime 9);;
Printf.printf "10 %B\n" (isprime 10);;
Printf.printf "11 %B\n" (isprime 11);;
