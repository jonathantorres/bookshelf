// changes on lookup_symbol_value
function lookup_symbol_value(symbol, env) {
    function env_loop(env) {
        function scan(symbols, vals) {
            return is_null(symbols)
                   ? env_loop(enclosing_environment(env))
                   : symbol === head(symbols)
                   ? pair("bounded", head(vals))
                   : scan(tail(symbols), tail(vals));
        }
        if (env === the_empty_environment) {
            return pair("unbounded", null);
        } else {
            const frame = first_frame(env);
            return scan(frame_symbols(frame), frame_values(frame));
        }
    }
    return env_loop(env);
}

function bound_symbol(symbol) {
    return is_pair(symbol) && equal(head(symbol), "bounded");
}

function get_symbol_value(symbol) {
    return tail(symbol);
}

// changes on machine instructions
"ev_name",
    assign("val", list(op("symbol_of_name"), reg("comp"), reg("env"))),
    assign("val", list(op("lookup_symbol_value"), reg("val"), reg("env"))),
    test(list(op("bound_symbol"), reg("val"))),
    branch(label("bound_symbol")),
    assign("val", constant("error")),
    go_to(label("error")),
"bound_symbol"
    assign("val", list(op("get_symbol_value"), reg("val"))),
    go_to(reg("continue")),
