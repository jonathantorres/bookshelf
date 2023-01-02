import { display } from 'sicp';

display(product(noop, 1, inc, 5));
display(product_iter(noop, 1, inc, 5));
display(factorial(10));
display(pi_approx(10));

// product: recursive process
function product(term, a, next, b) {
    if (a > b) {
        return 1;
    }
    return term(a) * product(term, next(a), next, b);
}

// product: iterative process
function product_iter(term, a, next, b) {
    function iter(a, res) {
       if (a > b)  {
           return res;
       }
       return iter(next(a), term(a) * res);
    }
    return iter(a, 1);
}

// factorial using the product process
function factorial(n) {
    return product(noop, 1, inc, n);
}

// pi using product
function pi_approx(x) {
    function pi_next(n) {
        return n+1;
    }

    function pi_term(n) {
        if (is_even(n)) {
            return (n+2)/(n+1);
        } else {
            return (n+1)/(n+2);
        }
    }
    return 4 * product(pi_term, 1, pi_next, x);
}

function is_even(n) {
    return n%2 === 0;
}

function inc(n) {
    return n+1;
}

function noop(n) {
    return n;
}

