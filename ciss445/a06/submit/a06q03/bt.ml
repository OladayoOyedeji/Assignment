exception UnderFlow;;

type 'a btree = Empty
              | Node of 'a btree * 'a * 'a btree
;;

let is_leaf btnode = match btnode with
    Empty -> false
  | Node (_, _, node) -> (node = Empty)
;;

let rec size t = match t with
    Empty -> 0
  | Node (xs, _, ys) -> 1 + (size xs) + (size ys);;


let rec height t = match t with
    Empty -> -1
  | Node (ls, _, rs) -> let left = (height ls) in
    let right = (height rs) in
    if left < right then 1 + right else 1 + left;;

let rec max_in_list list = match list with
    [] -> raise UnderFlow
  | [x] -> x
  | x::xs -> let max_r = max_in_list xs in
  if max_r < x then x else max_r;;

let rec max t = match t with
    Empty -> -1
  | Node (Empty, x, Empty) -> x
  | Node (ls, x, Empty) -> let left = (max ls) in
    max_in_list [left; x]
  | Node (Empty, x, rs) -> let right = (max rs) in
    max_in_list [right; x]
  | Node (ls, x, rs) -> let left = (max ls) in
    let right = (max rs) in
    max_in_list [left; right; x];;

(* let rec foldbtree fleft fmid fright g t base = match t with *)
(*     Empty -> base *)
(*   | Node (Empty, x, Empty) -> fmid x *)
(*   | Node (ls, x, rs) -> g (fleft ls) (fmid x) (fright rs) *)

let rec is_bst tree = match tree with
    Empty -> true
  | Node (left, x, right) ->
    let l = (match left with
          Empty -> true
        | Node (_, y, _) -> is_bst left && y < x)
    in
    let r = (match right with
          Empty -> true
        | Node (_, y, _) -> is_bst right && y > x)
    in

    l && r
;;
      
let rec bst_insert t x = match t with
  Empty -> Node (Empty, x, Empty)
  | Node (ls, key, rs) ->
    if x < key
    then
      Node ((bst_insert ls x), key, rs)
    else
      if x > key
      then
        Node (ls, key, (bst_insert rs x))
      else
        t
;;

let mov_pred tree =
  let rec f tree = match tree with
      Empty -> raise UnderFlow
    | Node (ls, k, Empty) -> (ls, k)
    | Node (ls, k, rs) -> (let (rs, acc) = f rs in
      (Node (ls, k, rs), acc))
  in
  match tree with
    Empty -> Empty
  | Node (ls, k, rs) ->
  (let (ls, acc) = f ls
  in  Node (ls, acc, rs))
;;

let mov_succ tree =
  let rec f tree = match tree with
      Empty -> raise UnderFlow
    | Node (Empty, k, rs) -> (rs, k)
    | Node (ls, k, rs) -> (let (ls, acc) = f ls in
      (Node (ls, k, rs), acc))
  in
  match tree with
    Empty -> Empty
  | Node (ls, k, rs) ->
  (let (rs, acc) = f rs
  in  Node (ls, acc, rs))
;;

let rec bst_delete t x = match t with
    Empty -> Empty
  | Node (Empty, key, Empty) -> Empty
  | Node (Empty, key, rs) ->
    if x < key then
      t
    else
      if x > key then
        Node (Empty, key, bst_delete rs x)
      else
        mov_succ t
  | Node (ls, key, rs) ->
    if x < key then
      Node (bst_delete ls x, key, rs)
    else
      if x > key then
        Node (ls, key, bst_delete rs x)
      else
        mov_pred t
;;
              
                
