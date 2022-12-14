import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate
} from 'sicp';

const l = list(list(1, 2, 3), list(4, 5, 6), list(7, 8, 9), list(10, 11, 12));

display_list(accumulate_n(plus, 0, l));

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

