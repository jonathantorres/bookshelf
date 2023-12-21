import {
    pair, head, tail, display, display_list, list, math_cos, math_sin, is_pair, is_number,
    is_string, is_null, append, error, equal, length, is_undefined, set_tail,
    map, apply_in_underlying_javascript, math_sqrt, math_atan, accumulate
} from 'sicp';

const operation_table = make_table();
const get = operation_table("lookup");
const put = operation_table("insert");

install_javascript_number_package();
install_rational_package();
install_rectangular_package();
install_polar_package();
install_complex_package();

const a = make_complex_from_real_imag(
    make_javascript_number(10),
    make_rational(5, 1)
);
const b = make_complex_from_mag_ang(
    make_rational(8, 2),
    make_javascript_number(4)
);

display(add(a, b));
display(sub(a, b));
display(mul(a, b));
display(div(a, b));

function apply_generic(op, args) {
    const type_tags = map(type_tag, args);
    const fun = get(op, type_tags);
    if (!is_undefined(fun)) {
        if (should_simplify(op)) {
            return drop(apply(fun, map(contents, args)));
        } else {
            return apply(fun, map(contents, args));
        }
    } else {
        if (length(args) === 2) {
            const type1 = head(type_tags);
            const type2 = head(tail(type_tags));
            const a1 = head(args);
            const a2 = head(tail(args));
            
            if (level(type1, hierarchy) > level(type2, hierarchy)) {
                return apply_generic(op, list(a1, succesive_raising(a2, type1)));
            } else if (level(type2, hierarchy) > level(type1, hierarchy)) {
                return apply_generic(op, list(succesive_raising(a1, type2), a2));
            } else {
                return error(list(op, type_tags), "no method for these types");
            }
        } else {
            return error(list(op, type_tags), "no method for these types");
        }
    }
}


const hierarchy = list("javascript_number", "rational", "complex");

function drop(type) {
    function is_js_number(x) {
        return equal(type_tag(x), "javascript_number");
    }
    if (is_js_number(type)) {
        return type;
    } else {
        const projected = project(type);
        return !equal(type_tag(type), type_tag(projected))
            && is_equal(raise(projected), type)
            ? drop(projected)
            : type;
    }
}

function level(type, type_list) {
    return is_null(type_list)
        ? error(type, "type is not supported")
        : equal(type, head(type_list))
        ? 1
        : 1 + level(type, tail(type_list));
}

function succesive_raising(type, to_type_tag) {
    return level(type_tag(type), hierarchy) === level(to_type_tag, hierarchy)
        ? type
        : succesive_raising(raise(type), to_type_tag);
}

function should_simplify(op) {
    return equal(op, "add")
        || equal(op, "sub")
        || equal(op, "mul")
        || equal(op, "div")
        ? true
        : false;
}

// install complex package
function install_complex_package() {
    // imported functions from rectangular and polar packages
    function make_from_real_imag(x, y) {
        return get("make_from_real_imag", "rectangular")(x, y);
    }
    function make_from_mag_ang(r, a) {
        return get("make_from_mag_ang", "polar")(r, a);
    }
    // internal functions
    function add_complex(z1, z2) {
        return make_from_real_imag(
            add(real_part(z1), real_part(z2)),
            add(imag_part(z1), imag_part(z2))
        );
    }
    function sub_complex(z1, z2) {
        return make_from_real_imag(
            sub(real_part(z1), real_part(z2)),
            sub(imag_part(z1), imag_part(z2))
        );
    }
    function mul_complex(z1, z2) {
        return make_from_mag_ang(
            mul(magnitude(z1), magnitude(z2)),
            add(angle(z1), angle(z2))
        );
    }
    function div_complex(z1, z2) {
        return make_from_mag_ang(
            div(magnitude(z1), magnitude(z2)),
            sub(angle(z1), angle(z2))
        );
    }
    function is_equal_complex(z1, z2) {
        return is_equal(real_part(z1), real_part(z2)) && is_equal(imag_part(z1), imag_part(z2));
    }
    function tag(z) { return attach_tag("complex", z); }
    function project_complex(z) {
        return is_equal(imag_part(z), make_javascript_number(0))
            ? real_part(z)
            : tag(z);
    }

    // interface to rest of the system
    put("add", list("complex", "complex"),
        (z1, z2) => tag(add_complex(z1, z2)));
    put("sub", list("complex", "complex"),
        (z1, z2) => tag(sub_complex(z1, z2)));
    put("mul", list("complex", "complex"),
        (z1, z2) => tag(mul_complex(z1, z2)));
    put("div", list("complex", "complex"),
        (z1, z2) => tag(div_complex(z1, z2)));
    put("is_equal", list("complex", "complex"),
        (z1, z2) => is_equal_complex(z1, z2));
    put("project", list("complex"),
        (z) => project_complex(z));
    put("make_from_real_imag", "complex",
        (x, y) => tag(make_from_real_imag(x, y)));
    put("make_from_mag_ang", "complex",
        (r, a) => tag(make_from_mag_ang(r, a)));
    return "done";
}

function install_rectangular_package() {
    // internal functions
    function real_part(z) { return head(z); }
    function imag_part(z) { return tail(z); }
    function make_from_real_imag(x, y) { return pair(x, y); }
    function magnitude(z) {
        return square_root(add(square(real_part(z)), square(imag_part(z))));
    }
    function angle(z) {
        return atan(imag_part(z), real_part(z));
    }
    function make_from_mag_ang(r, a) {
        return pair(mul(r, cosine(a)), mul(r, sine(a)));
    }

    // interface to the rest of the system
    function tag(x) { return attach_tag("rectangular", x); }
    put("real_part", list("rectangular"), real_part);
    put("imag_part", list("rectangular"), imag_part);
    put("magnitude", list("rectangular"), magnitude);
    put("angle", list("rectangular"), angle);
    put("make_from_real_imag", "rectangular",
        (x, y) => tag(make_from_real_imag(x, y)));
    put("make_from_mag_ang", "rectangular",
        (r, a) => tag(make_from_mag_ang(r, a)));
    return "done";
}

function install_polar_package() {
    // internal functions
    function magnitude(z) { return head(z); }
    function angle(z) { return tail(z); }
    function make_from_mag_ang(r, a) { return pair(r, a); }
    function real_part(z) {
        return mul(magnitude(z), cosine(angle(z)));
    }
    function imag_part(z) {
        return mul(magnitude(z), sine(angle(z)));
    }
    function make_from_real_imag(x, y) {
        return pair(square_root(add(square(x), square(y))),
                    atan(y, x));
    }

    // interface to the rest of the system
    function tag(x) { return attach_tag("polar", x); }
    put("real_part", list("polar"), real_part);
    put("imag_part", list("polar"), imag_part);
    put("magnitude", list("polar"), magnitude);
    put("angle", list("polar"), angle);
    put("make_from_real_imag", "polar",
        (x, y) => tag(make_from_real_imag(x, y)));
    put("make_from_mag_ang", "polar",
        (r, a) => tag(make_from_mag_ang(r, a)));
    return "done";
}

function make_complex_from_real_imag(x, y){
   return get("make_from_real_imag", "complex")(x, y);
}

function make_complex_from_mag_ang(r, a){
   return get("make_from_mag_ang", "complex")(r, a);
}

// rational package
function install_rational_package() {
    // internal functions
    function numer(x) { return head(x); }
    function denom(x) { return tail(x); }
    function make_rat(n, d) {
        const g = gcd(n, d);
        return pair(n / g, d / g);
    }
    function add_rat(x, y) {
        return make_rat(numer(x) * denom(y) + numer(y) * denom(x),
                        denom(x) * denom(y));
    }
    function sub_rat(x, y) {
        return make_rat(numer(x) * denom(y) - numer(y) * denom(x),
                        denom(x) * denom(y));
    }
    function mul_rat(x, y) {
        return make_rat(numer(x) * numer(y),
                        denom(x) * denom(y));
    }
    function div_rat(x, y) {
        return make_rat(numer(x) * denom(y),
                        denom(x) * numer(y));
    }
    function is_equal_rat(x, y) {
        return numer(x) * denom(y) === numer(y) * denom(x);
    }
    function tag(x) {
        return attach_tag("rational", x);
    }
    function project_rational(x) {
        return denom(x) === 1
            ? make_javascript_number(numer(x))
            : tag(x);
    }

    // interface to rest of the system
    put("add", list("rational", "rational"),
        (x, y) => tag(add_rat(x, y)));
    put("sub", list("rational", "rational"),
        (x, y) => tag(sub_rat(x, y)));
    put("mul", list("rational", "rational"),
        (x, y) => tag(mul_rat(x, y)));
    put("div", list("rational", "rational"),
        (x, y) => tag(div_rat(x, y)));
    put("is_equal", list("rational", "rational"),
        (x, y) => is_equal_rat(x, y));
    put("make", "rational",
        (n, d) => tag(make_rat(n, d)));
    put("raise", list("rational"),
        (x) => make_complex_from_real_imag(
            make_javascript_number(1.0 * (numer(x) / denom(x))),
            make_javascript_number(0)));
    put("project", list("rational"),
        (x) => project_rational(x));
    put("cosine", list("rational"),
        (x) => make_javascript_number(math_cos(numer(x) / denom(x))));
    put("sine", list("rational"),
        (x) => make_javascript_number(math_sin(numer(x) / denom(x))));
    put("atan", list("rational", "rational"),
        (x, y) => make_javascript_number(math_atan2(
            numer(x) / denom(x),
            numer(y) / denom(y))));
    put("square", list("rational"),
        (x) => tag(mul_rat(x, x)));
    put("square_root", list("rational"),
        (x) => make_javascript_number(math_sqrt((numer(x) * 1.0) / denom(x))));
    return "done";
}

function make_rational(n, d) {
    return get("make", "rational")(n, d);
}

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
    put("is_equal", list("javascript_number", "javascript_number"),
        (x, y) => x === y);
    put("make", "javascript_number",
        x => tag(x));
    put("raise", list("javascript_number"),
        x => make_rational(x, 1));
    put("project", list("javascript_number"),
        x => tag(x));
    put("square_root", list("javascript_number"),
        x => tag(math_sqrt(x)));
    put("square", list("javascript_number"),
        x => tag(x * x));
    put("sine", list("javascript_number"),
        x => tag(math_sin(x)));
    put("cosine", list("javascript_number"),
        x => tag(math_cos(x)));
    put("atan", list("javascript_number", "javascript_number"),
        (x, y) => tag(math_atan2(x,y)));
    return "done";
}

function make_javascript_number(n) {
    return get("make", "javascript_number")(n);
}

function add(x, y) { return apply_generic("add", list(x, y)); }

function sub(x, y) { return apply_generic("sub", list(x, y)); }

function mul(x, y) { return apply_generic("mul", list(x, y)); }

function div(x, y) { return apply_generic("div", list(x, y)); }

function square_root(x) { return apply_generic("square_root", list(x)); }

function sine(x) { return apply_generic("sine", list(x)); }

function cosine(x) { return apply_generic("cosine", list(x)); }

function atan(x, y) { return apply_generic("atan", list(x, y)); }

function real_part(z) { return apply_generic("real_part", list(z)); }

function imag_part(z) { return apply_generic("imag_part", list(z)); }

function magnitude(z) { return apply_generic("magnitude", list(z)); }

function angle(z)     { return apply_generic("angle", list(z)); }

function is_equal(x, y) { return apply_generic("is_equal", list(x, y)); }

function project(x) { return apply_generic("project", list(x)); }

function raise(x) { return apply_generic("raise", list(x)); }

function square(x) { return apply_generic("square", list(x)); }

function make_javascript_number(n) {
    return get("make", "javascript_number")(n);
}

function attach_tag(type_tag, contents) {
    return pair(type_tag, contents);
}

function type_tag(datum) {
    return is_pair(datum)
           ? head(datum)
           : error(datum, "bad tagged datum -- type_tag");
}

function contents(datum) {
    return is_pair(datum)
           ? tail(datum)
           : error(datum, "bad tagged datum -- contents");
}

function apply(fun, args) {
    return apply_in_underlying_javascript(fun, args);
}

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
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
