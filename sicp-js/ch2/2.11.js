import { display, pair, head, tail, stringify, math_min, math_max } from 'sicp';

const i = make_interval(1, 2);
const j = make_interval(2, 4);

display(print_interval(mul_interval(i, j)));

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
    const xl = lower_bound(x);
    const xu = upper_bound(x);
    const yl = lower_bound(y);
    const yu = upper_bound(y);

    if (p(xl) && p(xu) && p(yl) && p(yu)) {
        return make_interval(xl * yl, xu * yu);
    }

    if (p(xl) && p(xu) && n(yl) && p(yu)) {
        return make_interval(xu * yl, xu * yu);
    }

    if (p(xl) && p(xu) && n(yl) && n(yu)) {
        return make_interval(xu * yl, xl * yu);
    }

    if (n(xl) && p(xu) && p(yl) && p(yu)) {
        return make_interval(xl * yu, xu * yu);
    }

    if (n(xl) && p(xu) && n(yl) && n(yu)) {
        return make_interval(xu * yl, xl * yl);
    }

    if (n(xl) && n(xu) && p(yl) && p(yu)) {
        return make_interval(xl * yu, xu * yl);
    }

    if (n(xl) && n(xu) && n(yl) && p(yu)) {
        return make_interval(xl * yu, xl * yl);
    }

    if (n(xl) && n(xu) && n(yl) && n(yu)) {
        return make_interval(xu * yu, xl * yl);
    }

    if (n(xl) && p(xu) && n(yl) && p(yu)) {
        return final_mul(xl, xu, yl, yu);
    }

    return error("lower larger than upper");
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

function final_mul(xl, xu, yl, yu) {
    const p1 = xl * yl;
    const p2 = xl * yu;
    const p3 = xu * yl;
    const p4 = xu * yu;

    return make_interval(math_min(p1, p2, p3, p4), math_max(p1, p2, p3, p4));
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

function p(n) {
    return n >= 0;
}

function n(n) {
    return !p(n);
}

