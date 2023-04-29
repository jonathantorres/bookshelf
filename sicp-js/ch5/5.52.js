// use the compiler to run this code

// adding new operation
const exec_compiler_ops = append(eceval_operations, list(list("compile_and_assemble", compile_and_assemble)));

// loop stays the same as the compiler
const controller = list(
    "read_compile_execute_print_loop",
    perform(list(op("initialize_stack"))),
    perform(list(op("initialize_stack"))),
    assign("comp", list(op("user_read"), constant("EC-Comp input:"))),
    assign("env", list(op("get_current_environment"))),
    assign("continue", label("print_result")),
    go_to(label("compile_and_execute")),

    "print_result",
    perform(list(op("print_stack_statistics"))),
    perform(list(op("announce_output"), constant("EC-Comp value:"))),
    perform(list(op("user_print"), reg("val"))),
    go_to(label("read_compile_execute_print_loop")),

    // rest of the evaluator goes here
    "compile_and_execute",
    assign("val", list(op("compile_and_assemble"), reg("expr"))),
    go_to(reg("val")),
);

const machine = make_machine(
    list("expr", "env", "val", "fun", "argl", "continue", "unev"),
    exec_compiler_ops,
    controller
);

function compile_and_assemble(component) {
    return assemble(
        instructions(compile(component, "val", "return"), machine)
    );
}

function start_compiler() {
    the_global_environment = setup_environment();
    machine("start");
}

start_compiler();
