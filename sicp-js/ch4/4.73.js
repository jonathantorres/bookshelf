// function declarations
function conjoin(conjuncts, frame_stream) {
   return is_empty_conjunction(conjuncts)
          ? frame_stream
          : merge(
                evaluate_query(first_conjunct(conjuncts), frame_stream),
                conjoin(rest_conjuncts(conjuncts), frame_stream)
            );
}

function merge(s1, s2) {
    return stream_flatmap(
        f1 => {
            return stream_filter(
                f => !equal(f, "failed"),
                stream_map(
                    f2 => merge_frames(f1, f2),
                    s2
                );
            );
        },
        s2
    );
}

function merge_frames(f1, f2) {
    if (is_null(f1)) {
        return f2;
    }
    if (equal(f2, "failed")) {
        return "failed";
    }

    let variable = binding_variable(head(f1));
    let value = binding_value(head(f1));
    let ext = extend_if_possible(variable, value, f2);
    return merge_frames(tail(f1), ext);
}

