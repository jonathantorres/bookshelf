import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append,
    math_sqrt, math_random
} from 'sicp';

display(stream_ref(pi_estimate_stream(), 5000));

function pi_estimate_stream() {
    return scale_stream(monte_carlo(exp_stream(-1.0, 1.0, -1.0, 1.0, 1.0), 0, 0), 4.0);
}

function exp_stream(x1, x2, y1, y2, r) {
    return stream_map(
        (x) => r > x,
        add_streams(
            stream_map(square, rand_range_stream(x1, x2)),
            stream_map(square, rand_range_stream(y1, y2))
        )
    );
}

function monte_carlo(experiment_stream, passed, failed) {
    function next(passed, failed) {
        return pair(passed / (passed + failed),
                    () => monte_carlo(stream_tail(experiment_stream),
                                      passed, failed));
    }
    return head(experiment_stream)
           ? next(passed + 1, failed)
           : next(passed, failed + 1);
}

function rand_range_stream(low, high) {
    return pair(random_in_range(low, high), () => rand_range_stream(low, high));
}

function add_streams(s1, s2) {
    return stream_map_2((a, b) => a+b, s1, s2);
}

function scale_stream(stream, factor) {
    return stream_map(x => x * factor, stream);
}

function stream_map_2(f, s1, s2) {
    return is_null(s1) && is_null(s2)
           ? null
           : is_null(s1) || is_null(s2)
           ? error(null, "unexpected argument -- stream_map_2")
           : pair(f(head(s1), head(s2)),
                  memo(() => stream_map_2(f, stream_tail(s1),
                                          stream_tail(s2))));
}

function memo(fun) {
    let already_run = false;
    let result = undefined;
    return () => {
       if (!already_run) {
           result = fun();
           already_run = true;
           return result;
       } else {
           return result;
       }
   };
}

function random_in_range(low, high) {
    const range = high - low;
    return low + math_random() * range;
}

function square(n) {
    return n*n;
}
