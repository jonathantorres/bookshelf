// changes on make_operation_exp_ef
function make_operation_exp_ef(exp, machine, labels, operations) {
    const op = lookup_prim(operation_exp_op(exp), operations);
    const afuns = map(
        e => {
            if (is_label_exp(e)) {
                return error(e, "Cannot make operation on label");
            }
            return make_primitive_exp_ef(e, machine, labels);
        },
        operation_exp_operands(exp)
    );
    return () => apply_in_underlying_javascript(
                     op, map(f => f(), afuns));
}

function label_exp_label(exp) { return head(tail(exp)); }
