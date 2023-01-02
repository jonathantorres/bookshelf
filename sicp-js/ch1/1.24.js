import { display, get_time, math_floor, math_random } from 'sicp';

timed_prime_test(1009);
timed_prime_test(1013);
timed_prime_test(1019);

timed_prime_test(10007);
timed_prime_test(10009);
timed_prime_test(10037);

timed_prime_test(100003);
timed_prime_test(100019);
timed_prime_test(100043);

timed_prime_test(1000003);
timed_prime_test(1000033);

function timed_prime_test(n) {
    display(n);
    return start_prime_test(n, get_time());
}

function start_prime_test(n, start_time) {
    if (is_prime(n)) {
        return report_prime(get_time() - start_time);
    }
    return true;
}

function report_prime(elapsed_time) {
    display(" *** ");
    display(elapsed_time);
}

function is_prime(n) {
    // if n passes the test 5 times, n is considered a prime
    return fast_is_prime(n, 5);
}

function fast_is_prime(n, times) {
    if (times === 0) {
        return true;
    }
    if (fermat_test(n)) {
        return fast_is_prime(n, times-1);
    }
    return false;
}

function fermat_test(n) {
    function try_it(a) {
        return expmod(a, n, n) === a;
    }
    return try_it(1+math_floor(math_random() * (n-1)));
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

function square(n) {
    return n*n;
}

function is_even(n) {
    return n%2 === 0;
}

