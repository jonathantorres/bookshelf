import { display } from 'sicp';

// the value of k must be 13 in order to get an approximation
// that is accurate to 4 decimal places

display(1/cont_frac(i => 1, i => 1, 13));
display(1/cont_frac_iter(i => 1, i => 1, 13));

function cont_frac(n, d, k) {
    if (k === 1) {
        return n(k)/d(k);
    }
    return n(k) / (d(k) + cont_frac(n, d, k-1));
}

function cont_frac_iter(n, d, k) {
    function iter(k, r) {
        if (k === 1) {
            return n(k)/(d(k) + r);
        }
        return iter(k-1, n(k) / (d(k) + r))
    }
    return iter(k, 0);
}

