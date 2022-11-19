import { display, pair, head, tail, stringify, math_min, math_max } from 'sicp';

const i = make_interval(1, 2);
const j = make_interval(2, 4);

display(print_interval(add_interval(i, j)));

function make_interval(x, y) {
    return pair(x, y);
}

function add_interval(x, y) {
    return make_interval(
        lower_bound(x) + lower_bound(y),
        upper_bound(x) + upper_bound(y)
    );
}

function mul_interval(x, y) {
    const p1 = lower_bound(x) * lower_bound(y);
    const p2 = lower_bound(x) * upper_bound(y);
    const p3 = upper_bound(x) * lower_bound(y);
    const p4 = upper_bound(x) * upper_bound(y);

    return make_interval(
        math_min(p1, p2, p3, p4),
        math_max(p1, p2, p3, p4)
    );
}

function div_interval(x, y) {
    return mul_interval(
        x,
        make_interval(
            1 / upper_bound(y),
            1 / lower_bound(y)
        )
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

