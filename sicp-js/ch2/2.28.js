import { display, display_list, list, head, tail, is_null, pair, is_pair, append } from 'sicp';

const x = list(list(1, 2), list(3, 4));
const y = list(x, x);

display_list(x);
display_list(fringe(x));

display_list(y);
display_list(fringe(y));

function fringe(l) {
    if (is_null(l)) {
        return l;
    }
    if (!is_pair(l)) {
        return pair(l, null);
    }
    return append(fringe(head(l)), fringe(tail(l)));
}
