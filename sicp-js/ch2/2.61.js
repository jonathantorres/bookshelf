import { pair, head, tail, display, display_list, list, equal, is_null, append } from 'sicp';

display_list(adjoin_set(5, list(1,3,4)));
display_list(adjoin_set(2, list(1,3,4)));
display_list(adjoin_set(3, list(1,3,4)));
display_list(adjoin_set(0, list(1,3,4)));
display_list(adjoin_set(10, adjoin_set(15, adjoin_set(20, null))));

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
