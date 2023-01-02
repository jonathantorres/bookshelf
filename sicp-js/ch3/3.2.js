import { display, math_sqrt } from 'sicp';

const s = make_monitored(math_sqrt);

display(s(100));
display(s("how many calls"));
display(s(25));
display(s("how many calls"));
display(s("reset count"));
display(s("how many calls"));

function make_monitored(f) {
    let calls = 0;
    return input => {
        if (input === "how many calls") {
            return calls;
        } else if (input === "reset count") {
            calls = 0;
            return calls;
        }
        calls++;
        return f(input);
    };
}
