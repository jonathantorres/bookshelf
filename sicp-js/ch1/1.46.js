import { display, math_cos } from 'sicp';

display(sqrt(49));
display(fixed_point(math_cos, 1));

function iterative_improve(is_good_enough, improve) {
    function try_with(guess) {
        if (is_good_enough(guess)) {
            return guess;
        }
        return try_with(improve(guess));
    }
    return try_with;
}

function sqrt(n) {
    const tol = 0.001;
    function good_enough(guess) {
        return abs(square(guess)-n) < tol;
    }
    function improve(guess) {
       return average(guess, n/guess);
    }
   return iterative_improve(good_enough, improve)(1);
}

function fixed_point(f, first_guess) {
    const tol = 0.00001;
    function close_enough(x) {
        return abs(x - f(x)) < tol;
    }
    return iterative_improve(close_enough, f)(first_guess);
}

function abs(x) {
    return x >= 0 ? x : - x;
}

function average(x, y) {
    return (x + y) / 2;
}

function square(x) {
    return x * x;
}

function is_even(n) {
    return n % 2 === 0;
}

