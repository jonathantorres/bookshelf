import { display } from 'sicp';

display(sum(noop, 1, inc, 10));
display(sum(cube, 1, inc, 10));

function sum(term, a, next, b) {
    function iter(a, result) {
        return a > b
            ? result
            : iter(next(a), term(a) + result);
    }
    return iter(a, 0);
}

function cube(n) {
    return n*n*n;
}

function inc(n) {
    return n+1;
}

function noop(n) {
    return n;
}
