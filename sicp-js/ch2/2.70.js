import {
    pair, head, tail, display, display_list, list,
    is_null, append, error, equal, length, reverse, member
} from 'sicp';

const freq = list(
    list("A", 2), list("BOOM", 1),
    list("GET", 2), list("JOB", 2),
    list("NA", 16), list("SHA", 3),
    list("YIP", 9), list("WHA", 1)
);

const t = generate_huffman_tree(freq);

const msg = list(
    "GET", "A", "JOB",
    "SHA", "NA", "NA", "NA", "NA", "NA", "NA", "NA", "NA",
    "GET", "A", "JOB",
    "SHA", "NA", "NA", "NA", "NA", "NA", "NA", "NA", "NA",
    "WHA", "YIP", "YIP", "YIP", "YIP", "YIP", "YIP", "YIP", "YIP", "YIP",
    "SHA", "BOOM"
);
const encoded_msg = encode(msg, t);

// 84 bits are required to encode this message
display_list(encoded_msg);
display_list(length(encoded_msg));

function generate_huffman_tree(pairs) {
    return successive_merge(make_leaf_set(pairs));
}

function successive_merge(pairs) {
    if (length(pairs) == 1) {
        return head(pairs);
    }
    return successive_merge(
        adjoin_set(
            make_code_tree(head(pairs), head(tail(pairs))),
            tail(tail(pairs))
        )
    );
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

function encode(message, tree) {
    if (is_null(message)) {
        return null;
    }
    return append(encode_symbol(head(message), tree), encode(tail(message), tree));
}

function encode_symbol(symbol, tree) {
    if (is_null(symbol)) {
        return null;
    }
    const next_branch_bit = choose_side(symbol, tree);
    const next_branch = head(next_branch_bit);
    const bit = tail(next_branch_bit);

    if (is_leaf(next_branch)) {
        return pair(bit, null);
    }
    return pair(bit, encode_symbol(symbol, next_branch));
}

function choose_side(symbol, branch) {
    const l = left_branch(branch);
    const r = right_branch(branch);

    if (is_leaf(l)) {
        if (equal(symbol, symbol_leaf(l))) {
            return pair(l, 0);
        }
        return pair(r, 1);
    }
    if (is_element_of_set(symbol, symbols(l))) {
        return pair(l, 0);
    }

    if (is_leaf(r)) {
        if (equal(symbol, symbol_leaf(r))) {
            return pair(r, 1);
        }
        return pair(l, 0);
    }
    if (is_element_of_set(symbol, symbols(r))) {
        return pair(r, 1);
    }
    return error(symbol, "bad symbol -- choose_branch");
}

function is_element_of_set(x, set) {
    return !is_null(member(x, set));
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
