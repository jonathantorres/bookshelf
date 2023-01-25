import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map, eval_stream, head
} from 'sicp';

const cosine_series = pair(
    1,
    () => integrate_series(pair(0, () => stream_map((x) => (-x), integrate_series(cosine_series))))
);

const sine_series = pair(
    0,
    () => integrate_series(pair(1, () => integrate_series(stream_map(x => -x, sine_series))))
);

display(eval_stream(cosine_series, 10));
display(eval_stream(sine_series, 10));

function integrate_series(s) {
    function helper(ss, iter) {
        return pair(head(ss) / iter, () => helper(stream_tail(ss), iter + 1));
    }
    return helper(s, 1);
}
