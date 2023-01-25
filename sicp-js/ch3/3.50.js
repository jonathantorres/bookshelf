import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, eval_stream, head, is_null
} from 'sicp';

const s1 = stream(1,2,3);
const s2 = stream(1,2,3);

display(eval_stream(stream_map_2(add, s1, s2), 3));
display(eval_stream(stream_map_2_optimized(add, s1, s2), 3));

function stream_map_2(f, s1, s2) {
    function iter(f, s1, s2, res) {
        if (is_null(s1) || is_null(s2)) {
            return res;
        }
        return iter(
            f,
            stream_tail(s1),
            stream_tail(s2),
            stream_append(res, stream(f(head(s1), head(s2))))
        );
    }
    return iter(f, s1, s2, null);
}

function stream_map_2_optimized(f, s1, s2) {
    if (is_null(s1) || is_null(s2)) {
        return null;
    }
    return pair(
        f(head(s1), head(s2)),
        memo(() => stream_map_2_optimized(
            f,
            stream_tail(s1),
            stream_tail(s2)))
    );
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

function display_stream(s) {
    return stream_for_each(display, s);
}

function add(a, b) {
    return a+b;
}
