import { display } from 'sicp';

const f = makef(1/2);

display(f(0) + f(1));
display(f(1) + f(0));

function makef(i) {
    return x => {
        i = x-i;
        return i;
    }
}

