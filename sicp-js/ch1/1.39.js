import { display, math_PI } from 'sicp';

display(tan_cf(math_PI, 14));

function tan_cf(x, k) {
    return cont_frac(
        n => n === 1 ? x : - x * x,
        n => 2 * n - 1,
        k
    );
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

