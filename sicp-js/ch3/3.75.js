import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));

const zero_crossings = make_zero_crossings(integers, 1, 2);

display(eval_stream(zero_crossings, 10));

function make_zero_crossings(input_stream, last_value, last_avpt) {
    const avpt = (head(input_stream) + last_value) / 2;
    return pair(
        sign_change_detector(avpt, last_avpt),
        () => make_zero_crossings(stream_tail(input_stream), head(input_stream), avpt)
    );
}

function sign_change_detector(a, b) {
    if (b < 0 && 0 < a) {
        return 1;
    } else if (a < 0 && 0 < b) {
        return -1;
    } else {
        return 0;
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
