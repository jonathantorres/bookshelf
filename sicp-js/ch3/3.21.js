import {
    display, is_pair, is_null, list, pair, head, equal,
    tail, set_head, set_tail, error, member, append, display_list
} from 'sicp';

// Ben is printing the entire queue structure, which is the pair containing
// the list with the items of the queue and the pointer that points to the
// last item of the queue (if any), to print just the items of the queue
// we just have to print the list that starts from the front of the queue

const q = make_queue();
insert_queue(q, "a");
insert_queue(q, "b");
print_queue(q);

function make_queue() { return pair(null, null); }

function print_queue(queue) {
    if (is_empty_queue(queue)) {
        display("[]");
        return;
    }
    display(front_ptr(queue));
}

function front_queue(queue) {
    if (is_empty_queue(queue)) {
        return error(queue, "front_queue called with an empty queue");
    }

    return head(front_ptr(queue));
}

function delete_queue(queue) {
    if (is_empty_queue(queue)) {
        error(queue, "delete_queue called with an empty queue");
    } else {
        set_front_ptr(queue, tail(front_ptr(queue)));
        return queue;
    }
}

function insert_queue(queue, item) {
    const new_pair = pair(item, null);
    if (is_empty_queue(queue)) {
        set_front_ptr(queue, new_pair);
        set_rear_ptr(queue, new_pair);
    } else {
        set_tail(rear_ptr(queue), new_pair);
        set_rear_ptr(queue, new_pair);
    }
    return queue;
}

function is_empty_queue(queue) { return is_null(front_ptr(queue)); }

function front_ptr(queue) { return head(queue); }

function rear_ptr(queue) { return tail(queue); }

function set_front_ptr(queue, item) { set_head(queue, item); }

function set_rear_ptr(queue, item) { set_tail(queue, item); }
