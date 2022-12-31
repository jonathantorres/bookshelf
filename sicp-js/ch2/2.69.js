import {
    pair, head, tail, display, display_list, list,
    is_null, append, error, equal, length, reverse
} from 'sicp';

const t = make_code_tree(make_leaf("A", 4),
                            make_code_tree(make_leaf("B", 2),
                                           make_code_tree(
                                                make_leaf("D", 1),
                                                make_leaf("C", 1))));

const f = list(list("A", 4), list("B", 2), list("C", 1), list("D", 1));

display(equal(t, generate_huffman_tree(f)));

function generate_huffman_tree(pairs) {
    return successive_merge(make_leaf_set(pairs));
}

function successive_merge(pairs) {
    function merge(pairs) {
        if (length(pairs) == 2) {
            return make_code_tree(head(tail(pairs)), head(pairs));
        }
        return make_code_tree(head(pairs), merge(tail(pairs)));
    }
    return merge(reverse(pairs));
}

function make_leaf_set(pairs) {
    if (is_null(pairs)) {
        return null;
    } else {
        const first_pair = head(pairs);
        return adjoin_set(
                   make_leaf(head(first_pair),        // symbol
                             head(tail(first_pair))), // frequency
                   make_leaf_set(tail(pairs)));
    }
}

function make_code_tree(left, right) {
    return list("code_tree", left, right,
                append(symbols(left), symbols(right)),
                weight(left) + weight(right));
}

function adjoin_set(x, set) {
    return is_null(set)
           ? list(x)
           : weight(x) < weight(head(set))
           ? pair(x, set)
           : pair(head(set), adjoin_set(x, tail(set)));
}

function symbols(tree) {
    return is_leaf(tree)
           ? list(symbol_leaf(tree))
           : head(tail(tail(tail(tree))));
}

function weight(tree) {
    return is_leaf(tree)
           ? weight_leaf(tree)
           : head(tail(tail(tail(tail(tree)))));
}

function make_leaf(symbol, weight) {
    return list("leaf", symbol, weight);
}

function is_leaf(object) {
    return head(object) === "leaf";
}

function symbol_leaf(x) { return head(tail(x)); }

function weight_leaf(x) { return head(tail(tail(x))); }

function left_branch(tree) { return head(tail(tree)); }

function right_branch(tree) { return head(tail(tail(tree))); }
