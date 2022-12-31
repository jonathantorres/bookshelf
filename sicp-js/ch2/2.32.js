import {
    display, display_list, list, head, tail,
    is_null, pair, is_pair, map, append
} from 'sicp';

const l = list(1,2,3);

display_list(subsets(l));

function subsets(s) {
    if (is_null(s)) {
        return list(null);
    } else {
        const rest = subsets(tail(s));
        return append(rest, map(sub => {
            if (is_null(sub)) {
                return list(head(s));
            }
            return pair(head(s), pair(head(sub), tail(sub)));
        }, rest));
    }
}

