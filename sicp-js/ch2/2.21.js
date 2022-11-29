import { display, display_list, list, head, tail, is_null, pair } from 'sicp';

const n = list(1,2,3,4,5);

display_list(square_list(n));
display_list(square_list_map(n));

function square_list(items) {
    if (is_null(items)) {
        return null;
    }
    return pair(square(head(items)), square_list(tail(items)));
}

function square_list_map(items) {
    return map(square, items);
}

function map(f, items) {
    if (is_null(items)) {
        return null;
    }
    return pair(f(head(items)), map(f, tail(items)));
}

function square(x) {
    return x*x;
}
