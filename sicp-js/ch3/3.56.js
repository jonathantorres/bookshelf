import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map, eval_stream, head, is_null, error
} from 'sicp';

const integers = integers_starting_from(1);
const s = pair(1, () => merge(scale_stream(integers, 2), merge(scale_stream(integers, 3), scale_stream(integers, 5))));

display(eval_stream(s, 10));

function merge(s1, s2) {
    if (is_null(s1)) {
        return s2;
    } else if (is_null(s2)) {
        return s1;
    } else {
        const s1head = head(s1);
        const s2head = head(s2);
        return s1head < s2head
               ? pair(s1head, () => merge(stream_tail(s1), s2))
               : s1head > s2head
               ? pair(s2head, () => merge(s1, stream_tail(s2)))
               : pair(s1head, () => merge(stream_tail(s1), stream_tail(s2)));
    }
}

function integers_starting_from(n) {
    return pair(n, () => integers_starting_from(n + 1));
}

function scale_stream(stream, factor) {
    return stream_map(x => x * factor, stream);
}
