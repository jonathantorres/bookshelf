import {
    display, is_pair, is_null, list, pair, head,
    tail, set_head, set_tail, error, member, append
} from 'sicp';

const three_list = list("a", "b", "c");
const one = pair("a", "b");
const three = pair(one, one);
const four = pair(three, "c");
const seven = pair(three, three);

display(count_pairs(three_list));
display(count_pairs(four));
display(count_pairs(seven));

const cycle = make_cycle(three_list);
display(count_pairs(cycle));

function count_pairs(x) {
    let members = list();
    function cp(x) {
        if (!is_pair(x) || member(head(x), members)) {
            return 0;
        }
        members = append(members, list(head(x)));
        return cp(head(x)) + cp(tail(x)) + 1;
    }
    return cp(x);
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
