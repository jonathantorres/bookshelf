import {display, math_abs} from 'sicp';

// What's gonna happen is that this code will run the loop forever
// ultimately crashing the program, since the recursive call to sqrt_iter()
// will be evaluated first by the conditional() function

display(sqrt(9));

function conditional(predicate, then_clause, else_clause) {
    return predicate ? then_clause : else_clause;
}

function sqrt(x) {
    return sqrt_iter(1, x);
}

function sqrt_iter(guess, x) {
    return conditional(is_good_enough(guess, x),
                        guess,
                        sqrt_iter(improve(guess, x), x));
    // return is_good_enough(guess, x)
    //     ? guess
    //     : sqrt_iter(improve(guess, x), x);
}

function is_good_enough(guess, x) {
    return math_abs(square(guess) - x) < 0.001;
}

function improve(guess, x) {
    return average(guess, x/guess);
}

function average(x, y) {
    return (x+y) / 2;
}

function square(x) {
    return x*x;
}
