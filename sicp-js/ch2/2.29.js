import { display, display_list, list, head, tail, is_null, pair, is_pair } from 'sicp';

// weight = 2
// balanced = false
const a = make_mobile(
    make_branch(1, 1),
    make_branch(2, 1),
);

// weight = 4
// balanced = true
const b = make_mobile(
    make_branch(2, make_mobile(
        make_branch(2, 1),
        make_branch(2, 1),
    )),
    make_branch(2, make_mobile(
        make_branch(2, 1),
        make_branch(2, 1),
    ))
);

display(total_weight(a));
display(total_weight(b));

display(is_balanced(a));
display(is_balanced(b));

// 1. Implement left_branch, right_branch, branch_length and branch_structure
function branch_length(branch) {
    return head(branch);
}

function branch_structure(branch) {
    return head(tail(branch));
}

function left_branch(mobile) {
    return head(mobile);
}

function right_branch(mobile) {
    return head(tail(mobile));
}

// 2. Implement total_weight
function total_weight(mobile) {
    if (is_null(mobile)) {
        return 0;
    }
    if (!is_pair(mobile)) {
        return mobile;
    }
    return total_weight(branch_structure(left_branch(mobile)))
        + total_weight(branch_structure(right_branch(mobile)));
}

// 3. Implement a function that tests whether a mobile is balanced or not
function is_balanced(mobile) {
    if (!is_pair(mobile)) {
        return true;
    }
    const l = branch_length(left_branch(mobile)) * total_weight(branch_structure(left_branch(mobile)));
    const r = branch_length(right_branch(mobile)) * total_weight(branch_structure(right_branch(mobile)));

    return l === r
        && is_balanced(branch_structure(left_branch(mobile)))
        && is_balanced(branch_structure(right_branch(mobile)));
}

// 4. If the mobiles are represented using pairs instead of lists, we'd have to
//    remove the "head()" calls from the branch_structure function
//    and the right_branch function, since the "tail()" calls in them
//    no longer return a list, but the actual value.
//
//    These calls would look like this:
//    function right_branch(mobile) {
//        return tail(mobile);
//    }
//    function branch_structure(branch) {
//        return tail(branch);
//    }
//

function make_mobile(left, right) {
    return list(left, right);
}

function make_branch(length, structure) {
    return list(length, structure);
}

