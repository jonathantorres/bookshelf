import { display, error, math_sqrt, math_random } from 'sicp';

const m = 200560490131;
const a = 1103515245;
const b = 12345;
const random_init = 123456789;

function rand_update(x) {
    return (a * x + b) % m;
}

function make_rand() {
    let x = random_init;
    return (kind) => {
        if (kind === "generate") {
            x = rand_update(x);
            return x;
        } else if (kind === "reset") {
            return (val) => {
                x = val;
            }
        } else {
            return error("unknown kind value --- ", kind);
        }
    };
}
const rand = make_rand();

display(rand("generate"));
display(rand("generate"));
display(rand("generate"));
rand("reset")(987654321);
display(rand("generate"));
display(rand("generate"));
display(rand("generate"));
