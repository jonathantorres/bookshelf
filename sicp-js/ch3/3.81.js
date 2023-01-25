import {
    display, pair, stream, stream_tail, stream_for_each, stream_append, stream_map,
    eval_stream, head, tail, is_null, error, stream_ref, stream_filter, list, append,
    math_sqrt, math_random
} from 'sicp';

const random_init = 123456789;
const g = pair("generate", () => g);
const rand_nums = rand_numbers(g);

display(eval_stream(rand_nums, 10));

function rand_numbers(requests) {
    function next(seed, requests) {
        if (is_null(requests)) {
            return null;
        }
        if (head(requests) === "generate") {
            const g = rand_update(seed);
            return pair(g, () => next(g, stream_tail(requests)));
        } else if (head(requests) === "reset") {
            const g = head(stream_tail(requests));
            return next(g, stream_tail(stream_tail(requests)));
        } else {
            error("unknown request", head(requests));
        }
    }
    return next(random_init, requests);
}

function rand_update(x) {
    const m = 200560490131;
    const a = 1103515245;
    const b = 12345;
    return (a * x + b) % m;
}

