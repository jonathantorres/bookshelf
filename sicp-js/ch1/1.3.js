import { display } from 'sicp';

display(f(1, 2, 3)); // 13
display(f(3, 2, 1)); // 13
display(f(2, 1, 3)); // 13
display(f(1, 3, 2)); // 13
display(f(4, 7, 2)); // 65

function f(a, b, c) {
    return (a <= b && a <= c)
        ? sum_squares(b, c)
        : (b <= a && b <= c)
        ? sum_squares(a, c)
        : sum_squares(a, b);
}
  
function sum_squares(a, b) {
    return square(a) + square(b);
}

function square(x) {
    return x * x;
}
