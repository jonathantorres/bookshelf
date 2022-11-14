import { display, math_abs, math_log } from 'sicp';

display(fixed_point(x => math_log(1000)/math_log(x), 2));

function fixed_point(f, first_guess) {
    const tolerance = 0.00001;
    function close_enough(x, y) {
        return math_abs(x - y) < tolerance;
    }
    function try_with(guess) {
        const next = f(guess);
        display(next, "next:");
        return close_enough(guess, next)
               ? next
               : try_with(next);
    }
    return try_with(first_guess);
}
