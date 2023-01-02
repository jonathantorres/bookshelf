import { display, display_list, list, head, tail, is_null } from 'sicp';

display_list(last_pair(list(1,2,3,4)));
display_list(last_pair(list(23, 72, 149, 34)));

function last_pair(l) {
    if (is_null(tail(l))) {
        return list(head(l));
    }
    return last_pair(tail(l));
}

