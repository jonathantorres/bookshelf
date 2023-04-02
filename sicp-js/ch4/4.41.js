// this program must be run from the Source environment
// using the Non-deterministic variant
// https://sourceacademy.org/playground

// Cy checks the exercises in the "Data" chapter and there are 4 different solutions
function distinct(items) {
    return is_null(items)
           ? true
           : is_null(tail(items))
           ? true
           : is_null(member(head(items), tail(items)))
           ? distinct(tail(items))
           : false;
}

function chapter_check() {
    const alyssa = pair(2, 4);
    const louis = pair(1, 5);
    const ben = pair(5, amb(1,2,3));
    const cy = pair(3, amb(1,2));
    const eva = pair(4, amb(1,2,3));

    require(distinct(list(tail(ben), tail(cy), tail(eva))));

    return list(list("ben", tail(ben)),
                list("cy", tail(cy)),
                list("eva", tail(eva)));
}

display_list(chapter_check());
