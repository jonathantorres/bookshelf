import {display, math_abs, math_round} from 'sicp';

display(sqrt(1));
display(sqrt(2));
display(sqrt(4));
display(sqrt(9));
display(sqrt(10000)); // 10 thousand
display(sqrt(100000)); // 100 thousand
display(sqrt(1000000)); // 1 million
display(sqrt(100000000)); // 100 million
display(sqrt(1000000000)); // 1 billion

function sqrt(x) {
    return sqrt_iter(1, x);
}

function sqrt_iter(guess, x) {
    return is_good_enough(guess, x)
        ? guess
        : sqrt_iter(improve(guess, x), x);
}

function is_good_enough(guess, x) {
    return math_round(square(guess)) == x;
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
