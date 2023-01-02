import { display } from 'sicp';

display(sum(noop, 1, inc, 5)); // 15
display(product(noop, 1, inc, 5)); // 120

// accumulate: recursive process
function accumulate(combiner, null_value, term, a, next, b) {
    if (a > b) {
        return null_value;
    }
    return combiner(term(a), accumulate(combiner, null_value, term, next(a), next, b));
}

// accumulate: iterative process
function accumulate_iter(combiner, null_value, term, a, next, b) {
    function iter(a, res) {
        if (a > b) {
            return res;
        }
        return iter(next(a), combiner(term(a), res));
    }
    return iter(a, null_value);
}

function product(term, a, next, b) {
    function combiner(a, b) {
        return a*b;
    }
    return accumulate(combiner, 1, term, a, next, b);
}

function sum(term, a, next, b) {
    function combiner(a, b) {
        return a+b;
    }
    return accumulate(combiner, 0, term, a, next, b);
}

function noop(n) {
    return n;
}

function inc(n) {
    return n+1;
}

