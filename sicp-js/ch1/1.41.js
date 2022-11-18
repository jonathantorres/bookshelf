import { display } from 'sicp';

display(double(inc)(1));

// this call applies the same function 16 times, thus it returns 21
display(double(double(double))(inc)(5));

function double(f) {
   return x => f(f(x));
}

function inc(n) {
    return n+1;
}

