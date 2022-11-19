import { display, pair, head, tail, stringify, math_min, math_max } from 'sicp';

const x = make_interval(1, 2);
const y = make_interval(2, 4);

display(print_interval(sub_interval(x, y)));

function make_interval(x, y) {
    return pair(x, y);
}

function sub_interval(x, y) {
    return make_interval(
        lower_bound(x) - upper_bound(y),
        upper_bound(x) - lower_bound(y)
    );
}

function add_interval(x, y) {
    return make_interval(
        lower_bound(x) + lower_bound(y),
        upper_bound(x) + upper_bound(y)
    );
}

function upper_bound(i) {
    return head(i);
}

function lower_bound(i) {
    return tail(i);
}

function print_interval(i) {
    return "[ "  + stringify(lower_bound(i)) +
           " , " + stringify(upper_bound(i)) + " ]";
}

