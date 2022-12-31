import { pair, head, tail, display, display_list, list, list_ref, for_each } from 'sicp';

// 1. The painter that draws the outline of the designated frame
const f1 = make_frame(
    make_vect(0, 0), // origin
    make_vect(1, 0), // edge 1
    make_vect(0, 1)  // edge 2
);
const p1 = segments_to_painter(
    list(
        make_segment(make_vect(0, 0), make_vect(1, 0)),
        make_segment(make_vect(1, 0), make_vect(1, 1)),
        make_segment(make_vect(1, 1), make_vect(0, 1)),
        make_segment(make_vect(0, 1), make_vect(0, 0)),
    )
);
p1(f1);
display("-----------------------");

// 2. The painter that draws an "X" by connecting opposite corners of the frame.
const f2 = make_frame(
    make_vect(0, 0), // origin
    make_vect(1, 0), // edge 1
    make_vect(0, 1)  // edge 2
);
const p2 = segments_to_painter(
    list(
        make_segment(make_vect(0, 0), make_vect(1, 1)),
        make_segment(make_vect(0, 1), make_vect(1, 0))
    )
);
p2(f2);
display("-----------------------");

// 3. The painter that draws a diamond shape by connecting the midpoints of the sides of the frame.
const f3 = make_frame(
    make_vect(0, 0), // origin
    make_vect(1, 0), // edge 1
    make_vect(0, 1)  // edge 2
);
const p3 = segments_to_painter(
    list(
        make_segment(make_vect(0, 0.5), make_vect(0.5, 1)),
        make_segment(make_vect(0.5, 1), make_vect(1, 0.5)),
        make_segment(make_vect(1, 0.5), make_vect(0.5, 0)),
        make_segment(make_vect(0.5, 0), make_vect(0, 0.5))
    )
);
p3(f3);
display("-----------------------");

function segments_to_painter(segment_list) {
    return frame =>
             for_each(segment =>
                        draw_line(
                            frame_coord_map(frame)
                                (start_segment(segment)),
                            frame_coord_map(frame)
                                (end_segment(segment))),
                      segment_list);
}

// "drawing a line" here simulated
// by printing the coordinates of
// the start and end of the line
function draw_line(v_start, v_end) {
    display("line starting at");
    display(v_start);
    display("line ending at");
    display(v_end);
}

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

function make_frame(origin, edge1, edge2) {
    return list(origin, edge1, edge2);
}

function origin_frame(frame) {
    return list_ref(frame, 0);
}

function edge1_frame(frame) {
    return list_ref(frame, 1);
}

function edge2_frame(frame) {
    return list_ref(frame, 2);
}

function frame_coord_map(frame) {
    return v => add_vect(origin_frame(frame),
                         add_vect(scale_vect(xcor_vect(v),
                                             edge1_frame(frame)),
                                  scale_vect(ycor_vect(v),
                                             edge2_frame(frame))));
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

function make_segment(start, end) {
    return pair(start, end);
}

function start_segment(s) {
    return head(s);
}

function end_segment(s) {
    return tail(s);
}
