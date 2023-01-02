import { display, math_floor, math_random } from 'sicp';

display(sum_prime_squares(1, 10)); // 87
display(prime_products(10)); // 189

function prime_products(n) {
    function filter(x) {
        return gcd(x, n) === 1;
    }
    function times(a, b) {
        return a*b;
    }
    function inc(x) {
        return x+1;
    }
    function noop(x) {
        return x;
    }
    return filtered_accumulate(times, 1, noop, 1, inc, n, filter);
}

function sum_prime_squares(a, b) {
    function filter(n) {
        return is_prime(n);
    }
    function sum(a, b) {
        return a + b;
    }
    function inc(n) {
        return n+1;
    }
    function square(n) {
        return n*n;
    }
    return filtered_accumulate(sum, 0, square, a, inc, b, filter);
}

function filtered_accumulate(combiner, null_value, term, a, next, b, filter) {
    if (a > b) {
        return null_value;
    }
    if (!filter(a)) {
        return filtered_accumulate(combiner, null_value, term, next(a), next, b, filter);
    }
    return combiner(
        term(a),
        filtered_accumulate(combiner, null_value, term, next(a), next, b, filter)
    );
}

function is_prime(n) {
    return fast_is_prime(n, 10);
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

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
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
