import { display } from 'sicp';

display(euler(20));

function euler(n) {
    function d(x) {
        if (x < 3) {
            return x;
        }
        const e = 2*(x+1)/3;
        if (is_even(e)) {
            return e;
        }
        return 1;
    }
    return 2+cont_frac(x => 1, d, n);
}

function cont_frac(n, d, k) {
    function iter(k, r) {
        if (k === 1) {
            return n(k)/(d(k) + r);
        }
        return iter(k-1, n(k) / (d(k) + r))
    }
    return iter(k, 0);
}

function is_even(n) {
    return n%2 === 0;
}
