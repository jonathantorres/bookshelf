import { display } from 'sicp';

display(approx_cubic(1, -4, 0));

function approx_cubic(a, b, c) {
    return newtons_method(cubic(a, b, c), 1);
}

function newton_transform(g) {
    return x => x - g(x) / deriv(g)(x);
}

function newtons_method(g, guess) {
    return fixed_point(newton_transform(g), guess);
}

function cubic(a, b, c) {
    return x => cube(x) + a*square(x) + b*x + c;
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

function deriv(g) {
    const dx = 0.00001;
    return x => (g(x + dx) - g(x)) / dx;
}

function abs(x) {
    return x >= 0 ? x : - x;
}

function square(x) {
    return x * x;
}

function cube(x) {
    return x * x * x;
}

