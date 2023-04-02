'use strict';

office_move(5);

function office_move(num) {
    const backtrack = function (perm, k, n) {
        if (is_solution(perm, k, n)) {
            process_solution(perm);
        } else {
            let candidates = construct_candidates(perm, k, n);

            for (let i = 0; i < candidates.length; i++) {
                perm[k] = candidates[i];
                backtrack(perm, k+1, n);
            }
        }
    }

    let a = new Array(num)
    backtrack(a, 0, num);
}

function construct_candidates(perm, k, n) {
    let candidates = [];
    let in_perm = new Array(n);

    for (let i = 0; i < n; i++) {
        in_perm[i] = false;
    }

    for (let i = 0; i < k; i++) {
        in_perm[perm[i]] = true;
    }

    for (let i = 0; i < n; i++) {
        if (!in_perm[i]) {
            candidates.push(i);
        }
    }

    return candidates;
}

function process_solution(perm, k, n) {
    let alyssa = perm[0]+1;
    let ben = perm[1]+1;
    let cy = perm[2]+1;
    let lem = perm[3]+1;
    let louis = perm[4]+1;

    console.log("alyssa: " + alyssa);
    console.log("ben: " + ben);
    console.log("cy: " + cy);
    console.log("lem: " + lem);
    console.log("louis: " + louis);
}

function is_solution(perm, k, n) {
    if (k !== n) {
        return false;
    }

    let alyssa = perm[0]+1;
    let ben = perm[1]+1;
    let cy = perm[2]+1;
    let lem = perm[3]+1;
    let louis = perm[4]+1;

    if (
        alyssa !== 5
        && ben !== 1
        && cy !== 5
        && cy !== 1
        && lem > ben
        && Math.abs(cy - ben) !== 1
        && Math.abs(louis - cy) !== 1
    ) {
        return true;
    }

    return false;
}
