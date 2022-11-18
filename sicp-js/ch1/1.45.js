import { display, math_floor, math_log2 } from 'sicp';

display(nroots(5, 32));

function nroots(n, x) {
    return fixed_point(
        repeated(average_damp, math_floor(math_log2(n)))(y => x/fast_expt(y, n-1)),
        1
    );
}

function repeated(f, n) {
    if (n === 0) {
        return x => x;
    }
    return compose(f, repeated(f, n-1));
}

function compose(f, g) {
    return x => f(g(x));
}

function fixed_point(f, first_guess) {
    const tolerance = 0.00001;
    function close_enough(x, y) {
        return abs(x - y) < tolerance;
    }
    function try_with(guess) {
        const next = f(guess);
        return close_enough(guess, next)
               ? next
               : try_with(next);
    }
    return try_with(first_guess);
}

function fast_expt(b, n) {
    return n === 0
           ? 1
           : is_even(n)
           ? square(fast_expt(b, n / 2))
           : b * fast_expt(b, n - 1);
}

function abs(x) {
    return x >= 0 ? x : - x;
}

function average(x, y) {
    return (x + y) / 2;
}

function average_damp(f) {
    return x => average(x, f(x));
}

function square(x) {
    return x * x;
}

function is_even(n) {
    return n % 2 === 0;
}
