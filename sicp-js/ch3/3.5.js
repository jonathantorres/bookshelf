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
   return () => {
              x = rand_update(x);
              return x;
          };
}
const rand = make_rand();

display(estimate_integral(pred, -1, 1, -1, 1, 9000));

function estimate_integral(p, x1, x2, y1, y2, trials) {
    const area = (x2-x1)*(y2-y1);
    function experiment() {
        return p(random_in_range(x1, x2), random_in_range(y1, y2));
    }
    return monte_carlo(trials, experiment) * area;
}

function pred(x, y) {
    return square(x) + square(y) <= 1;
}

function estimate_pi(trials) {
    return math_sqrt(6 / monte_carlo(trials, dirichlet_test));
}

function dirichlet_test() {
    return gcd(rand(), rand()) === 1;
}

function monte_carlo(trials, experiment) {
    function iter(trials_remaining, trials_passed) {
        return trials_remaining === 0
               ? trials_passed / trials
               : experiment()
               ? iter(trials_remaining - 1, trials_passed + 1)
               : iter(trials_remaining - 1, trials_passed);
    }
    return iter(trials, 0);
}

function random_in_range(low, high) {
    const range = high - low;
    return low + math_random() * range;
}

function gcd(a, b) {
    return b === 0 ? a : gcd(b, a % b);
}

function square(n) {
    return n*n;
}
