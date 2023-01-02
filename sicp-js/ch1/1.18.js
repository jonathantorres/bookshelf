import { display } from 'sicp';

display(times(2, 2));
display(times(2, 10));
display(times(3, 10));
display(times(3, 300));
display(times(5, 500));

function times(a, b) {
    return times_iter(a, b, 0);
}

function times_iter(a, b, c) {
   if (b === 0)  {
      return c;
   }
   if (is_even(b)) {
      return times_iter(double(a), halve(b), c);
   }
   return times_iter(a, b-1, a+c);
}

function double(n) {
    return 2*n;
}

function halve(n) {
    return n/2;
}

function is_even(n) {
    return n % 2 === 0;
}

