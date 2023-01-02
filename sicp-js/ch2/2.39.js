import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate, append
} from 'sicp';

const fold_right = accumulate;
const l = list(1, 2, 3);

display_list(reverse(l));
display_list(reverse_with_fold_left(l));

function reverse(sequence) {
    return fold_right((x, y) => append(y, list(x)), null, sequence);
}

function reverse_with_fold_left(sequence) {
    return fold_left((x, y) => pair(y, x), null, sequence);
}

function fold_left(op, initial, sequence) {
    function iter(result, rest) {
        return is_null(rest)
               ? result
               : iter(op(result, head(rest)), tail(rest));
    }
    return iter(initial, sequence);
}

