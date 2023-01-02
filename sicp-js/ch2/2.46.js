import { pair, head, tail, display, display_list } from 'sicp';

const v1 = make_vect(1, 2);
const v2 = make_vect(3, 4);

display(add_vect(v1, v2));
display(sub_vect(v1, v2));
display(scale_vect(2, v1));

function scale_vect(s, v) {
    return make_vect(
        s*xcor_vect(v),
        s*ycor_vect(v)
    );
}

function sub_vect(v1, v2) {
    return make_vect(
        xcor_vect(v1) - xcor_vect(v2),
        ycor_vect(v1) - ycor_vect(v2),
    );
}

function add_vect(v1, v2) {
    return make_vect(
        xcor_vect(v1) + xcor_vect(v2),
        ycor_vect(v1) + ycor_vect(v2),
    );
}

function make_vect(x, y) {
    return pair(x, y);
}

function xcor_vect(v) {
    return head(v);
}

function ycor_vect(v) {
    return tail(v);
}
