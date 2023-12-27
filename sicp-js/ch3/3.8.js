import { display } from 'sicp';

const f = makef();

display(f(0) + f(1));

function makef() {
    let last = 0;
    return (n) => {
        const tmp = last;
        last = n;
        return tmp;
    };
}
