import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan
} from 'sicp';

// to keep things simple, the coefficients are represented as primitive numbers
const p1 = make_poly("x", list(make_term(100, 1), make_term(2, 2), make_term(0, 1)));
const p2 = make_poly("x", list(make_term(55, 5), make_term(3, 2), make_term(1, 1)));

display_list(div_poly(p1, p2));

// function to divide polynomials
function div_poly(p1, p2) {
    if (is_same_variable(variable(p1), variable(p2))) {
        const result = div_terms(term_list(p1), term_list(p2));
        const quotient = head(result);
        const remainder = head(tail(result));
        return list(make_poly(variable(p1), quotient), make_poly(variable(p1), remainder));
    } else {
        return error("Polynomials not in same var - div_poly", list(p1, p2));
    }
}

function div_terms(L1, L2) {
    if (is_empty_termlist(L1)) {
        return list(the_empty_termlist, the_empty_termlist);
    } else {
        const t1 = first_term(L1);
        const t2 = first_term(L2);
        if (order(t2) > order(t1)) {
            return list(the_empty_termlist, L1);
        } else {
            const new_c = coeff(t1) / coeff(t2);
            const new_o = order(t1) - order(t2);
            const rest_of_result = div_terms(
                sub_terms(L1, mul_term_by_all_terms(make_term(new_o, new_c), L2)),
                L2
            );
            return list(adjoin_term(make_term(new_o, new_c), head(rest_of_result)), head(tail(rest_of_result)));
        }
    }
}

// polynomial addition
function add_poly(p1, p2) {
    return is_same_variable(variable(p1), variable(p2))
           ? make_poly(variable(p1),
                       add_terms(term_list(p1),
                                 term_list(p2)))
           : error(list(p1, p2), "polys not in same var -- add_poly");
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

// subtracting terms
function sub_terms(L1, L2) {
    return add_terms(L1, negate_terms(L2));
}

function negate_terms(tl) {
    if (is_empty_termlist(tl)) {
        return the_empty_termlist;
    } else {
        const first = first_term(tl);
        const rest = rest_terms(tl);
        return adjoin_term(make_term(order(first), coeff(first) * -1), negate_terms(rest));
    }
}

// polynomial multiplication
function mul_poly(p1, p2) {
    return is_same_variable(variable(p1), variable(p2))
           ? make_poly(variable(p1),
                       mul_terms(term_list(p1),
                                 term_list(p2)))
           : error(list(p1, p2), "polys not in same var -- mul_poly");
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

function adjoin_term(term, term_list) {
    return coeff(term) === 0
           ? term_list
           : pair(term, term_list);
}
