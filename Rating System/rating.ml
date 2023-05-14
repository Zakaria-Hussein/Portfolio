type ih = int
type uh = int
(*db is a record holding the list or assoc lists to hold the values from the files being read in*)
type db = { handles : int list ; handle_Name : (int*string) list ; handle_Descript : (int*string) list 
; handle_user : (int*int) list ; handle_user_rating : (int*int*float) list }
exception LineFormatError
exception ItemError
exception RatingError

(*takes each line from the from_file and splits the string by commas. 
Then the first element determines i or r and from there each value is added the the list it belongs to 
and the updated record is returned.*)
let add s r = let ls = (String.split_on_char ',' s) in try (match (List.hd ls) with
| "i" -> let r = {handles = r.handles@[int_of_string (List.nth ls 1)] ; handle_Name = r.handle_Name@[(int_of_string (List.nth ls 1), (List.nth ls 2))] ; 
handle_Descript = r.handle_Descript@[(int_of_string (List.nth ls 1), (List.nth ls 3))] ; handle_user = r.handle_user ; handle_user_rating = r.handle_user_rating} in r
| "r" -> let r = {handles = r.handles ; handle_Name = r.handle_Name ; 
handle_Descript = r.handle_Descript ; handle_user = r.handle_user@[(int_of_string (List.nth ls 2), (int_of_string (List.nth ls 1)))] ; handle_user_rating = r.handle_user_rating@[(int_of_string (List.nth ls 2)), (int_of_string (List.nth ls 1)),(float_of_string (List.nth ls 3))]} in r) with Match_failure _ -> r

(*splits the string by commas and matches the first element to i or r. if neither then raises the LineFormatError.
  once matched checks if the list is length 4 and that the names and handles can be converted to int.
  for r we check if the rating can be converted to float. All these checks got through an if and return the record or raise the error*)
let check_line reco s = 
let rec inner_line s = let ls = (String.split_on_char ',' s) in match List.hd ls with
|"i" -> if ((List.length ls = 4) && (if (try (match (int_of_string (List.nth ls 1)) with _ -> true) with Failure _ -> false) <> false then true else false)) then reco else raise LineFormatError
|"r" -> if ((List.length ls = 4) && (if (try (match (int_of_string (List.nth ls 1)) with _ -> true) with Failure _ -> false) <> false then true else false) && 
    (if (try (match (int_of_string (List.nth ls 2)) with _ -> true) with Failure _ -> false) <> false then true else false) && 
    (if (try (match (float_of_string (List.nth ls 3)) with _ -> true) with Failure _ -> false) <> false then true else false)) then reco else raise LineFormatError
|_ -> raise LineFormatError
in inner_line s

(*checks if there are any duplicate values in the handle list. if true then raise the error 
else return true*)
let check_handle reco = 
let rec inner_handle ls = match ls with
|[] -> true
|h::t -> if List.mem h t then raise ItemError else inner_handle t
in inner_handle reco.handles

(*checks if there are any duplicate Names in the handle_Name list. if true then raise the error 
else return true*)
let check_shortName reco = 
let rec inner_short ls = match ls with
|[] -> true
|h::t -> if List.mem h t then raise ItemError else inner_short t
in inner_short (List.map (fun (_, b) -> b) reco.handle_Name)

(*checks if any values in the rating list are not -1. or 1. if true raises the error
  returns true*)
let check_rating reco = 
let rec inner_rate ls = match ls with
|[] -> true
|(_, _, h)::t -> if ((h <> 1.) && (h <> -1.)) then raise RatingError else inner_rate t 
in inner_rate reco.handle_user_rating

(*checks if any values in the rating list do not have item handles to match. if true raises the error
  returns true*)
let check_missing_rate reco = 
let rec inner_miss ls = match ls with
|[] -> true
|(h, _, _)::t -> if List.mem h (reco.handles) then inner_miss t else raise RatingError
in inner_miss reco.handle_user_rating

(*checks if any duplicates of handle_user entries appear. if true then raise error 
else return true*)
let check_double reco = 
let rec inner_double ls = match ls with
|[] -> true
|h::t -> if List.mem h t then raise RatingError else inner_double t
in inner_double reco.handle_user


(*opens the file and reads in each line and passes the lines to the check_line to check for LineFormatErrors
  if no errors then passes them to the add and adds to the db before calling recursively on that db.
  Once complete the file is closed and the entire db is passed through each error checking function.
  if no errors are found then the db is returned.*)
let from_file f = let ic = open_in f in
let rec helper reco = 
match (try Some (input_line ic) with End_of_file -> None) with
|None -> let () = close_in ic in if ((check_double reco) && (check_handle reco) && (check_missing_rate reco) && (check_rating reco) && (check_shortName reco)) then reco else reco
|Some s -> helper (add s (check_line reco s)) 
in helper {handles = [] ; handle_Name = [] ; handle_Descript = [] ; handle_user = [] ; handle_user_rating = []}

(*returns the iname given the item handle*)
let iname_from_handle d ih = let l = List.filter (fun (a, b) -> if (a = ih) then true else false) d.handle_Name in match l with [] -> raise Not_found | _ -> Stdlib.snd (List.hd l)

(*returns description given the item handle*)
let description_from_handle d ih = let l = List.filter (fun (a, b) -> if (a = ih) then true else false) d.handle_Descript in match l with [] -> raise Not_found | _ -> Stdlib.snd (List.hd l)

(*returns the item handle given the name*)
let handle_from_iname d name = let l = List.filter (fun (a, b) -> if (b = name) then true else false) d.handle_Name in match l with [] -> None | _ -> Some (Stdlib.fst (List.hd l))

(*returns the rating given a user and item handle*)
let get d i u = 
let rec inner_get ls = match ls with
|[] -> 0.
|(a, b, c)::t -> if (a = i) && (b = u) then c else inner_get t 
in inner_get d.handle_user_rating

(*returns the handle list*)
let get_items d = d.handles

(*returns the user list*)
let get_users d = List.sort_uniq (fun a b -> if a > b then 1 else if b > a then -1 else 0) (List.map (Stdlib.snd) d.handle_user)

(*returns all the user rating pairs given an item handle*)
let get_item d i = 
let rec inner_get_item ls acc = match ls with
|[] -> if acc = [] then raise Not_found else acc
|(a, b, c)::t -> if (a = i) then inner_get_item t ((b, c)::acc) else inner_get_item t acc
in inner_get_item d.handle_user_rating []