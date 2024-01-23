import {
    display, pair, stream, stream_tail, stream_for_each, stream_append,
    stream_map, eval_stream, head, is_null, error, math_abs, stream_ref
} from 'sicp';

display(sqrt(25, 0.0000010));

function stream_limit(s, tolerance) {
    if (math_abs(stream_ref(s, 0) - stream_ref(s, 1)) < tolerance) {
        return stream_ref(s, 1);
    }
    return stream_limit(stream_tail(s), tolerance);
}

function sqrt(x, tolerance) {
    return stream_limit(sqrt_stream(x), tolerance);
}

function sqrt_stream(x) {
   return pair(1, () => stream_map(guess => sqrt_improve(guess, x), sqrt_stream(x)));
}

function sqrt_improve(guess, x) {
    return average(guess, x / guess);
}

function average(x, y) {
    return (x + y) / 2;
}
