'use strict';

derangements(3);

function derangements(n) {
    const backtrack = function (deran, start, n) {
        if (is_solution(deran, start, n)) {
            process_solution(deran);
        } else {
            let candidates = construct_candidates(deran, start, n);

            for (let i = 0; i < candidates.length; i++) {
                deran[start] = candidates[i];
                backtrack(deran, start+1, n);
            }
        }
    }

    let d = new Array(n)
    backtrack(d, 0, n);
}

function construct_candidates(deran, k, n) {
    let c = [];
    let in_deran = new Array(n);

    for (let i = 0; i < n; i++) {
        in_deran[i] = false;
    }

    for (let i = 0; i < k; i++) {
        in_deran[deran[i]] = true;
    }

    for (let i = 0; i < n; i++) {
        if (!in_deran[i] && i !== k) {
            c.push(i);
        }
    }

    return c;
}

function process_solution(deran) {
    let solution = [];

    for (let i = 0; i < deran.length; i++) {
        solution.push(deran[i]+1);
    }

    console.log(solution);
}

function is_solution(deran, k, n) {
    return k === n;
}
