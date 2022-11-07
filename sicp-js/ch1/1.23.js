import { display, get_time } from 'sicp';

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
timed_prime_test(1000037);

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
    return n === smallest_divisor(n);
}

function smallest_divisor(n) {
    return find_divisor(n, 2);
}

function find_divisor(n, test_divisor) {
    if (square(test_divisor) > n) {
        return n;
    }
    if (divides(test_divisor, n)) {
        return test_divisor;
    }
    return find_divisor(n, next(test_divisor));
}

function next(n) {
    if (n === 2) {
        return 3;
    }
    return n+2;
}

function divides(a, b) {
    return b%a === 0;
}

function square(n) {
    return n*n;
}
