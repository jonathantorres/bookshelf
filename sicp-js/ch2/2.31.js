import { display, display_list, list, head, tail, is_null, pair, is_pair, map } from 'sicp';

const l = list(1, list(2, list(3,4), 5), list(6, 7));

display_list(square_tree(l));

function square_tree(tree) {
    return tree_map(square, tree);
}

function tree_map(f, tree) {
    return map(sub => {
        if (!is_pair(sub)) {
            return f(sub);
        }
        return tree_map(f, sub);
    }, tree);
}

function square(n) {
    return n*n;
}

