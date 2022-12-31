import { display } from 'sicp';

// In applicative order evaluation, this program will crash.
// Since the recursion in p() does not end (no base case)
//
// In normal order evaluation, the crash won't happen
// since p() is not executed, because is not evaluated by
// the interpreter since "x" in test() is 0
// and thus test() will return 0

display(test(0, p()));

function p() {
    return p();
}

function test(x, y) {
    return x === 0 ? 0 : y;
}
