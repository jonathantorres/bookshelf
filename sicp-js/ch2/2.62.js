import { pair, head, tail, display, display_list, list, equal, is_null, append } from 'sicp';

const s = union_set(
   adjoin_set(10, adjoin_set(20, adjoin_set(30, null))),
   adjoin_set(10, adjoin_set(15, adjoin_set(20, null)))
);

display_list(s); // list(10, 15, 20, 30)

function union_set(set1, set2) {
    if (is_null(set1)) {
        return set2;
    }
    if (is_null(set2)) {
        return set1;
    }

    const x1 = head(set1);
    const x2 = head(set2);

    if (x1 === x2) {
        return pair(x1, union_set(tail(set1), tail(set2)));
    } else if (x1 < x2) {
        return pair(x1, union_set(tail(set1), set2));
    }

    return pair(x2, union_set(set1, tail(set2)));
}

function adjoin_set(x, set) {
    if (is_null(set)) {
        return pair(x, set);
    }
    if (equal(x, head(set))) {
        return set;
    }
    if (x > head(set)) {
        return pair(head(set), adjoin_set(x, tail(set)));
    }
    return pair(x, set);
}

function is_element_of_set(x, set) {
    if (is_null(set)) {
        return false;
    }
    if (equal(x, head(set))) {
        return true;
    }
    if (x < head(set)) {
        return false;
    }
    return is_element_of_set(x, tail(set));
}
