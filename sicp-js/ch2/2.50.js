import { pair, head, tail, display, display_list, list, list_ref, for_each } from 'sicp';

const f = make_frame(
    make_vect(0, 0), // origin
    make_vect(1, 0), // edge 1
    make_vect(0, 1)  // edge 2
);

const diamond = segments_to_painter(
    list(
        make_segment(make_vect(0, 0.5), make_vect(0.5, 1)),
        make_segment(make_vect(0.5, 1), make_vect(1, 0.5)),
        make_segment(make_vect(1, 0.5), make_vect(0.5, 0)),
        make_segment(make_vect(0.5, 0), make_vect(0, 0.5))
    )
);

const rot90 = rotate90(diamond);
const horz = flip_horz(diamond);
const rot180 = rotate180(diamond);
const rot270 = rotate270(diamond);
display("Flip Horizontal -----------------------");
horz(f);

display("Rotate 90 -----------------------");
rot90(f);

display("Rotate 180 -----------------------");
rot180(f);

display("Rotate 270 -----------------------");
rot270(f);

function flip_horz(painter) {
    return transform_painter(
        painter,
        make_vect(1, 0),
        make_vect(0, 0),
        make_vect(1, 1)
    );
}

function rotate180(painter) {
    return transform_painter(
        painter,
        make_vect(1, 1),
        make_vect(0, 1),
        make_vect(1, 0)
    );
}

function rotate270(painter) {
    return transform_painter(
        painter,
        make_vect(0, 1),
        make_vect(0, 0),
        make_vect(1, 0)
    );
}

function rotate90(painter) {
    return transform_painter(
        painter,
        make_vect(1, 0),
        make_vect(1, 1),
        make_vect(0, 0)
    );
}

function transform_painter(painter, origin, corner1, corner2) {
    return frame => {
             const m = frame_coord_map(frame);
             const new_origin = m(origin);
             return painter(make_frame(
                                new_origin,
                                sub_vect(m(corner1), new_origin),
                                sub_vect(m(corner2), new_origin)));
           };
}

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

function scale_vect(s, v) {
    return make_vect(
        s*xcor_vect(v),
        s*ycor_vect(v)
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
