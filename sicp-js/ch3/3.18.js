import {
    display, is_pair, is_null, list, pair, head, equal,
    tail, set_head, set_tail, error, member, append
} from 'sicp';

const a = list("a", "b", "c");
display(has_cycle(a));

const b = list("a", "a", "a");
display(has_cycle(b));

const c = 1;
display(has_cycle(c));

const cycle = make_cycle(a);
display(has_cycle(cycle));

function has_cycle(x) {
    function check(y) {
        if (is_null(y)) {
            return false;
        }
        if (x === y) {
            return true;
        }
        return check(tail(y));
    }
    if (!is_pair(x)) {
        return false;
    }
    return check(tail(x));
}

function last_pair(x) {
    return is_null(tail(x))
           ? x
           : last_pair(tail(x));
}

function make_cycle(x) {
    set_tail(last_pair(x), x);
    return x;
}
