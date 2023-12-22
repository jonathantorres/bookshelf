import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan
} from 'sicp';

const operation_table = make_table();
const get = operation_table("lookup");
const put = operation_table("insert");

install_sparse_package();
install_dense_package();
install_polynomial_package();

const p1 = make_sparse_poly("x", list(list(100,1), list(2, 2), list(0, 1)));
const p2 = make_dense_poly("x", list(0, 3, 4, 2));

display_list(add(p1, p1));
display_list(mul(p1, p1));
display_list(add(p2, p2));
display_list(mul(p2, p2));

function make_sparse_poly(variable, terms) {
    return get("make_sparse", "polynomial")(variable, terms);
}

function make_dense_poly(variable, terms) {
    return get("make_dense", "polynomial")(variable, terms);
}

// the polynomial package
function install_polynomial_package() {
    // imported functions from sparse and dense packages
    function make_sparse_poly(variable, terms) {
        return get("make_sparse_poly", "sparse")(variable, terms);
    }
    function make_dense_poly(variable, terms) {
        return get("make_dense_poly", "dense")(variable, terms);
    }

    // internal functions
    function make_term(order, coeff) {
        return list(order, coeff);
    }
    function order(term) {
        return head(term);
    }
    function coeff(term) {
        return head(tail(term));
    }
    function variable(p) { return head(p); }
    function term_list(p) { return tail(p); }
    
    function is_variable(x) { return is_string(x); }

    function is_same_variable(v1, v2) {
        return is_variable(v1) && is_variable(v2) && v1 === v2;
    }
    function first_term(tl) {
        return apply_generic("first_term", list(tl));
    }
    function rest_terms(tl) {
        return apply_generic("rest_terms", list(tl));
    }
    function is_empty_termlist(tl) {
        return apply_generic("is_empty_termlist", list(tl));
    }
    function the_empty_termlist(tl) {
        return get("the_empty_termlist", type_tag(tl))();
    }
    function adjoin_term(term, term_list) {
        const fun = get("adjoin_term", type_tag(term_list));
        return !is_undefined(fun)
            ? fun(term, contents(term_list))
            : error(list(term_list), "no function for these types - adjoin_term");
    }

    function make_poly(variable, term_list) {
        return pair(variable, term_list);
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
                                           coeff(t1) + coeff(t2)),
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

    function mul_terms(L1, L2) {
        return is_empty_termlist(L1)
               ? the_empty_termlist(L1)
               : add_terms(mul_term_by_all_terms(
                                     first_term(L1), L2),
                           mul_terms(rest_terms(L1), L2));
    }
    function mul_term_by_all_terms(t1, L) {
        if (is_empty_termlist(L)) {
            return the_empty_termlist(L);
        } else {
            const t2 = first_term(L);
            return adjoin_term(
                       make_term(order(t1) + order(t2),
                                 coeff(t1) * coeff(t2)),
                       mul_term_by_all_terms(t1, rest_terms(L)));
        }
    }

    // interface to rest of the system
    function tag(p) {
        return attach_tag("polynomial", p);
    }
    put("add", list("polynomial", "polynomial"),
        (p1, p2) => tag(add_poly(p1, p2)));
    put("mul", list("polynomial", "polynomial"),
        (p1, p2) => tag(mul_poly(p1, p2)));
    put("make_sparse", "polynomial",
        (variable, terms) => tag(make_sparse_poly(variable, terms)));
    put("make_dense", "polynomial",
        (variable, terms) => tag(make_dense_poly(variable, terms)));

    return "done";
}

// sparse representation of polynomials
function install_sparse_package() {
    // internal functions
    const the_empty_termlist = null;
    function first_term(term_list) {
        return head(term_list);
    }
    function rest_terms(term_list) {
        return tail(term_list);
    }
    function is_empty_termlist(term_list) {
        return is_null(term_list);
    }
    function coeff(term) {
        head(tail(term));
    }
    function adjoin_term(term, term_list) {
        return coeff(term) === 0
               ? term_list
               : pair(term, term_list);
    }
    function make_sparse_poly(variable, term_list) {
        return pair(variable, term_list);
    }
    
    // interface to the rest of the system
    function tag(term_list) {
        return attach_tag("sparse", term_list);
    }

    put("first_term", list("sparse"), tl => first_term(tl));
    put("rest_terms", list("sparse"), tl => tag(rest_terms(tl)));
    put("is_empty_termlist", list("sparse"), tl => is_empty_termlist(tl));
    put("the_empty_termlist", "sparse", () => tag(the_empty_termlist));
    put("adjoin_term", "sparse", (t, tl) => tag(adjoin_term(t, tl)));
    put("make_sparse_poly", "sparse", (variable, terms) => make_sparse_poly(variable, tag(terms)));
    
    return "done";
}

// dense representation of polynomials
function install_dense_package() {
    // internal functions
    const the_empty_termlist = null;
    function make_term(order, coeff) {
        return list(order, coeff);
    }
    function first_term(term_list) {
        return make_term(length(term_list) - 1, head(term_list));
    }
    function rest_terms(term_list) {
        return tail(term_list);
    }
    function is_empty_termlist(term_list) {
        return is_null(term_list);
    }
    function order(term) {
        head(term);
    }
    function coeff(term) {
        head(tail(term));
    }
    function adjoin_term(term, term_list) {
        return coeff(term) === 0
               ? term_list
               : order(term) === length(term_list)
               ? pair(coeff(term), term_list)
               : adjoin_term(term, pair(0, term_list));
    }
    function make_dense_poly(variable, term_list) {
        return pair(variable, term_list);
    }
    
    // interface to the rest of the system
    function tag(term_list) {
        return attach_tag("dense", term_list);
    }

    put("first_term", list("dense"), tl => first_term(tl));
    put("rest_terms", list("dense"), tl => tag(rest_terms(tl)));
    put("is_empty_termlist", list("dense"), tl => is_empty_termlist(tl));
    put("the_empty_termlist", "dense", () => tag(the_empty_termlist));
    put("adjoin_term", "dense", (t, tl) => tag(adjoin_term(t, tl)));
    put("make_dense_poly", "dense", (variable, terms) => make_dense_poly(variable, tag(terms)));
    
    return "done";
}

// to keep things simple, I decided to use
// primitive numbers to represent the polynomial's coefficients

// generic functions
function add(x, y) { return apply_generic("add", list(x, y)); }
function sub(x, y) { return apply_generic("sub", list(x, y)); }
function mul(x, y) { return apply_generic("mul", list(x, y)); }
function div(x, y) { return apply_generic("div", list(x, y)); }

function attach_tag(type_tag, contents) {
    if (is_number(contents)) {
        return pair("javascript_number", contents);
    } else {
        return pair(type_tag, contents);
    }
}

function type_tag(datum) {
    if (is_number(datum)) {
        return "javascript_number";
    } else if (is_pair(datum)) {
        return head(datum);
    } else {
        return error(datum, "bad tagged datum -- type_tag");
    }
}

function contents(datum) {
    if (is_number(datum)) {
        return datum;
    } else if (is_pair(datum)) {
        return tail(datum);
    } else {
        return error(datum, "bad tagged datum -- contents");
    }
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
