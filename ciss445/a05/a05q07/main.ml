(* Name: Oladayo Oyedeji
   File: main.ml *)

let print_bool x = Printf.printf "%B" x;;

let subsequence list1 list2 =
  let rec f list1 list2 acc = match acc with
  [] -> true
  | x::xs -> match list2 with
    [] -> false
    | y::ys -> if x = y then
        f list1 ys xs
      else
        f list1 ys acc
  in

  f list1 list2 list1;;
