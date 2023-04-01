// this program must be run from the Source environment
// using the Non-deterministic variant
// https://sourceacademy.org/playground
function an_integer_between(low, high) {
    require(low <= high);
    return amb(low, an_integer_between(low+1, high));
}

function a_pythogorean_triple_between(low, high) {
    const i = an_integer_between(low, high);
    const j = an_integer_between(i, high);
    const k = an_integer_between(j, high);
    require(i * i + j * j === k * k);
    return list(i, j, k);
}

a_pythogorean_triple_between(5, 15);

