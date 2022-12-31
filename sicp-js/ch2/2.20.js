import { display, display_list, list, head, tail, is_null, pair } from 'sicp';

display(brooks(plus_curried, list(3, 4))); // 7
display(brooks_curried(list(plus_curried, 3, 4))); // 7

// this call returns 7
display(brooks_curried(list(brooks_curried, list(plus_curried, 3, 4))));

// this call returns 7
display(brooks_curried(list(brooks_curried, list(brooks_curried, list(plus_curried, 3, 4)))));

function brooks(f, params) {
    if (is_null(params)) {
        return f;
    }
    return brooks(f(head(params)), tail(params));
}

function brooks_curried(params) {
    return brooks(head(params), tail(params));
}

function plus_curried(x) {
    return y => y+x;
}
