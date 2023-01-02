import { pair, head, tail, display, display_list, list } from 'sicp';

const f = make_frame(1, 2, 3);
display(origin_frame(f));
display(edge1_frame(f));
display(edge2_frame(f));

// list version implementation
function make_frame(origin, edge1, edge2) {
    return list(origin, edge1, edge2);
}

function origin_frame(f) {
    return head(f);
}

function edge1_frame(f) {
    return head(tail(f));
}

function edge2_frame(f) {
    return head(tail(tail(f)));
}

// pair version implementation
function make_frame(origin, edge1, edge2) {
    return pair(origin, pair(edge1, edge2));
}

function origin_frame(f) {
    return head(f);
}

function edge1_frame(f) {
    return head(tail(f));
}

function edge2_frame(f) {
    return tail(tail(f));
}
