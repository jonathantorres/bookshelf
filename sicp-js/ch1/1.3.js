import { display } from 'sicp';

display(f(1, 2, 3)); // 13
display(f(3, 2, 1)); // 13
display(f(2, 1, 3)); // 13
display(f(1, 3, 2)); // 13
display(f(4, 7, 2)); // 65

function f(a, b, c) {
    let lar1 = a;
    let lar2 = a;

    if (b > a && b > c) {
        lar1 = b;
    } else if (c > a && c > b) {
        lar1 = c;
    }

    if (lar1 == a) {
        lar2 = b > c ? b : c;
    } else if (lar1 == b) {
        lar2 = a > c ? a : c;
    } else {
        lar2 = a > b ? a : b;
    }

    return square(lar1) + square(lar2);
}

function square(x) {
    return x * x;
}
