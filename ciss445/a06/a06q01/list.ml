
exception StackUnderFlow

type 'a list = Empty
             | Cons of 'a * 'a list
;;

let init () = Empty;;

let size list = 
  let rec f list n = match list with
      Empty -> n
    | Cons (y, ys) -> f ys (n + 1)
  in
  f list 0
;;

let is_empty list = list = Empty;;

let head list = match list with
  Empty -> raise StackUnderFlow
  | Cons (y, ys) -> y;;
  
let rec tail list = match list with
  Empty -> raise StackUnderFlow
  | Cons (x, Empty) -> x
  | Cons (x, xs) -> tail xs;;

let insert_head list x = Cons (x, list);;

let delete_head list = match list with
  Empty -> raise StackUnderFlow
  | Cons (y, Empty) -> Empty
  | Cons (y, Cons (x, xs)) -> Cons (x, xs);;


let rec insert_tail list x = match list with
  Empty -> Cons(x, Empty)
  | Cons (y, ys) -> Cons (y, insert_tail ys x)
;;

let rec delete_tail list = match list with
  Empty -> Empty
  | Cons (y, Empty) -> Empty
  | Cons (y, ys) -> Cons (y, delete_tail ys)
;;

let rev list =
  let rec rev2 list revlist = match list with
    Empty -> revlist
    | Cons (x, xs) -> rev2 xs (Cons (x, revlist))
  in
  rev2 list Empty
;;
