import { display, pair, head, tail, stringify, math_sqrt } from 'sicp';

const top = make_segment(
    make_point(0, 10),
    make_point(10, 10)
);
const bottom = make_segment(
    make_point(0, 0),
    make_point(10, 0)
);
const left = make_segment(
    make_point(0, 0),
    make_point(0, 10)
);
const right = make_segment(
    make_point(10, 0),
    make_point(10, 10)
);

const rect = make_rect(top, bottom, left, right);
display(rect_perim(rect));
display(rect_area(rect));

function make_rect(top, bottom, left, right) {
    return pair(
        pair(top, bottom),
        pair(left, right)
    );
}

function rect_perim(r) {
    return segment_len(rect_top(r))
        + segment_len(rect_bottom(r))
        + segment_len(rect_right(r))
        + segment_len(rect_left(r));
}

function rect_area(r) {
    return segment_len(rect_top(r)) * segment_len(rect_left(r));
}

function rect_top(r) {
    return head(head(r));
}

function rect_bottom(r) {
    return tail(head(r));
}

function rect_right(r) {
    return tail(tail(r));
}

function rect_left(r) {
    return head(tail(r));
}

function make_segment(p1, p2) {
    return pair(p1, p2);
}

function segment_len(s) {
    const x1 = x_point(start_segment(s));
    const x2 = x_point(end_segment(s));
    const y1 = y_point(start_segment(s));
    const y2 = y_point(end_segment(s));

    return math_sqrt(square(x2 - x1)+square(y2-y1));
}

function start_segment(s) {
    return head(s);
}

function end_segment(s) {
    return tail(s);
}

function make_point(x, y) {
    return pair(x, y);
}

function x_point(p) {
    return head(p);
}

function y_point(p) {
    return tail(p);
}

function print_point(p) {
    display("(" + stringify(x_point(p)) + "," + stringify(y_point(p)) + ")");
}

function square(n) {
    return n*n;
}

