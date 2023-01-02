import {
    pair, head, tail, display, display_list, list,
    equal, is_null, append, length, math_floor
} from 'sicp';

const x = list_to_tree(list(1, 2, 3));
const y = list_to_tree(list(3, 4, 5));

display_list(tree_to_list(intersection_set(x, y))); // list(3)
display_list(tree_to_list(union_set(x, y))); // list(1, 2, 3, 4, 5)

function intersection_set(set1, set2) {
    if (is_null(set1) || is_null(set2)) {
        return null;
    }
    const l1 = tree_to_list(set1);
    const l2 = tree_to_list(set2);

    return list_to_tree(intersection_set_list(l1, l2));
}

function union_set(set1, set2) {
    if (is_null(set1)) {
        return set2;
    }
    if (is_null(set2)) {
        return set1;
    }
    const l1 = tree_to_list(set1);
    const l2 = tree_to_list(set2);

    return list_to_tree(union_set_list(l1, l2));
}

function union_set_list(set1, set2) {
    if (is_null(set1)) {
        return set2;
    }
    if (is_null(set2)) {
        return set1;
    }

    const x1 = head(set1);
    const x2 = head(set2);

    if (x1 === x2) {
        return pair(x1, union_set_list(tail(set1), tail(set2)));
    } else if (x1 < x2) {
        return pair(x1, union_set_list(tail(set1), set2));
    }

    return pair(x2, union_set(set1, tail(set2)));
}

function intersection_set_list(set1, set2) {
    if (is_null(set1) || is_null(set2)) {
        return null;
    }
    const x1 = head(set1);
    const x2 = head(set2);

    return x1 === x2
           ? pair(x1, intersection_set_list(tail(set1), tail(set2)))
           : x1 < x2
           ? intersection_set_list(tail(set1), set2)
           : // x2 < x1
         intersection_set_list(set1, tail(set2));
}


function tree_to_list(tree) {
    function copy_to_list(tree, result_list) {
        return is_null(tree)
               ? result_list
               : copy_to_list(left_branch(tree),
                              pair(entry(tree),
                                   copy_to_list(right_branch(tree),
                                                result_list)));
    }
    return copy_to_list(tree, null);
}

function list_to_tree(elements) {
    function partial_tree(elts, n) {
        if (n === 0) {
            return pair(null, elts);
        } else {
            const left_size = math_floor((n - 1) / 2);
            const left_result = partial_tree(elts, left_size);
            const left_tree = head(left_result);
            const non_left_elts = tail(left_result);
            const right_size = n - (left_size + 1);
            const this_entry = head(non_left_elts);
            const right_result = partial_tree(tail(non_left_elts), right_size);
            const right_tree = head(right_result);
            const remaining_elts = tail(right_result);
            return pair(make_tree(this_entry, left_tree, right_tree),
                        remaining_elts);
        }
    }
    return head(partial_tree(elements, length(elements)));
}

function entry(tree) { return head(tree); }

function left_branch(tree) { return head(tail(tree)); }

function right_branch(tree) { return head(tail(tail(tree))); }

function make_tree(entry, left, right) {
    return list(entry, left, right);
}
