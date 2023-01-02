import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate, append, filter
} from 'sicp';

display_list(prime_sum_pairs(6));

function prime_sum_pairs(n) {
    return map(make_pair_sum, filter(is_prime_sum, unique_pairs(n)));
}

function unique_pairs(n) {
    return accumulate(append, null, map(i => {
        return map(j => list(i, j), enumerate_interval(1, i-1));
    }, enumerate_interval(1, n)));
}

function enumerate_interval(low, high) {
    return low > high
           ? null
           : pair(low, enumerate_interval(low + 1, high));
}

function make_pair_sum(pair) {
    return list(head(pair), head(tail(pair)),
                head(pair) + head(tail(pair)));
}

function is_prime_sum(pair) {
    return is_prime(head(pair) + head(tail(pair)));
}

function flatmap(f, seq) {
    return accumulate(append, null, map(f, seq));
}

function find_divisor(n, test_divisor) {
    return square(test_divisor) > n
           ? n
           : divides(test_divisor, n)
           ? test_divisor
           : find_divisor(n, test_divisor + 1);
}

function divides(a, b) {
    return b % a === 0;
}

function is_prime(n) {
    return n === smallest_divisor(n);
}

function square(x) {
    return x * x;
}

function smallest_divisor(n) {
    return find_divisor(n, 2);
}

