module Rating = struct
  type ih = int
  type uh = int
  type db = DB
  let from_file (s:string) = DB
  let iname_from_handle DB : ih -> string = string_of_int
  let handle_from_iname DB s : ih option = Some (int_of_string s)
  let description_from_handle DB : ih -> string = function 1 -> "one" | 2 -> "two" | 3 -> "three" | 4 -> "four" | 5 -> "five" | _ -> "nope."
  let get_users DB : uh list = [1;2;3;4;5;6]
  let get_items DB : ih list = [1;2;3;4;5]
  let get_item DB = function
  | 1 -> [(1,-1.);(2,1.)]
  | 2 -> [(2,-1.);(3,1.);(4,-1.)]
  | 3 -> [(1,-1.);(2,-1.);(4,-1.);(5,-1.)]
  | 4 -> [(6,1.);(2,-1.)]
  | 5 -> [(6,1.)] | _ -> raise Not_found
  let get DB (i : ih) (u : uh) = try List.assoc u (get_item DB i) with Not_found -> 0.
end

(* this just lets things in rec.ml compile... *)
module Similar = struct
  let similarity Rating.DB i1 i2 = 0.
  let rec top_k Rating.DB k i = if k = 0 then [] else (1.-.1./.(float_of_int k),k)::(top_k Rating.DB (k-1) i)
end
        
let check (x,m) (y,n) = (abs_float (x -. y)) < 1e-7 && m=n
let (=?) = List.for_all2 check
