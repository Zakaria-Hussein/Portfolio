(*given item1 and item2 returns the number of users who gave both the same rating.*)
let both db i1 i2 =
let rec inner_both ls1 ls2 acc= match ls1 with
|[] -> acc
|h::t -> if (List.mem h ls2) then (inner_both t ls2 (acc +. 1.)) else inner_both t ls2 acc
in inner_both (Rating.get_item db i1) (Rating.get_item db i2) 0.

(*given item1 and item2 returns the number of users who gave both opposite ratings.*)
let opposite1 db i1 i2 = 
let rec inner_opp1 ls1 ls2 acc= match ls1 with
|[] -> acc
|(a, b)::t -> if (List.mem (a, (-1. *. b)) ls2) then (inner_opp1 t ls2 (acc +. 1.)) else inner_opp1 t ls2 acc
in inner_opp1 (Rating.get_item db i1) (Rating.get_item db i2) 0.

(*calculates the cosine similarity for item1 and item2.*)
let similarity db i1 i2 = 
((both db i1 i2) -. (opposite1 db i1 i2)) /. 
(Stdlib.sqrt((float_of_int (List.length (Rating.get_item db i1))) *. (float_of_int (List.length (Rating.get_item db i2)))))

(*given item1 and a list of items returns a tuple list of the similarity between the item 
  and item1 and the item itself*)
let rec most_similar db it ls= match ls with
|[] -> []
|h::t -> ((similarity db it h), h)::(most_similar db it t)

(*sorts the similarity list from greatest to smallest*)
let sort_ls db it = (List.rev (List.sort (fun (a, _) (b, _) -> if a > b then 1 else if a < b then -1 else 0) (most_similar db it (Rating.get_items db))))

(*returns the top k number of similar items from the sorted list*)
let top_k db k it = 
let rec inner_top db k it ls acc = 
if k > (List.length ls) then ls else match ls with
|h::t -> if k = 0 then (List.rev acc) else inner_top db (k-1) it t (h::acc)
in inner_top db k it (match (sort_ls db it) with h::t -> t ) []

