import { display } from 'sicp';

const zero = f => x => x;
const one = f => x => f(x);
const two = f => x => f(f(x));

display(plus(one, two)(n => n+1)(0));

function add_1(n) {
    return f => x => f(n(f)(x));
}

function plus(a, b) {
    return f => x => a(f)(b(f)(x));
}
