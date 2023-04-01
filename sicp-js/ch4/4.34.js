// this program must be run from the Source environment
// using the Non-deterministic variant
// https://sourceacademy.org/playground
function an_integer_starting_from(n) {
    return amb(n, an_integer_starting_from(n + 1));
}

function pythagorean_triple_gt(low) {
    const k = an_integer_starting_from(low);
    const i = an_integer_between(low, k);
    const j = an_integer_between(i, k);

    require((i*i)+(j*j) === k*k);
    return list(i, j, k);
}

pythagorean_triple_gt(10);
