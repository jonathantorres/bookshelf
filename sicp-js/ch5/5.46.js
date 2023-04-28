// changes on compile_lambda_body
function compile_lambda_body(exp, fun_entry, env) {
    const params = lambda_parameter_symbols(exp);
    return append_instruction_sequences(
        make_instruction_sequence(list("env", "fun", "argl"), list("env"),
            list(fun_entry,
                 assign("env",
                        list(op("compiled_function_env"),
                             reg("fun"))),
                 assign("env",
                        list(op("extend_environment"),
                             constant(params),
                             reg("argl"),
                             reg("env"))))),
        compile_sequence(scan_out_declarations(lambda_body(exp)), "val", "return", pair(params, env)));
}
