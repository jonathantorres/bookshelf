import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));

display(eval_stream(a(), 10));
display(eval_stream(b(), 10));

// the stream of all pairs of positive integers (i,j) with i<=j ordered according to the sum i+j
function a() {
    function sum(p) {
        return head(p) + head(tail(p));
    }
    return weighted_pairs(integers, integers, sum);
}

// the stream of all pairs of positive integers (i,j) with i<=j where neither i nor j
// is divisible by 2, 3, or 5, and the pairs are ordered according to the sum 2i+3j+5ij
function b() {
    function divisible(n) {
        return !(
            n%2 === 0
            || n%3 === 0
            || n%5 === 0
        );
    }
    function weight(p) {
        const i = head(p);
        const j = head(tail(p));
        return 2*i + 3*j + 5*i*j;
    }
    const ints = stream_filter(divisible, integers);
    return weighted_pairs(ints, ints, weight);
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
