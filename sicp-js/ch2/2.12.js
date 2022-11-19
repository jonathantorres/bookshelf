import { display, pair, head, tail, stringify } from 'sicp';

display(percent(make_interval(30, 35)));
display(make_center_percent(30, 15));

function make_center_percent(c, p) {
    const w = (p/100) * c;
    return make_center_width(c, w);
}

function make_center_width(c, w) {
    return make_interval(c - w, c + w);
}

function percent(i) {
    return ((upper_bound(i) - lower_bound(i)) / lower_bound(i)) * 100;
}

function center(i) {
    return (lower_bound(i) + upper_bound(i)) / 2;
}

function width(i) {
    return (upper_bound(i) - lower_bound(i)) / 2;
}

function make_interval(x, y) {
    return pair(x, y);
}

function upper_bound(i) {
    return tail(i);
}

function lower_bound(i) {
    return head(i);
}

function print_interval(i) {
    return "[ "  + stringify(lower_bound(i)) +
           " , " + stringify(upper_bound(i)) + " ]";
}
