import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate
} from 'sicp';

const x = list(list(1, 2), list(3, 4));
const y = list(list(1, 2), list(3, 4), 5, list(10, 11, list(2, 3, 4)));
const z = pair(list(1, 2), list(3, 4));

display(count_leaves(x));
display(count_leaves(y));
display(count_leaves(z));

function count_leaves(t) {
    return accumulate((x, y) => x+y, 0, map(st => {
        if (is_null(st)) {
            return 0;
        }
        if (!is_pair(st)) {
            return 1;
        }
        return count_leaves(st);
    }, t));
}
