'use strict';

let seen_solutions = [];

multisets([1,1,2,2]);

function multisets(start_set) {
    const backtrack = function (set, start_set, k, n) {
        if (is_solution(set, start_set, k, n)) {
            process_solution(set);
        } else {
            let candidates = construct_candidates(set, start_set, k, n);

            for (let i = 0; i < candidates.length; i++) {
                set[k] = candidates[i];
                backtrack(set, start_set, k+1, n);
            }
        }
    }

    let s = new Array(start_set.length);
    backtrack(s, start_set, 0, start_set.length);
}

function construct_candidates(set, start_set, k, n) {
    let c = [];
    let start_cpy = Array.from(start_set);

    for (let i = 0; i < k; i++) {
        const idx = start_cpy.indexOf(set[i]);

        if (idx >= 0) {
            start_cpy.splice(idx, 1);
        }
    }

    for (const i of start_cpy) {
        c.push(i);
    }

    return c;
}

function process_solution(set) {
    let solution = [];

    for (let i = 0; i < set.length; i++) {
        solution.push(set[i]);
    }

    console.log(solution);
}

function is_solution(set, start_set, k, n) {
    if (k !== n) {
        return false;
    }

    let seen = false;
    let set_cpy = Array.from(set);

    for (let i = 0; i < seen_solutions.length; i++) {
        if (is_same(seen_solutions[i], set_cpy)) {
            seen = true;
            break;
        }
    }

    if (!seen) {
        seen_solutions.push(set_cpy);
    }

    return !seen;
}

function is_same(a, b) {
    let same = true;

    for (let i = 0; i < a.length; i++) {
        if (a[i] !== b[i]) {
            same = false;
            break;
        }
    }

    return same;
}
