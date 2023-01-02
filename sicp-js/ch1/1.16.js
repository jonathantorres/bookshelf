import { display } from 'sicp';

display(fast_expt(2, 8)); // 256
display(fast_expt(2, 10)); // 1024
display(fast_expt(5, 5));
display(fast_expt(500, 100));

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
