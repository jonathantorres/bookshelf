import { display } from 'sicp';

display(repeated(square, 2)(5));
display(repeated(inc, 10)(10));

function repeated(f, n) {
    function rep(x, n) {
        if (n === 0) {
            return x;
        }
        if (is_even(n)) {
            return rep(compose(f, f)(x), n-2);
        } else {
            return rep(f(x), n-1);
        }
    }
    return x => f(rep(x, n-1));
}

function compose(f, g) {
    return x => f(g(x));
}

function square(n) {
    return n*n;
}

function inc(n) {
    return n+1;
}

function is_even(n) {
    return n%2 === 0;
}

