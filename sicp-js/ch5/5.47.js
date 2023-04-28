function compile_name(component, target, linkage, env) {
    const symbol = find_symbol(component, env);

    if (symbol === "not-found") {
        return end_with_linkage(linkage,
                   make_instruction_sequence(list("env"), list(target),
                       list(assign(target,
                                   list(op("lookup_symbol_value"),
                                        constant(symbol),
                                        reg("env"))))));
    } else {
        return end_with_linkage(linkage,
                   make_instruction_sequence(list("env"), list(target),
                       list(assign(target,
                                   list(op("lexical_address_lookup"),
                                        constant(symbol),
                                        reg("env"))))));
    }
}

function find_symbol(symbol, env) {
    function search_symbol(v, l, n) {
        if (is_null(l)) {
            return false;
        }
        if (equal(v, head(l))) {
            return n;
        }
        return search_symbol(v, tail(l), n+1);
    }

    function search_frame(frames, i) {
        if (is_null(frames)) {
            return "not-found";
        }

        let other = search_symbol(symbol, head(frames), 0);
        if (other) {
            return pair(i, other);
        }

        return search_frame(tail(frames), i+1);
    }

    return search_frame(env, 0);
}

function compile_function_call(target, linkage) {
    const primitive_branch = make_label("primitive_branch");
    const compiled_branch = make_label("compiled_branch");
    const after_call = make_label("after_call");
    const compiled_linkage = linkage === "next" ? after_call : linkage;

    return append_instruction_sequences(
        make_instruction_sequence(list("fun"), null,
            list(test(list(op("is_primitive_function"), reg("fun"))),
                 branch(label(primitive_branch)))),
        append_instruction_sequences(
            parallel_instruction_sequences(
                append_instruction_sequences(
                    compiled_branch,
                    compile_fun_appl(target, compiled_linkage)),
                append_instruction_sequences(
                    primitive_branch,
                    end_with_linkage(linkage,
                        make_instruction_sequence(list("fun", "argl"),
                                                  list(target),
                            list(assign(
                                   target,
                                   list(op("apply_primitive_function"),
                                        reg("fun"), reg("argl")))))))),
            after_call));
}
