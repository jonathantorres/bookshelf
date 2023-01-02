import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate, append, filter
} from 'sicp';

// list(list(5, 3, 2), list(5, 4, 1), list(6, 3, 1))
display_list(ord_triples(6, 10));

function ord_triples(n, s) {
    return filter(l => {
        if (accumulate(sum, 0, l) === s) {
            return true;
        }
        return false;
    }, flatmap(i => {
        return flatmap(j => {
            return map(k => {
                return list(i, j, k);
            }, enumerate_interval(1, j-1));
        }, enumerate_interval(1, i-1));
    }, enumerate_interval(1, n)));
}

function flatmap(f, seq) {
    return accumulate(append, null, map(f, seq));
}

function enumerate_interval(low, high) {
    return low > high
           ? null
           : pair(low, enumerate_interval(low + 1, high));
}

function sum(a, b) {
    return a+b;
}
