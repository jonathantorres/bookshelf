import { display } from 'sicp';

display(smallest_divisor(199));
display(smallest_divisor(1999));
display(smallest_divisor(19999));

function smallest_divisor(n) {
    return find_divisor(n, 2);
}

function find_divisor(n, test_divisor) {
    if (square(test_divisor) > n) {
        return n;
    }
    if (divides(test_divisor, n)) {
        return test_divisor;
    }
    return find_divisor(n, test_divisor+1);
}

function divides(a, b) {
    return b%a === 0;
}

function square(n) {
    return n*n;
}
