import { display, display_list, list, head, tail, is_null, pair, is_pair, map } from 'sicp';

const l = list(1, list(2, list(3,4), 5), list(6, 7));

display_list(square_tree(l));
display_list(square_tree_map(l));

function square_tree(tree) {
    if (is_null(tree)) {
        return tree;
    }
    if (!is_pair(tree)) {
        return square(tree);
    }
    return pair(square_tree(head(tree)), square_tree(tail(tree)));
}

function square_tree_map(tree) {
    return map(sub => {
        if (!is_pair(sub)) {
            return square(sub);
        }
        return square_tree_map(sub);
    }, tree);
}

function square(n) {
    return n*n;
}

