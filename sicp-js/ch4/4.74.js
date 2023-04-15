// frame bindings
function make_frame(symbols, values) { return pair(symbols, values); }

function frame_symbols(frame) { return head(frame); }

function frame_values(frame) { return tail(frame); }

function first_frame(env) { return head(env); }

// extend and friends
function make_binding(variable, value) {
    return pair(variable, value);
}
function binding_variable(binding) {
    return head(binding);
}
function binding_value(binding) {
    return tail(binding);
}
function binding_in_frame(variable, frame) {
    return assoc(variable, frame);
}
function extend(variable, value, frame) {
    return pair(make_binding(variable, value), frame);
}

// promises
function make_promise(vars, pred) {
    return pair(vars, pred);
}

function promise_variables(p) {
    return head(p);
}

function promise_predicate(p) {
    return tail(p);
}

function is_free(variable, frame) {
    const binding = binding_in_frame(variable, frame);

    return !binding || (is_variable(binding_value(binding)) && is_free(binding_value(binding), frame));
}

function free_variables(query, frame) {
    if (is_null(query)) {
        return null;
    }

    if (is_variable(query) && is_free(query, frame)) {
        return list(query);
    }

    if (is_pair(query)) {
        return append(
            free_variables(head(query), frame),
            free_variables(tail(query), frame)
        );
    }

    return null;
}

function compact_frame(frame) {
    const promises = frame_symbols(frame);
    if (is_null(promises)) {
        return frame;
    }
    const promise = head(promises);
    const rest = tail(promises);
    const vars = promise_variables(promise);
    const pred = promise_predicate(promise);
    const has_free = map(v => is_free(v, frame), vars);

    if (has_free) {
        return pred(frame);
    }
    return compact_frame(make_frame(frame_symbols(frame), rest));
}

function promise_to_frame(frame, free_vars, pred) {
    return make_frame(
        frame_symbols(frame),
        pair(make_promise(free_vars, pred), frame_values(frame))
    );
}

// changes on negate and js predicate
function negate(exps, frame_stream) {
   return stream_flatmap(
              frame =>
                promise_to_frame(frame, free_variables(negated_query(exps), frame),
                frame => is_null(evaluate_query(negated_query(exps), singleton_stream(frame)))),
        frame_stream);
}

function javascript_predicate(exps, frame_stream) {
    return stream_map(
        frame => promise_to_frame(
            frame,
            free_variables(exps, frame),
            frame => evaluate(instantiate_expression(javascript_predicate_expression(exps), frame),
            (v, f) => error("Unknown variable -- JS Predicate"))
        ),
        frame_stream
    );
}

