import { display, display_list, list, head, tail, is_null, pair, is_pair } from 'sicp';

const x = list(list(1, 2), list(3, 4));

display_list(deep_reverse(x));

function deep_reverse(l) {
    function dr(l) {
        if (is_null(l)) {
            return l;
        }
        if (!is_pair(l)) {
            return l;
        }
        return pair(is_pair(head(l)) ? reverse(dr(head(l))) : head(l), dr(tail(l)));
    }
    return reverse(dr(l));
}

function reverse(l) {
    function reverse_iter(l, res) {
        if (is_null(l)) {
            return res;
        }
        return reverse_iter(tail(l), pair(head(l), res));
    }
    return reverse_iter(l, null);
}

