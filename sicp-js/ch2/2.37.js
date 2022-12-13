import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate
} from 'sicp';

const v = list(10, 20, 30);

// 1 2 3
// 3 5 1
// 1 1 1
const m1 = list(
    list(1, 2, 3),
    list(3, 5, 1),
    list(1, 1, 1)
);

// 1 2 3
// 4 5 6
// 7 8 9
const m2 = list(
    list(1, 2, 3),
    list(4, 5, 6),
    list(7, 8, 9)
);

// 11
display(dot_product(list(1, 2), list(3, 4)));

// list(140, 160, 60)
display_list(matrix_times_vector(m1, v));

// list(list(1, 3, 1), list(2, 5, 1), list(3, 1, 1))
display_list(transpose(m1));

// list(list(30, 36, 42), list(30, 39, 48), list(12, 15, 18))
display_list(matrix_times_matrix(m1, m2));

function matrix_times_vector(m, v) {
    return map(r => {
        return dot_product(r, v);
    }, m);
}

function transpose(mat) {
    return accumulate_n((x, y) => {
        return pair(x, y);
    }, list(), mat);
}

// n = 
// 1 2 3
// 3 5 1
// 1 1 1

// m = 
// 1 2 3
// 4 5 6
// 7 8 9

// transpose(n) = 
// 1 3 1
// 2 5 1
// 3 1 1

// 30 46 42
// 30 39 48
// 12 15 18
// list(list(30, 36, 42), list(30, 39, 48), list(12, 15, 18))
function matrix_times_matrix(n, m) {
    const cols = transpose(n);
    return map(r => {
        return matrix_times_vector(transpose(m), matrix_times_vector(cols, r));
    }, m);
}

function dot_product(v, w) {
    return accumulate(plus, 0, accumulate_n(times, 1, list(v, w)));
}

function accumulate_n(op, init, seqs) {
    if (is_null(head(seqs))) {
        return null;
    }

    return pair(
        accumulate(op, init, map(sl => head(sl), seqs)),
        accumulate_n(op, init, map(sl => tail(sl), seqs))
    );
}

function plus(x, y) {
    return x+y;
}

function times(x, y) {
    return x*y;
}
