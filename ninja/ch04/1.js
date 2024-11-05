'use strict';

const assert = require('node:assert/strict');

function sum(...args) {
    var sum = 0;

    for (var i = 0; i < args.length; i++) {
        sum += args[i];
    }

    return sum;
}

assert(sum(1, 2, 3) === 6, 'Sum of first three numbers is 6');
assert(sum(1, 2, 3, 4) === 10, 'Sum of first four numbers is 10');

