import { display, math_floor, math_random } from 'sicp';

display(is_prime(1009)); // true
display(is_prime(1000033)); // true

// carmichael numbers are not prime
display(is_prime(561));
display(is_prime(1105));
display(is_prime(1729));
display(is_prime(2465));
display(is_prime(2821));
display(is_prime(6601));

function is_prime(n) {
    return fast_is_prime(n, 10);
}

function fast_is_prime(n, times) {
    if (times === 0) {
        return true;
    }
    if (miller_rabin_test(n)) {
        return fast_is_prime(n, times-1);
    }
    return false;
}

function miller_rabin_test(n) {
    function try_it(a) {
        return expmod(a, n, n, n) === a;
    }
    return try_it(1+math_floor(math_random() * (n-1)));
}

function expmod(base, exp, m, n) {
    if (exp === 0) {
        return 1;
    }
    if (is_even(exp)) {
        let s = expmod(base, exp/2, m, n);
        if (s !== 1 && s !== m-1 && square(s)%m === 1) {
            return 0;
        }
        return square(s)%m;
    }
    return (base * expmod(base, exp-1, m, n)) % m;
}

function square(n) {
    return n*n;
}

function is_even(n) {
    return n%2 === 0;
}

