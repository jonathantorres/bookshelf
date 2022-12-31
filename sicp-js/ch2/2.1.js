import { display, pair, head, tail, stringify } from 'sicp';

const neg = make_rat(-6,-3);
print_rat(neg);

function make_rat(n, d) {
    const g = gcd(n, d);
    return pair(sign(n)*sign(d)*abs(n/g), abs(d/g));
}

function numer(p) {
    return head(p);
}

function denom(p) {
    return tail(p);
}

function print_rat(x) {
    return display(stringify(numer(x)) + " / " + stringify(denom(x)));
}

function sign(n) {
    if (n < 0) {
        return -1;
    } else if (n > 0) {
        return 1;
    } else {
        return 0;
    }
}

function abs(x) {
    return x >= 0 ? x : - x;
}

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}

