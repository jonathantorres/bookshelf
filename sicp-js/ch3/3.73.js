import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append
} from 'sicp';

const ones = pair(1, () => ones);
const integers = pair(1, () => add_streams(ones, integers));

const rc1 = rc(5, 1, 0.5)(integers, 1);

display(eval_stream(rc1, 10));

function rc(r, c, dt) {
    return (si, initial) => {
        return add_streams(
            scale_stream(si, r),
            integral(scale_stream(si, 1/c), initial, dt)
        );
    }
}

function integral(integrand, initial_value, dt) {
    const integ = pair(
        initial_value,
        () => add_streams(scale_stream(integrand, dt), integ)
    );
    return integ;
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
