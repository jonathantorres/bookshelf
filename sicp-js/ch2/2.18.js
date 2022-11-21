import { display, display_list, list, head, tail, is_null, pair } from 'sicp';

display_list(reverse(list(1,2,3,4,5,6)));

function reverse(l) {
    if (is_null(tail(l))) {
        return l;
    }
    return append(reverse(tail(l)), pair(head(l), null));
}

function append(list1, list2) {
    return is_null(list1)
           ? list2
           : pair(head(list1), append(tail(list1), list2));
}

