import {display, math_abs} from 'sicp';

display(cube_root(8));
display(cube_root(20));
display(cube_root(64));
display(cube_root(1000)); // 1,000
display(cube_root(100000)); // 100,000
display(cube_root(1000000)); // 1,000,000


function cube_root(x) {
    return cube_root_iter(1, x);
}

function cube_root_iter(guess, x) {
    return is_good_enough(guess, x)
        ? guess
        : cube_root_iter(improve(guess, x), x);
}

function is_good_enough(guess, x) {
    return math_abs(cube(guess) - x) < 0.001;
}

function improve(guess, x) {
    return ((x/square(guess)) + 2*guess)/3;
}

function cube(x) {
    return x*x*x;
}

function square(x) {
    return x*x;
}
