(* rec.ml *)
(* read a rating database (.csv file) *)
(* and find the k "most similar" items *)

(*calls the from_file and takes the input for the file name. if an error is returned the user is given 
  the chance to try again*)
let get_db_file () =
  let () = print_string "Enter name of ratings file: " in
  let rfname = read_line () in
  try (Rating.from_file rfname) with Rating.RatingError -> let () = print_string "RatingError" in (exit 0) | Rating.ItemError-> let () = print_string "ItemError" in (exit 0) | Rating.LineFormatError -> let () = print_string "LineFormatError" in (exit 0)

(*calls the handle_from_iname and takes the input for the name. if the name doesn't exist the user is given 
  the chance to try again*)
let rec get_search_handle rdb =
  let () = print_string "Enter name of item to search for: " in
  let iname = read_line () in
  match Rating.handle_from_iname rdb iname with Some ih -> ih | None -> 
    let () = print_string "Enter continue or quit: " in
    let iname = read_line () in
    match iname with "quit" -> (exit 0) | _ -> get_search_handle rdb

(*helper for get_num_matches*)
let rec copy () = 
let () = print_string "Enter continue or quit: " in
  let iname = read_line () in
  match iname with "quit" -> (exit 0) | _ -> let () = print_string "How many suggestions do you want? (1-5): " in 
  try (let inum = read_int () in if (inum >= 1) && (inum <= 5) then inum else raise Not_found ) with _ -> copy ()

(*takes the input for the number of suggestions. if the input is not an integer the user is given 
  the chance to try again*)
let rec get_num_matches () =
  let () = print_string "How many suggestions do you want? (1-5): " in 
  try (let inum = read_int () in if (inum >= 1) && (inum <= 5) then inum else raise Not_found ) with _ -> copy ()

let ask_again () =
  let () = print_string "Make another recommendation? (y/n): " in
  let ans = read_line () in (String.lowercase_ascii ans) = "y"

(*prints out the lines of the similar items*)
let rec print_helper topk rdb i  u= match topk with
|[] -> ()
|(a, b)::t -> print_helper t rdb (i+1) (Printf.printf "%d)\t%6.3f\t%s: %s\n" i a (Rating.iname_from_handle rdb b) (Rating.description_from_handle rdb b)) 

(*prints out the unchanging score and setup then calls the helper function*)
let print_out topk rdb = 
let () = Printf.printf "# \tscore \tname: description\n==\t======\t===================\n" in (print_helper topk rdb 1 ()) 


let rec main_loop rdb =
  let ih = get_search_handle rdb in
  let k = get_num_matches () in
  let topk = Similar.top_k rdb k ih in
  let () = print_out topk rdb in
  if ask_again () then main_loop rdb else ()


let () = main_loop (get_db_file ())
