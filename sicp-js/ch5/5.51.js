function compile_and_run(program) {
    const stack = eceval("stack");
    const instrs = assemble(append(instructions(compile(program, "val", "next")), go_to(reg("print_result"))), eceval);

    stack("pop");
    stack("push", instrs);

    return start(eceval);
}
