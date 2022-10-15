import { display } from 'sicp';

// a and b will be added if b >= 0
// otherwise they will be substracted

display(a_plus_abs_b(1, 2));
display(a_plus_abs_b(1, 0));

function a_plus_abs_b(a, b) {
    return (b >= 0 ? plus : minus)(a, b);
}

function plus(a, b) {
    return a + b;
}

function minus(a, b) {
    return a - b;
}
