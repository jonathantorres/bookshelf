import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan
} from 'sicp';

// to keep things simple, the coefficients are represented as primitive numbers
const p1 = make_poly("x", list(make_term(100, 1), make_term(2, 2), make_term(0, 1)));
const p2 = make_poly("y", list(make_term(55, 5), make_term(3, 2), make_term(1, 1)));

display_list(add_poly(p1, p2));
display_list(mul_poly(p1, p2));

// rewrittern polynomial addition function
function add_poly(p1, p2) {
    const v1 = variable(p1);
    const v2 = variable(p2);
    const t1 = term_list(p1);
    const t2 = term_list(p2);
    
    if (is_same_variable(v1, v2)) {
        return make_poly(v1, add_terms(t1, t2));
    } else if (is_before(v1, v2)) {
        return add_poly(p1, append_poly(v1, p2));
    } else {
        return add_poly(append_poly(v2, p1), p2);
    }
}

// rewritten polynomial multiplication function
function mul_poly(p1, p2) {
    const v1 = variable(p1);
    const v2 = variable(p2);
    const t1 = term_list(p1);
    const t2 = term_list(p2);
    
    if (is_same_variable(v1, v2)) {
        return make_poly(v1, mul_terms(t1, t2));
    } else if (is_before(v1, v2)) {
        return mul_poly(p1, append_poly(v1, p2));
    } else {
        return mul_poly(append_poly(v2, p1), p2);
    }
}

function adjoin_term(term, term_list) {
    if (is_number(coeff(term)) && coeff(term) === 0) {
        return term_list;
    } else if (is_empty_termlist(term_list)) {
        return term_list;
    } else if (order(head(term_list)) > order(term)) {
        return pair(head(term_list), adjoin_term(term, tail(term_list)));
    } else if (order(head(term_list)) === order(term)) {
        return adjoin_term(
                make_term(order(term), coeff(term) + coeff(head(term_list))),
                tail(term_list));
    } else {
        return pair(term, term_list);
    }
}


function is_before(v1, v2) {
    return v1 < v2;
}

function append_poly(variable, num) {
    return make_poly(variable, adjoin_term(make_term(0, num), the_empty_termlist));
}

// adding terms
function add_terms(L1, L2) {
    if (is_empty_termlist(L1)) {
      return L2;
    } else if (is_empty_termlist(L2)) {
      return L1;
    } else {
        const t1 = first_term(L1);
        const t2 = first_term(L2);
        return order(t1) > order(t2)
               ? adjoin_term(t1, add_terms(rest_terms(L1), L2))
               : order(t1) < order(t2)
               ? adjoin_term(t2, add_terms(L1, rest_terms(L2)))
               : adjoin_term(make_term(order(t1),
                                       coeff(t1) + coeff(t2)),
                             add_terms(rest_terms(L1),
                                       rest_terms(L2)));
    }
}

// multiplying terms
function mul_terms(L1, L2) {
    return is_empty_termlist(L1)
           ? the_empty_termlist
           : add_terms(mul_term_by_all_terms(
                                 first_term(L1), L2),
                       mul_terms(rest_terms(L1), L2));
}

function mul_term_by_all_terms(t1, L) {
    if (is_empty_termlist(L)) {
        return the_empty_termlist;
    } else {
        const t2 = first_term(L);
        return adjoin_term(
                   make_term(order(t1) + order(t2),
                             coeff(t1) * coeff(t2)),
                   mul_term_by_all_terms(t1, rest_terms(L)));
    }
}

function make_poly(variable, term_list) {
    return pair(variable, term_list);
}

function is_variable(x) { return is_string(x); }

function is_same_variable(v1, v2) {
    return is_variable(v1) && is_variable(v2) && v1 === v2;
}

const the_empty_termlist = null;
function variable(p) { return head(p); }
function term_list(p) { return tail(p); }

function first_term(term_list) {
    return head(term_list);
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
