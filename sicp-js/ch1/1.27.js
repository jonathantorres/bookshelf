import { display } from 'sicp';

display(carmichael(561));
display(carmichael(1105));
display(carmichael(1729));
display(carmichael(2465));
display(carmichael(2821));
display(carmichael(6601));

// not a carmichael
display(carmichael(100));

function carmichael(n) {
    return carmichael_iter(n, 0);
}

function carmichael_iter(n, a) {
    if (n === a) {
        return true;
    }
    if (!fermat_test(n, a)) {
        return false;
    }
    return carmichael_iter(n, a+1);
}

function fermat_test(n, a) {
    return expmod(a, n, n) === a;
}

function expmod(base, exp, m) {
    if (exp === 0) {
        return 1;
    }
    if (is_even(exp)) {
        return square(expmod(base, exp/2, m)) % m;
    }
    return (base * expmod(base, exp-1, m)) % m;
}

function is_even(n) {
    return n%2 === 0;
}

function square(n) {
    return n*n;
}
