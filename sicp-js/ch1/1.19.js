import { display } from 'sicp';

for (let i = 0; i <= 10; i++) {
    console.log(fib(i));
}

function fib(n) {
    return fib_iter(1, 0, 0, 1, n);
    // return fib2(n);
}

function fib_iter(a, b, p, q, count) {
    return count === 0
           ? b
           : is_even(count)
           ? fib_iter(a,
                      b,
                      square(p) + square(q),    // compute p'
                      2 * p * q + square(q),    // compute q'
                      count / 2)
           : fib_iter(b * q + a * q + a * p,
                      b * p + a * q,
                      p,
                      q,
                      count - 1);
}

function fib2(n) {
    if (n === 0) {
        return 0;
    }
    if (n === 1) {
        return 1;
    }
    return fib2(n-1) + fib2(n-2);
}

function is_even(n) {
    return n%2 === 0;
}

function square(n) {
    return n*n;
}
