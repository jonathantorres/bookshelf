import { pair, head, tail, display, display_list } from 'sicp';

const s = make_segment(
    make_vect(0, 1),
    make_vect(1, 1),
);

display(s);

function make_segment(start, end) {
    return pair(start, end);
}

function start_segment(s) {
    return head(s);
}

function end_segment(s) {
    return tail(s);
}

function make_vect(x, y) {
    return pair(x, y);
}

function xcor_vect(v) {
    return head(v);
}

function ycor_vect(v) {
    return tail(v);
}
