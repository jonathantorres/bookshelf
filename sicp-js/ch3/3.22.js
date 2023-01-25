import {
    display, is_pair, is_null, list, pair, head, equal,
    tail, set_head, set_tail, error, member, append, display_list
} from 'sicp';

const q = make_queue();
q("insert")("a");
q("insert")("b");
q("print")();
q("delete")();
q("print")();

function make_queue() {
    let front_ptr = null;
    let rear_ptr = null;

    // internal functions
    function insert_queue(item) {
        const new_pair = pair(item, null);
        if (is_empty_queue()) {
            set_front_ptr(new_pair);
            set_rear_ptr(new_pair);
        } else {
            set_tail(rear_ptr, new_pair);
            set_rear_ptr(new_pair);
        }
    }

    function delete_queue() {
        if (is_empty_queue()) {
            return error("delete_queue called with an empty queue");
        } else {
            set_front_ptr(tail(front_ptr));
        }
    }

    function print_queue() {
        if (is_empty_queue()) {
            display("[]");
            return;
        }
        display(front_ptr);
    }

    function is_empty_queue() { return is_null(front_ptr); }

    function set_front_ptr(p) { front_ptr = p; }

    function set_rear_ptr(p) { rear_ptr = p; }

    function dispatch(m) {
        if (m === "insert") {
            return insert_queue;
        } else if (m === "delete") {
            return delete_queue;
        } else if (m === "print") {
            return print_queue;
        } else {
            return error("unknown queue operation", m);
        }
    }
    return dispatch;
}
