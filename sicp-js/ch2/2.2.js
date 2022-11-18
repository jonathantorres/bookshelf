import { display, pair, head, tail, stringify } from 'sicp';

const p1 = make_point(0, 0);
const p2 = make_point(1, 1);
const s = make_segment(p1, p2);
const m = midpoint_segment(s);

print_point(m);

function midpoint_segment(s) {
   const x = x_point(start_segment(s)) + x_point(end_segment(s));
   const y = y_point(start_segment(s)) + y_point(end_segment(s));

   return make_point(abs(x/2), abs(y/2));
}

function make_segment(p1, p2) {
    return pair(p1, p2);
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

function numer(p) {
    return head(p);
}

function denom(p) {
    return tail(p);
}

function abs(x) {
    return x >= 0 ? x : - x;
}

