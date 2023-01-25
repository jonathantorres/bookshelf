import {
    display, pair, stream, stream_tail, stream_for_each, stream_append,
    stream_map, eval_stream, head, is_null, error
} from 'sicp';

const cosine_series = pair(
    1,
    () => integrate_series(pair(0, () => stream_map((x) => (-x), integrate_series(cosine_series))))
);

display(eval_stream(invert_unit_series(cosine_series), 10));

function invert_unit_series(s) {
    return pair(
        1,
        () => stream_map(x => -x, mul_series(stream_tail(s), invert_unit_series(s)))
    );
}

function mul_series(s1, s2) {
    return pair(
        head(s1) * head(s2),
        () => add_streams(mul_series(stream_tail(s1), s2), scale_stream(stream_tail(s2), head(s1)))
    );
}

function integrate_series(s) {
    function helper(ss, iter) {
        return pair(head(ss) / iter, () => helper(stream_tail(ss), iter + 1));
    }
    return helper(s, 1);
}

function add_streams(s1, s2) {
    return stream_map_2((a, b) => a+b, s1, s2);
}

function scale_stream(s, factor) {
    return stream_map(x => x*factor, s);
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
