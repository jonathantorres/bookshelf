import { display } from 'sicp';

const p = pair(1,2);

display(head(p));
display(tail(p));

function pair(a, b) {
    return fast_expt(2, a) * fast_expt(3, b);
}

function head(p) {
    if (is_even(p)) {
        return head(p/2) + 1;
    }
    return 0;
}

function tail(p) {
    if (p%3 === 0) {
        return tail(p/3) + 1;
    }
    return 0;
}

function fast_expt(b, n) {
    return fast_expt_iter(b, n, 1);
}

function fast_expt_iter(b, n, a) {
    if (n === 0) {
        return a;
    }
    if (is_even(n)) {
        return fast_expt_iter(square(b), n/2, a);
    }
    return fast_expt_iter(b, n-1, b*a);
}

function is_even(n) {
    return n%2 === 0;
}

function square(n) {
    return n*n;
}
