import { display, get_time } from 'sicp';

search_for_primes(1000);
// search_for_primes(10000);
// search_for_primes(100000);
// search_for_primes(1000000);
// search_for_primes(10000000);

function search_for_primes(n) {
    let found = 0;
    while (found < 3) {
        if (is_even(n)) {
            n++;
            continue;
        }
        if (timed_prime_test(n) !== true) {
            found++;
            display("found " + n);
        }
        n++;
    }
}

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
    return find_divisor(n, test_divisor+1);
}

function is_even(n) {
    return n%2 === 0;
}

function divides(a, b) {
    return b%a === 0;
}

function square(n) {
    return n*n;
}
