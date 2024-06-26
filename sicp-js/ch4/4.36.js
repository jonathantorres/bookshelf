// this program must be run from the Source environment
// using the Non-deterministic variant
// https://sourceacademy.org/playground

// There are 5 different solutions to the office move puzzle

function distinct(items) {
    return is_null(items)
           ? true
           : is_null(tail(items))
           ? true
           : is_null(member(head(items), tail(items)))
           ? distinct(tail(items))
           : false;
}

function office_move() {
    const alyssa = amb(1, 2, 3, 4, 5);
    const ben = amb(1, 2, 3, 4, 5);
    const cy = amb(1, 2, 3, 4, 5);
    const lem = amb(1, 2, 3, 4, 5);
    const louis = amb(1, 2, 3, 4, 5);
    require(distinct(list(alyssa, ben, cy, lem, louis)));
    require(alyssa !== 5);
    require(ben !== 1);
    require(cy !== 5);
    require(cy !== 1);
    require(lem > ben);
    require(math_abs(cy - ben) !== 1);
    return list(list("alyssa", alyssa),
                list("ben", ben),
                list("cy", cy),
                list("lem", lem),
                list("louis", louis));
}

display_list(office_move());
