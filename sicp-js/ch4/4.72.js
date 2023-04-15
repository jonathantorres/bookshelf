// function declarations
function uniquely_asserted(query, frame_stream) {
    return stream_flatmap(
        frame => {
            let result = evaluate_query(negated_query(query), singleton_stream(frame));
            return is_singleton_stream(result)
                    ? result
                    : null;
        },
        frame_stream
    );
}

function is_singleton_stream(st) {
    return !is_null(st) && is_null(stream_tail(st));
}

// add function to query system
put("unique", "evaluate_query", uniquely_asserted);

// query for testing
and(supervisor($j, $x), unique(supervisor($any, $x)))
