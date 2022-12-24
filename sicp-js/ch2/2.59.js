import { pair, head, tail, display, display_list, list, equal, is_null } from 'sicp';

const s = union_set(
   adjoin_set(10, adjoin_set(20, adjoin_set(30, null))),
   adjoin_set(10, adjoin_set(15, adjoin_set(20, null)))
);

display_list(s);

function union_set(set1, set2) {
    if (is_null(set1)) {
        return set2;
    }
    if (is_null(set2)) {
        return set1;
    }
    return union_set(adjoin_set(head(set2), set1), tail(set2));
}

function is_element_of_set(x, set) {
    if (is_null(set)) {
        return false;
    }
    if (equal(x, head(set))) {
        return true;
    }
    return is_element_of_set(x, tail(set));
}

function adjoin_set(x, set) {
    if (is_element_of_set(x, set)) {
        return set;
    }
    return pair(x, set);
}
