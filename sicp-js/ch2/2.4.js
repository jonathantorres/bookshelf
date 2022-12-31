import { display } from 'sicp';

const p = pair(1, 2);

display(head(p));
display(tail(p));

function pair(x, y) {
    return m => m(x, y);
}

function head(z) {
    return z((p, q) => p);
}

function tail(z) {
    return z((p, q) => q);
}
