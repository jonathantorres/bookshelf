import {
    display, pair, stream, stream_tail, stream_for_each, stream_append,
    stream_map, eval_stream, head, is_null, error, math_abs, stream_ref
} from 'sicp';

const ln2_stream = partial_sums(ln2_summands(1));

display(eval_stream(ln2_stream, 5));

function ln2_summands(n) {
    return pair(1.0/n, () => stream_map((x) => -x, ln2_summands(n+1)));
}

function partial_sums(s) {
    return pair(head(s), () => add_streams(stream_tail(s), partial_sums(s)));
}

function add_streams(s1, s2) {
    return stream_map_2((a, b) => a+b, s1, s2);
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
