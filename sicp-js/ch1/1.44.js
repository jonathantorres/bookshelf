import { display } from 'sicp';

display(nfold_smooth(cube, 5)(3));

function nfold_smooth(f, n) {
    return repeated(smooth, n)(f);
}

function smooth(f) {
    const dx = 0.00001;
    return x => (f(x-dx) + f(x) + f(x+dx)) / 3;
}

function cube(n) {
    return n*n*n;
}

function compose(f, g) {
    return x => f(g(x));
}

function repeated(f, n) {
    if (n === 0) {
        return x => x;
    }
    return compose(f, repeated(f, n-1));
}
