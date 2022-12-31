// This program needs to be run on the SourceAcademy environment: https://sourceacademy.org/playground
import { beside, below, stack, show, heart } from 'rune';

function split(f1, f2) {
    return (painter, n) => {
        if (n === 0) {
            return painter;
        } else {
           const smaller = split(f1, f2)(painter, n-1);
           return f1(painter, f2(smaller, smaller));
        }
    };
}

const right_split = split(beside, stack);
const up_split = split(stack, beside);

show(right_split(heart, 4));
show(up_split(heart, 4));
