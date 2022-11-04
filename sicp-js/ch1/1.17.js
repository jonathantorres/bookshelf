import { display } from 'sicp';

display(fast_times(2, 5));
display(fast_times(5, 5));
display(fast_times(10, 100));

function fast_times(a, b) {
    if (b === 0) {
        return 0;
    }
    if (is_even(b)) {
       return double(fast_times(a, halve(b)));
    }
    return a+fast_times(a, b-1);
}

function is_even(n) {
    return n%2 === 0;
}

function double(n) {
    return 2*n;
}

function halve(n) {
   return n/2;
}

