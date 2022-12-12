import {
    display, display_list, list, head,
    tail, is_null, pair, is_pair, accumulate
} from 'sicp';

const x = list(1,2,3,4);
const y = list(5,6,7,8);

display_list(map(n => n*n, x));
display_list(append(x, y));
display_list(length(x));

function map(f, sequence) {
    return accumulate((x, y) => pair(f(x), y), null, sequence);
}

function append(seq1, seq2) {
    return accumulate(pair, seq2, seq1);
}

function length(sequence) {
    return accumulate((x, y) => y+1, 0, sequence);
}

