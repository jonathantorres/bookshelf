import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));

display(eval_stream(two_squares(), 10));

function two_squares() {
    const ints = weighted_pairs(integers, integers, weight);
    function square(n) {
        return n*n;
    }
    function weight(p) {
        return square(head(p)) + square(head(tail(p)));
    }
    function filter(s) {
        const p1 = head(s);
        const p2 = head(stream_tail(s));
        const p3 = head(stream_tail(stream_tail(s)));
        if (weight(p1) === weight(p2) && weight(p1) === weight(p3) && weight(p2) === weight(p3)) {
            return pair(weight(p1), () => filter(stream_tail(s)));
        }
        return filter(stream_tail(s));
    }
    return filter(ints);
}

function weighted_pairs(s, t, w) {
    return pair(
        list(head(s), head(t)),
        () => merge_weighted(
            stream_map(x => list(head(s), x), stream_tail(t)),
            weighted_pairs(stream_tail(s), stream_tail(t), w),
            w
        )
    );
}

function merge_weighted(s1, s2, w) {
    if (is_null(s1)) {
        return s2;
    } else if (is_null(s2)) {
        return s1;
    } else {
        const s1head = head(s1);
        const s2head = head(s2);
        const s1w = w(s1head);
        const s2w = w(s2head);
        return s1w < s2w
               ? pair(s1head, () => merge_weighted(stream_tail(s1), s2, w))
               : pair(s2head, () => merge_weighted(s1, stream_tail(s2), w));
    }
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
