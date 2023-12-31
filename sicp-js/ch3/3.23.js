import {
    display, is_pair, is_null, list, pair, head, equal,
    tail, set_head, set_tail, error, member, append, display_list
} from 'sicp';

// we use a doubly linked list to make insertions and deletions in constant time

const d = make_deque();
rear_insert_deque(d, "a");
rear_insert_deque(d, "b");
rear_insert_deque(d, "c");
front_insert_deque(d, "f");
rear_delete_deque(d);
print_deque(d);

function print_deque(d) {
    if (is_empty_deque(d)) {
        display("[]");
        return d;
    }
    display("[");
    function loop(n) {
        display(node_val(n));
        if (is_null(right_link(n))) {
            return "ok";
        }
        loop(right_link(n));
    }
    loop(front_ptr(d));
    display("]");
    return d;
}

function front_deque(d) {
    if (is_empty_deque(d)) {
        return error(d, "front_deque called with an empty deque");
    }

    return node_val(front_ptr(d));
}

function rear_deque(d) {
    if (is_empty_deque(d)) {
        return error(d, "rear_deque called with an empty deque");
    }

    return node_val(rear_ptr(d));
}

function front_delete_deque(d) {
    if (is_empty_deque(d)) {
        error(d, "delete_deque called with an empty deque");
    } else {
        let new_front = null;
        if (!is_null(right_link(front_ptr(d)))) {
            new_front = right_link(front_ptr(d));
            set_left_link(new_front, null);
        }
        set_front_ptr(d, new_front);
        return d;
    }
}

function rear_delete_deque(d) {
    if (is_empty_deque(d)) {
        error(d, "delete_deque called with an empty deque");
    } else {
        let new_rear = null;
        if (!is_null(left_link(rear_ptr(d)))) {
            new_rear = left_link(rear_ptr(d));
            set_right_link(new_rear, null);
        }
        set_rear_ptr(d, new_rear);
        return d;
    }
}

function rear_insert_deque(d, item) {
    const new_node = make_node(item);
    if (is_empty_deque(d)) {
        set_front_ptr(d, new_node);
        set_rear_ptr(d, new_node);
    } else {
        set_left_link(new_node, rear_ptr(d));
        set_right_link(rear_ptr(d), new_node);
        set_rear_ptr(d, new_node);
    }
    return d;
}

function front_insert_deque(d, item) {
    const new_node = make_node(item);
    if (is_empty_deque(d)) {
        set_front_ptr(d, new_node);
        set_rear_ptr(d, new_node);
    } else {
        set_right_link(new_node, front_ptr(d));
        set_left_link(front_ptr(d), new_node);
        set_front_ptr(d, new_node);
    }
    return d;
}

function front_ptr(d) { return head(d); }

function rear_ptr(d) { return tail(d); }

function set_front_ptr(d, item) { set_head(d, item); }

function set_rear_ptr(d, item) { set_tail(d, item); }

function is_empty_deque(d) { return is_null(front_ptr(d)); }

function make_deque() { return pair(null, null); }

function make_node(v) {
    return pair(null, pair(v, null));
}

function node_val(n) {
    return head(tail(n));
}

function right_link(n) {
    return tail(tail(n));
}

function left_link(n) {
    return head(n);
}

function set_left_link(n, val) {
    set_head(n, val);
}

function set_right_link(n, val) {
    set_tail(tail(n), val);
}
