import {
    pair, head, tail, display, display_list, list,
    equal, is_null, append, length, math_floor
} from 'sicp';

const planets = make_tree(make_record(4, "Mars"),
              make_tree(make_record(2, "Venus"),
                        null,
                        make_tree(make_record(3, "Earth"),
                                  null, null)),
              make_tree(make_record(6, "Saturn"),
                        make_tree(make_record(5, "Jupiter"),
                                  null, null),
                        null));

display(lookup(3, planets));

function lookup(id, db) {
    if (is_null(db)) {
        return false;
    }
    const e = key(entry(db));

    if (equal(id, e)) {
        return entry(db);
    }
    if (id < e) {
        return lookup(id, left_branch(db));
    }
    return lookup(id, right_branch(db));
}

function key(record) {
    return head(record);
}

function make_record(id, name) {
    return pair(id, name);
}

function entry(tree) { return head(tree); }

function left_branch(tree) { return head(tail(tree)); }

function right_branch(tree) { return head(tail(tail(tree))); }

function make_tree(entry, left, right) {
    return list(entry, left, right);
}

