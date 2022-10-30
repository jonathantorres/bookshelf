import { display } from 'sicp';

display(f(5));
display(fi(5));

// recursive process
function f(n) {
    if (n < 3) {
        return n;
    }
    return f(n-1) + 2*f(n-2) + 3*f(n-3);
}

// iterative process
function fi(n) {
    if (n < 3) {
        return n;
    }

    return f_iter(2, 1, 0, n);
}

function f_iter(a, b, c, n) {
    if (n == 0) {
        return c;
    }

    return f_iter(
        a + 2*b + 3*c,
        a,
        b,
        n-1
    );
}

