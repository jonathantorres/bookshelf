import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append
} from 'sicp';

display(eval_stream(solve_2nd(1, 2, 0.001, 5, 6), 10));

function solve_2nd(a, b, dt, y0, dy0) {
    const y = integral(() => dy, y0, dt);
    const dy = integral(() => ddy, dy0, dt);
    const ddy = add_streams(scale_stream(dy, a), scale_stream(y, b));
    return y;
}

function integral(delayed_integrand, initial_value, dt) {
    const integ = pair(
        initial_value,
        () => {
            const integrand = delayed_integrand();
            return is_null(integrand)
                ? null
                : add_streams(scale_stream(integrand, dt), integ);
        }
    );

    return integ;
}

function scale_stream(stream, factor) {
    return stream_map(x => x * factor, stream);
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
