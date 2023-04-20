// a. Updated fibonacci register machine
controller(
  list(
    assign("continue", label("fib_done")),
  "fib_loop",
    test(list(op("<"), reg("n"), constant(2))),
    branch(label("immediate_answer")),
    save("continue"),
    assign("continue", label("afterfib_n_1")),
    save("n"),
    assign("n", list(op("-"), reg("n"), constant(1))),
    go_to(label("fib_loop")),
  "afterfib_n_1",
    restore("n"),
    restore("continue"),
    assign("n", list(op("-"), reg("n"), constant(2))),
    save("continue"),
    assign("continue", label("afterfib_n_2")),
    save("val"),
    go_to(label("fib_loop")),
  "afterfib_n_2",
    restore("n"),
    restore("continue"),
    assign("val", list(op("+"), reg("val"), reg("n"))),
    go_to(reg("continue")),
  "immediate_answer",
    assign("val", reg("n")),
    go_to(reg("continue")),
  "fib_done"))


// b. Code changes on make_save_ef and on make_restore_ef
function make_save_ef(inst, machine, stack, pc) {
    const reg = get_register(machine, stack_inst_reg_name(inst));
    return () => {
       push(stack, pair(stack_inst_reg_name(inst), get_contents(reg)));
       advance_pc(pc);
   };
}

function make_restore_ef(inst, machine, stack, pc) {
    const reg_name = stack_inst_reg_name(inst);
    const reg = get_register(machine, reg_name);
    return () => {
        const pop_reg = pop(stack);
        if (equal(head(pop_reg), reg_name)) {
            set_contents(reg, pop(stack));
            advance_pc(pc);
        } else {
            error(reg_name, "This values does not belong to the register");
        }
   };
}


// c. Code changes on make_stack, make_save_ef and make_restore_ef
function make_stack() {
    let stack = null;
    function push(reg_name, x) {
        const reg = assoc(reg_name, stack);
        if (reg) {
            set_tail(reg, pair(x, tail(reg)));
            return "done";
        }
        return error(reg_name, "This register is not in the stack");
    }
    function pop(reg_name) {
        const reg = assoc(reg_name, stack);
        if (reg) {
            if (is_null(tail(reg))) {
                error(reg_name, "empty stack -- pop");
            } else {
                const top = head(tail(stack));
                set_tail(reg, tail(head(reg)));
                return top;
            }
        }
        return error(reg_name, "This register is not in the stack");
    }
    function initialize() {
        for_each(s => set_tail(s, null), stack);
        return "done";
    }
    function dispatch(message) {
        return message === "push"
               ? push
               : message === "pop"
               ? pop
               : message === "initialize"
               ? initialize()
               : error(message, "unknown request -- stack");
    }
    return dispatch;
}

function make_save_ef(inst, machine, stack, pc) {
    const reg = get_register(machine, stack_inst_reg_name(inst));
    return () => {
       push(stack, stack_inst_reg_name(inst), get_contents(reg));
       advance_pc(pc);
   };
}

function make_restore_ef(inst, machine, stack, pc) {
    const reg_name = stack_inst_reg_name(inst);
    const reg = get_register(machine, reg_name);
    return () => {
        const v = pop(stack, reg_name);
       set_contents(reg, v);
       advance_pc(pc);
   };
}
