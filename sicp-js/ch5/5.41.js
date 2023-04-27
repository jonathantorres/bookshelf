// changes in the compile function
function compile(component, target, linkage) {
    return is_literal(component)
           ? compile_literal(component, target, linkage)
           : is_name(component)
           ? compile_name(component, target, linkage)
           : is_open_coded(component)
           ? compile_open_coded(component, target, linkage)
           : is_application(component)
           ? compile_application(component, target, linkage)
           : is_operator_combination(component)
           ? compile(operator_combination_to_application(component), target, linkage)
           : is_conditional(component)
           ? compile_conditional(component, target, linkage)
           : is_lambda_expression(component)
           ? compile_lambda_expression(component, target, linkage)
           : is_sequence(component)
           ? compile_sequence(sequence_statements(component), target, linkage)
           : is_block(component)
           ? compile_block(component, target, linkage)
           : is_return_statement(component)
           ? compile_return_statement(component, target, linkage)
           : is_function_declaration(component)
           ? compile(function_decl_to_constant_decl(component), target, linkage)
           : is_declaration(component)
           ? compile_declaration(component, target, linkage)
           : is_assignment(component)
           ? compile_assignment(component, target, linkage)
           : error(component, "unknown component type -- compile");
}

function compile_open_coded(component, target, linkage) {
    const oper = head(component);
    const args = open_args(tail(component), head(tail(component)));

    return end_with_linkage(
        linkage,
        append_instruction_sequences(
            head(args),
            preserving(
                list("arg1"),
                head(tail(args)),
                make_instruction_sequence(
                    list("arg1", "arg2"),
                    list(target),
                    list(assign(target, list(op(oper), reg("arg1"), reg("arg2"))))
                )
            )
        )
    );
}

function open_args(op1, op2) {
    return list(
        compile(op1, "arg1", "next"),
        compile(op2, "arg2", "next")
    );
}

function is_open_coded(component) {
    return is_tagged_list(component, "===") ||
        is_tagged_list(component, "*") ||
        is_tagged_list(component, "-") ||
        is_tagged_list(component, "+");
}
