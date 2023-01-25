import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, eval_stream, head, is_null, error
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));
const factorials = pair(1, () => mul_streams(factorials, integers));

display(eval_stream(mul_streams(integers, integers), 3));
display(eval_stream(factorials, 10));

function add_streams(s1, s2) {
    return stream_map_2((a, b) => a+b, s1, s2);
}

function mul_streams(s1, s2) {
    return stream_map_2((a, b) => a*b, s1, s2);
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
