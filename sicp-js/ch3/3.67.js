import {
    display, pair, stream, stream_tail, stream_for_each, stream_append,
    stream_map, eval_stream, head, is_null, error, stream_ref, list
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));

display(eval_stream(pairs(integers, integers), 50));

function pairs(s, t) {
    return pair(
        list(head(s), head(t)),
        () => interleave(
            interleave(
                stream_map(x => list(head(s), x), stream_tail(t)),
                stream_map(x => list(x, head(t)), stream_tail(s)),
            ),
            pairs(stream_tail(s), stream_tail(t))
        )
    );
}

function interleave(s1, s2) {
    return is_null(s1)
           ? s2
           : pair(head(s1), () => interleave(s2, stream_tail(s1)));
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
