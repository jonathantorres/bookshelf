import {
    pair, head, tail, display, list, is_string, is_null,
    append, error, equal, length, is_undefined
} from 'sicp';

// a few tests to make sure that it works
const tl = list(3);
const t1 = make_term(1, -5);
const t2 = make_term(2, 5);
const t3 = make_term(3, 4);

display(
    adjoin_term(t3,
        adjoin_term(t2,
            adjoin_term(t1, tl))));

// first_term needs to be re-written to also include the order
// based on the length of the term_list
function first_term(term_list) {
    return make_term(length(term_list) - 1, head(term_list));
}

// changes on adjoin-term based on this new representation
function adjoin_term(term, term_list) {
    return is_equal_to_zero(coeff(term))
           ? term_list
           : order(term) === length(term_list)
           ? pair(coeff(term), term_list)
           : adjoin_term(term, pair(0, term_list));
}

// using this procedure since we are not dealing with the packages in this exercise
function is_equal_to_zero(x) {
    return x === 0;
}

// everything else stays the same
const the_empty_termlist = null;

function variable(p) { return head(p); }
function term_list(p) { return tail(p); }
function is_variable(x) { return is_string(x); }

function is_same_variable(v1, v2) {
    return is_variable(v1) && is_variable(v2) && v1 === v2;
}

function rest_terms(term_list) {
    return tail(term_list);
}

function is_empty_termlist(term_list) {
    return is_null(term_list);
}

function make_term(order, coeff) {
    return list(order, coeff);
}

function order(term) {
    return head(term);
}

function coeff(term) {
    return head(tail(term));
}
