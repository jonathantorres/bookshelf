import { pair, head, tail, display, display_list, list, equal, is_null } from 'sicp';

const x = list(2, 3, 2, 1, 3, 2, 2); // set: 1,2,3
const y = list(3, 4, 3, 5, 4, 3); // set: 3,4,5
const z = list(1, 1, 2, 1, 2); // set: 1,2

display(is_element_of_set(1, x)); // true
display(is_element_of_set(4, x)); // false

display_list(adjoin_set(1, x));
display_list(adjoin_set(4, x));

display_list(intersection_set(x, y));
display_list(union_set(y, z));

function union_set(set1, set2) {
    if (is_null(set1)) {
        return set2;
    }
    if (is_null(set2)) {
        return set1;
    }
    return union_set(adjoin_set(head(set2), set1), tail(set2));
}

function intersection_set(set1, set2) {
    if (is_null(set1) || is_null(set2)) {
        return null;
    }
    if (is_element_of_set(head(set1), set2)) {
        return pair(head(set1), intersection_set(tail(set1), set2));
    }
    return intersection_set(tail(set1), set2);
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
