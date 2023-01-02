import { pair, head, tail, display, display_list, list, is_pair, length } from 'sicp';

display(equal(list("this", "is", "a", "list"), list("this", "is", "a", "list")));
display(equal(list("this", "is", "a", "list"), list("this", list("is", "a"), "list")));
display(equal(list(1,2,3), list(1,2)));

function equal(a, b) {
    if (length(a) !== length(b)) {
        return false;
    }
    if (!is_pair(a) && !is_pair(b)) {
        return a === b;
    }
    return head(a) === head(b) && equal(tail(a), tail(b));
}
