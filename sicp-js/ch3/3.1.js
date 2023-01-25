import { display } from 'sicp';

const a = make_accumulator(5);

display(a(10));
display(a(10));

function make_accumulator(sum) {
    return amount => {
        return sum += amount;
    };
}
