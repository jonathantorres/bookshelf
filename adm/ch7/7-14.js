'use strict';

let seen_solutions = [];

letter_permutations('Jonathan');

function letter_permutations(s) {
    const backtrack = function (perm, str, k, n) {
        if (is_solution(perm, str, k, n)) {
            process_solution(perm);
        } else {
            let candidates = construct_candidates(perm, str, k, n);

            for (let i = 0; i < candidates.length; i++) {
                perm[k] = candidates[i];
                backtrack(perm, str, k+1, n);
            }
        }
    }

    let a = new Array(s.length)
    backtrack(a, s.toLowerCase(), 0, s.length);
}

function construct_candidates(perm, str, k, n) {
    let candidates = [];
    let str_cpy = Array.from(str);

    for (let i = 0; i < k; i++) {
        const idx = str_cpy.indexOf(perm[i]);

        if (idx >= 0) {
            str_cpy.splice(idx, 1);
        }
    }

    for (const c of str_cpy) {
        candidates.push(c);
    }

    return candidates;
}

function process_solution(perm, str, k, n) {
    let solution = '';

    for (const c of perm) {
        solution += c;
    }

    console.log(solution);
}

function is_solution(perm, str, k, n) {
    if (k !== n) {
        return false;
    }

    let seen = false;
    let perm_str = '';

    for (const c of perm) {
        perm_str += c;
    }

    for (let i = 0; i < seen_solutions.length; i++) {
        if (seen_solutions[i] === perm_str) {
            seen = true;
            break;
        }
    }

    if (!seen) {
        seen_solutions.push(perm_str);
    }

    return !seen;
}

