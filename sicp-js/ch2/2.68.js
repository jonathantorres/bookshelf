import {
    pair, head, tail, display, display_list,
    list, is_null, append, error, equal
} from 'sicp';

const t = make_code_tree(make_leaf("A", 4),
                            make_code_tree(make_leaf("B", 2),
                                           make_code_tree(
                                                make_leaf("D", 1),
                                                make_leaf("C", 1))));

const msg = list("A", "D", "A", "B", "B", "C", "A");

display(equal(
    decode(encode(msg, t), t),
    msg
));

function encode(message, tree) {
    if (is_null(message)) {
        return null;
    }
    return append(encode_symbol(head(message), tree), encode(tail(message), tree));
}

function decode(bits, tree) {
    function decode_1(bits, current_branch) {
        if (is_null(bits)) {
            return null;
        } else {
            const next_branch = choose_branch(head(bits),
                                              current_branch);
            return is_leaf(next_branch)
                   ? pair(symbol_leaf(next_branch),
                          decode_1(tail(bits), tree))
                   : decode_1(tail(bits), next_branch);
        }
    }
    return decode_1(bits, tree);
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

function choose_branch(bit, branch) {
    return bit === 0
           ? left_branch(branch)
           : bit === 1
           ? right_branch(branch)
           : error(bit, "bad bit -- choose_branch");
}

function make_code_tree(left, right) {
    return list("code_tree", left, right,
                append(symbols(left), symbols(right)),
                weight(left) + weight(right));
}

function left_branch(tree) { return head(tail(tree)); }

function right_branch(tree) { return head(tail(tail(tree))); }

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
