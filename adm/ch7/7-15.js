'use strict';

subsets(5, 10);

function subsets(k, n) {
    const backtrack = function (subs, s, k, n) {
        if (is_solution(subs, s, k, n)) {
            process_solution(subs, s, k, n);
        } else {
            let candidates = construct_candidates();

            for (let i = 0; i < candidates.length; i++) {
                subs[s] = candidates[i];
                backtrack(subs, s+1, k, n);
            }
        }
    }

    let s = new Array(n)
    backtrack(s, 0, k, n);
}

function construct_candidates() {
    return [
        true,
        false,
    ];
}

function process_solution(subs, s, k, n) {
    let solution = [];

    for (let i = 0; i < subs.length; i++) {
        if (subs[i] === true) {
            solution.push(i+1);
        }
    }

    if (solution.length === k) {
        console.log(solution);
    }
}

function is_solution(subs, s, k, n) {
    return s === n;
}
