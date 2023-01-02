import { display } from 'sicp';

display(integral(cube, 0, 1, 100));
display(integral(cube, 0, 1, 1000));

display(simp(cube, 0, 1, 100));
display(simp(cube, 0, 1, 1000));

function simp(f, a, b, n) {
    let h = (b - a) / n;
    function si_term(x) {
        let r = 1;

        if (x > 0 && x < n) {
            if (is_even(x)) {
                r = 2;
            } else {
                r = 4;
            }
        }
        return r * f(a + (x * h));
    }
    function si_next(x) {
        return x+1;
    }
    return h/3 * sum(si_term, 0, si_next, n);
}

function integral(f, a, b, dx) {
    function add_dx(x) {
        return x + dx;
    }
    return sum(f, a + dx / 2, add_dx, b) * dx;
}

function sum(term, a, next, b) {
    if (a > b) {
        return 0;
    }
    return term(a) + sum(term, next(a), next, b);
}

function cube(n) {
    return n*n*n;
}

function is_even(n) {
    return n%2 === 0;
}

