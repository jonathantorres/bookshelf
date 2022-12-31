import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan
} from 'sicp';

const operation_table = make_table();
const get = operation_table("lookup");
const put = operation_table("insert");

install_javascript_number_package();
install_polynomial_package();


// TODO: Implement this


function install_polynomial_package() {
    // internal functions
    // representation of poly
    function make_poly(variable, term_list) {
        return pair(variable, term_list);
    }
    function variable(p) { return head(p); }
    function term_list(p) { return tail(p); }

    // representation of terms and term lists
    function adjoin_term(term, term_list) {
        return is_equal_to_zero(coeff(term))
               ? term_list
               : pair(coeff(term), term_list);
    }
    const the_empty_termlist = null;
    function first_term(term_list) {
        return make_term(head(term_list), length(term_list)-1);
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

    function mul_poly(p1, p2) {
        return is_same_variable(variable(p1), variable(p2))
               ? make_poly(variable(p1),
                           mul_terms(term_list(p1),
                                     term_list(p2)))
               : error(list(p1, p2), "polys not in same var -- mul_poly");
    }

    function sub_poly(p1, p2) {
        return add_poly(p1, negate_poly(p2));
    }

    function negate_poly(p) {
        return tail(make_polynomial("x", map(negate_term, tail(p))));
    }

    function negate_term(t) {
        const n = -tail(coeff(t));
        return make_term(order(t), make_javascript_number(n));
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
    function div_poly(p1, p2) {
        if (is_same_variable(variable(p1), variable(p2))) {
            return map(term_list => make_poly(variable(p1), term_list),
                div_terms(term_list(p1), term_list(p2)));
        }
        return error("Polynomials not in same var - div_poly", list(p1, p2));
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
                const new_c = div(coeff(t1), coeff(t2));
                const new_o = order(t1) - order(t2);
                const term = list(new_o, new_c);
                const rest_of_result = div_terms(
                    sub_poly(L1, mul_terms(adjoin_term(term, the_empty_termlist), L2)),
                    L2
                );
                return list(adjoin_term(term, head(rest_of_result)), tail(rest_of_result));
            }
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
    put("make", "polynomial",
        (variable, terms) => tag(make_poly(variable, terms)));

    return "done";
}

// javascript number package
function install_javascript_number_package() {
    function tag(x) {
        return attach_tag("javascript_number", x);
    }
    put("add", list("javascript_number", "javascript_number"),
        (x, y) => tag(x + y));
    put("sub", list("javascript_number", "javascript_number"),
        (x, y) => tag(x - y));
    put("mul", list("javascript_number", "javascript_number"),
        (x, y) => tag(x * y));
    put("div", list("javascript_number", "javascript_number"),
        (x, y) => tag(x / y));
    put("is_equal_to_zero", list("javascript_number"), x => x === 0);
    put("make", "javascript_number", x => tag(x));

    return "done";
}

function add(x, y) { return apply_generic("add", list(x, y)); }

function sub(x, y) { return apply_generic("sub", list(x, y)); }

function mul(x, y) { return apply_generic("mul", list(x, y)); }

function div(x, y) { return apply_generic("div", list(x, y)); }

function is_equal_to_zero(x) {
    return apply_generic("is_equal_to_zero", list(x));
}

function make_javascript_number(n) {
    return get("make", "javascript_number")(n);
}

function make_polynomial(variable, terms) {
    return get("make", "polynomial")(variable, terms);
}

function is_variable(x) { return is_string(x); }

function is_same_variable(v1, v2) {
    return is_variable(v1) && is_variable(v2) && v1 === v2;
}

function attach_tag(type_tag, contents) {
    if (is_number(contents)) {
        return pair("javascript_number", contents);
    }
    return pair(type_tag, contents);
}

function type_tag(datum) {
    if (is_number(datum)) {
        return "javascript_number";
    }
    if (is_pair(datum)) {
        return head(datum);
    }

    return error(datum, "bad tagged datum -- type_tag");
}

function contents(datum) {
    if (is_number(datum)) {
        return datum;
    }
    if (is_pair(datum)) {
        return tail(datum);
    }

    return error(datum, "bad tagged datum -- contents");
}

function apply(fun, args) {
    return apply_in_underlying_javascript(fun, args);
}

function apply_generic(op, args) {
    const type_tags = map(type_tag, args);
    const fun = get(op, type_tags);

    return !is_undefined(fun)
           ? apply_in_underlying_javascript(fun, map(contents, args))
           : error(list(op, type_tags), "no method for these types -- apply_generic");
}

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}

function square(x) {
    return x * x;
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
