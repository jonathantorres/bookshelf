import {
    pair, head, tail, display, display_list, list, math_cos, math_sin,
    is_null, append, error, equal, length
} from 'sicp';

display(make_from_mag_ang(10, 10)("angle"));

function make_from_mag_ang(r, a) {
    function dispatch(op) {
        if (op === "real_part") {
            return dispatch("magnitude") * math_cos(dispatch("angle"));
        }
        if (op === "imag_part") {
            return dispatch("magnitude") * math_sin(dispatch("angle"));
        }
        if (op === "magnitude") {
            return r;
        }
        if (op === "angle") {
            return a;
        }
        return error(op, "unknown op -- make_from_mag_ang");
    }
    return dispatch;
}
