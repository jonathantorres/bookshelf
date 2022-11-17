import { display } from 'sicp';

display(compose(square, inc)(6));

function compose(f, g) {
    return x => f(g(x));
}

function square(n) {
    return n*n;
}

function inc(n) {
    return n+1;
}

