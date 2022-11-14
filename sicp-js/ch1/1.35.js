import { display, math_abs } from 'sicp';

display(fixed_point(x => 1 + (1/x), 1));

function fixed_point(f, first_guess) {
    const tolerance = 0.00001;
    function close_enough(x, y) {
        return math_abs(x - y) < tolerance;
    }
    function try_with(guess) {
        const next = f(guess);
        return close_enough(guess, next)
               ? next
               : try_with(next);
    }
    return try_with(first_guess);
}

