'use strict';

const fs = require('fs');

let seen_solutions = [];
let all_words = [];

fs.readFile('words.txt', (err, buf) => {
    if (err) {
        throw err;
    }

    all_words = buf.toString().split('\n').map(w => w.toLowerCase());

    anagram('Many voted bush retired');
});

function anagram(s) {
    const backtrack = function (ana, str, k, n) {
        if (is_solution(ana, str, k, n)) {
            process_solution(ana);
        } else {
            let candidates = construct_candidates(ana, str, k, n);

            for (let i = 0; i < candidates.length; i++) {
                ana[k] = candidates[i];
                backtrack(ana, str, k+1, n);
            }
        }
    }

    let a = new Array(s.length)
    backtrack(a, s.toLowerCase(), 0, s.length);
}

function construct_candidates(ana, str, k, n) {
    let candidates = [];
    let str_cpy = Array.from(str);

    if (k >= 3) {
        let phrase = '';

        for (let i = 0; i < k; i++) {
            phrase += ana[i];
        }

        let words = phrase.split(' ');

        if (words.length > 1) {
            words.pop();

            for (const cur_word of words) {
                if (all_words.indexOf(cur_word) < 0) {
                    // if the word is gibberish, reject the anagram (no further candidates)
                    return candidates;
                }
            }
        }
    }

    for (let i = 0; i < k; i++) {
        const idx = str_cpy.indexOf(ana[i]);

        if (idx >= 0) {
            str_cpy.splice(idx, 1);
        }
    }

    for (const i of str_cpy) {
        candidates.push(i);
    }

    return candidates;
}

function process_solution(ana) {
    let phrase = '';

    for (let i = 0; i < ana.length; i++) {
        phrase += ana[i];
    }

    console.log(phrase);
}

function is_solution(ana, str, k, n) {
    if (k !== n) {
        return false;
    }

    let seen = false;
    let ana_cpy = Array.from(ana);

    for (let i = 0; i < seen_solutions.length; i++) {
        if (is_same(seen_solutions[i], ana_cpy)) {
            seen = true;
            break;
        }
    }

    if (seen) {
        return false;
    }

    seen_solutions.push(ana_cpy);

    let phrase = '';

    for (let i = 0; i < ana_cpy.length; i++) {
        phrase += ana_cpy[i];
    }

    let words = phrase.split(' ');

    for (const cur_word of words) {
        if (all_words.indexOf(cur_word) < 0) {
            return false;
        }
    }

    return true;
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
