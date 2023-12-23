import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan
} from 'sicp';

const operation_table = make_table();
const get = operation_table("lookup");
const put = operation_table("insert");

install_javascript_number_package();
install_rational_package();
install_polynomial_package();

// create the polynomials p1, p2 and p3
const p1 = make_polynomial("x", list(list(2, 1), list(1, -2), list(0, 1)));
const p2 = make_polynomial("x", list(list(2, 11), list(0, 7)));
const p3 = make_polynomial("x", list(list(1, 13), list(0, 5)));

// create the products q1 and q2
const q1 = mul(p1, p2);
const q2 = mul(p1, p3);

// the gcd is not the same as p1, the remainder terms
// have non-integers as coefficients
display_list(greatest_common_divisor(q1, q2));

function install_polynomial_package() {
    // internal functions
    function make_poly(variable, term_list) {
        return pair(variable, term_list);
    }
    function make_term(order, coeff) {
       return list(order, coeff);
    }
    function variable(p) { return head(p); }
    function term_list(p) { return tail(p); }
    function first_term(term_list) {
        return head(term_list);
    }

    const the_empty_termlist = null;
    function rest_terms(term_list) {
        return tail(term_list);
    }
    function is_empty_termlist(term_list) {
        return is_null(term_list);
    }
    function order(term) {
        return head(term);
    }
    function coeff(term) {
        return head(tail(term));
    }
    function is_variable(x) { return is_string(x); }

    function is_same_variable(v1, v2) {
        return is_variable(v1) && is_variable(v2) && v1 === v2;
    }

    function adjoin_term(term, term_list) {
        return is_equal_to_zero(coeff(term))
               ? term_list
               : pair(term, term_list);
    }
    
    // polynomial addition
    function add_poly(p1, p2) {
        return is_same_variable(variable(p1), variable(p2))
               ? make_poly(variable(p1),
                           add_terms(term_list(p1),
                                     term_list(p2)))
               : error(list(p1, p2), "polys not in same var -- add_poly");
    }

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
                                           add(coeff(t1),
                                               coeff(t2))),
                                 add_terms(rest_terms(L1),
                                           rest_terms(L2)));
        }
    }
    
    // polynomial subtraction
    function sub_poly(p1, p2) {
        return is_same_variable(variable(p1), variable(p2))
               ? make_poly(variable(p1),
                           sub_terms(term_list(p1),
                                     term_list(p2)))
               : error(list(p1, p2), "polys not in same var -- sub_poly");
    }
    
    function sub_terms(L1, L2) {
        return add_terms(L1, negate_terms(L2));
    }
    
    // polynomial multiplication
    function mul_poly(p1, p2) {
        return is_same_variable(variable(p1), variable(p2))
               ? make_poly(variable(p1),
                           mul_terms(term_list(p1),
                                     term_list(p2)))
               : error(list(p1, p2), "polys not in same var -- mul_poly");
    }

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
                                 mul(coeff(t1), coeff(t2))),
                       mul_term_by_all_terms(t1, rest_terms(L)));
        }
    }

    // polynomial division
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
    
    // gcd for polynomials
    function gcd_poly(p1, p2) {
        return is_same_variable(variable(p1), variable(p2))
               ? make_poly(variable(p1),
                           gcd_terms(term_list(p1),
                                     term_list(p2)))
               : error(list(p1, p2), "polys not in same var -- gcd_poly");
    }
    
    function gcd_terms(a, b) {
        return is_empty_termlist(b)
            ? a
            : gcd_terms(b, remainder_terms(a, b));
    }
    
    function remainder_terms(L1, L2) {
        return head(tail(div_terms(L1, L2)));
    }
    
    function negate_terms(tl) {
        if (is_empty_termlist(tl)) {
            return the_empty_termlist;
        } else {
            const first = first_term(tl);
            const rest = rest_terms(tl);
            return adjoin_term(make_term(order(first), neg(coeff(first))), negate_terms(rest));
        }
    }

    // interface to rest of the system
    function tag(p) {
        return attach_tag("polynomial", p);
    }
    put("add", list("polynomial", "polynomial"),
        (p1, p2) => tag(add_poly(p1, p2)));
    put("sub", list("polynomial", "polynomial"),
        (p1, p2) => tag(sub_poly(p1, p2)));
    put("mul", list("polynomial", "polynomial"),
        (p1, p2) => tag(mul_poly(p1, p2)));
    put("div", list("polynomial", "polynomial"),
        (p1, p2) => tag(div_poly(p1, p2)));
    put("greatest_common_divisor", list("polynomial", "polynomial"),
        (p1, p2) => tag(gcd_poly(p1, p2)));
    put("make", "polynomial",
        (variable, terms) => tag(make_poly(variable, terms)));

    return "done";
}

function make_polynomial(variable, terms) {
    return get("make", "polynomial")(variable, terms);
}

// rational package
function install_rational_package() {
    // internal functions
    function numer(x) { return head(x); }
    function denom(x) { return tail(x); }
    function make_rat(n, d) {
        return pair(n, d);
    }
    function add_rat(x, y) {
        return make_rat(add(mul(numer(x), denom(y)), mul(numer(y), denom(x))),
                        mul(denom(x), denom(y)));
    }
    function sub_rat(x, y) {
        return make_rat(sub(mul(numer(x), denom(y)), mul(numer(y), denom(x))),
                        mul(denom(x), denom(y)));
    }
    function mul_rat(x, y) {
        return make_rat(mul(numer(x), numer(y)),
                        mul(denom(x), denom(y)));
    }
    function div_rat(x, y) {
        return make_rat(mul(numer(x), denom(y)),
                        mul(denom(x), numer(y)));
    }
    // interface to rest of the system
    function tag(x) {
        return attach_tag("rational", x);
    }
    put("add", list("rational", "rational"),
        (x, y) => tag(add_rat(x, y)));
    put("sub", list("rational", "rational"),
        (x, y) => tag(sub_rat(x, y)));
    put("mul", list("rational", "rational"),
        (x, y) => tag(mul_rat(x, y)));
    put("div", list("rational", "rational"),
        (x, y) => tag(div_rat(x, y)));
    put("make", "rational",
        (n, d) => tag(make_rat(n, d)));
    return "done";
}

function make_rational(n, d) {
    return get("make", "rational")(n, d);
}

// javascript number package
function install_javascript_number_package() {
    put("add", list("javascript_number", "javascript_number"),
        (x, y) => x + y);
    put("sub", list("javascript_number", "javascript_number"),
        (x, y) => x - y);
    put("mul", list("javascript_number", "javascript_number"),
        (x, y) => x * y);
    put("div", list("javascript_number", "javascript_number"),
        (x, y) => x / y);
    put("neg", list("javascript_number"),
        (x) => x * -1);
    put("is_equal", list("javascript_number", "javascript_number"),
        (x, y) => x === y);
    put("is_equal_to_zero", list("javascript_number"),
        (x) => x === 0);
    put("greatest_common_divisor", list("javascript_number", "javascript_number"),
        (x, y) => gcd(x, y));

    return "done";
}

function add(x, y) { return apply_generic("add", list(x, y)); }

function sub(x, y) { return apply_generic("sub", list(x, y)); }

function mul(x, y) { return apply_generic("mul", list(x, y)); }

function div(x, y) { return apply_generic("div", list(x, y)); }

function is_equal(x, y) { return apply_generic("is_equal", list(x, y)); }

function is_equal_to_zero(x) { return apply_generic("is_equal_to_zero", list(x)); }

function neg(x) { return apply_generic("neg", list(x)); }

function greatest_common_divisor(x, y) { return apply_generic("greatest_common_divisor", list(x, y)); }

function attach_tag(type_tag, contents) {
    return type_tag === "javascript_number"
        ? contents
        : pair(type_tag, contents);
}

function type_tag(datum) {
    return is_number(datum)
        ? "javascript_number"
        : is_pair(datum)
        ? head(datum)
        : error(datum, "bad tagged datum -- type_tag");
}

function contents(datum) {
    return is_number(datum)
        ? datum
        : is_pair(datum)
        ? tail(datum)
        : error(datum, "bad tagged datum -- contents");
}

function apply(fun, args) {
    return apply_in_underlying_javascript(fun, args);
}

function apply_generic(op, args) {
    const type_tags = map(type_tag, args);
    const fun = get(op, type_tags);

    return !is_undefined(fun)
           ? apply_in_underlying_javascript(fun, map(contents, args))
           : error(list(op, type_tags),
                   "no method for these types -- apply_generic");
}

function gcd(a, b) {
    return b === 0
        ? a
        : gcd(b, a % b);
}

// operation_table, put and get
// from chapter 3 (section 3.3.3)
function assoc(key, records) {
    return is_null(records)
           ? undefined
           : equal(key, head(head(records)))
           ? head(records)
           : assoc(key, tail(records));
}

function make_table() {
    const local_table = list("*table*");
    function lookup(key_1, key_2) {
        const subtable = assoc(key_1, tail(local_table));
        if (is_undefined(subtable)) {
            return undefined;
        } else {
            const record = assoc(key_2, tail(subtable));
            return is_undefined(record)
                   ? undefined
                   : tail(record);
        }
    }
    function insert(key_1, key_2, value) {
        const subtable = assoc(key_1, tail(local_table));
        if (is_undefined(subtable)) {
            set_tail(local_table,
                     pair(list(key_1, pair(key_2, value)),
                          tail(local_table)));
        } else {
            const record = assoc(key_2, tail(subtable));
            if (is_undefined(record)) {
                set_tail(subtable,
                         pair(pair(key_2, value), tail(subtable)));
            } else {
                set_tail(record, value);
            }
        }
    }
    function dispatch(m) {
        return m === "lookup"
               ? lookup
               : m === "insert"
               ? insert
               : error(m, "unknown operation -- table");
    }
    return dispatch;
}
