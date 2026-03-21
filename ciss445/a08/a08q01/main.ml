(* Name: Oladayo Oyedeji *)
(* File: main.ml *)

let rec in_list elem list = match list with
    [] -> false
  | x::xs -> if x = elem then true
    else
      in_list elem xs
;;

let dfa language states start_state accept_state transition =
  let state_transition state trans transition =
    let rec s_t transition = match transition with
        [] -> "crash"
      | (s,t,n)::xs -> 
        if s = state && t = trans
        then
          n
        else
          s_t xs
    in
    s_t transition
    in
  let rec loop state language = match language with
      [] -> in_list state accept_state
    | x::xs ->
        let next_state = state_transition state x transition in
        loop next_state xs
    in
    loop start_state language
;;

let m list = dfa list ["q0"; "q1"; "q2"] "q0" ["q2"]
    [("q0", "a", "q2");
     ("q0", "b", "q1");
     ("q1", "a", "q0");
     ("q1", "b", "q2");
     ("q2", "a", "q1");
     ("q2", "b", "q0")]
;;
