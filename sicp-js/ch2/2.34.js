import {
    display, display_list, list, head,
    tail, is_null, pair, is_pair, accumulate
} from 'sicp';

display(horner_eval(2, list(1, 3, 0, 5, 0, 1)));

function horner_eval(x, coefficient_sequence) {
    return accumulate((this_coeff, higher_terms) => this_coeff + x * higher_terms,
                      0,
                      coefficient_sequence);
}
