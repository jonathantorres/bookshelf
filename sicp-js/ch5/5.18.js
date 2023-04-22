// changes on make_new_machine
function make_new_machine() {
    const pc = make_register("pc");
    const flag = make_register("flag");
    const stack = make_stack();
    let labels = null;
    let current_label = "**unassigned**";
    let current_line = 0;
    let breakpoint_line = 0;
    let breakpoint = true;
    let the_instruction_sequence = null;
    let the_ops = list(list("initialize_stack", () => stack("initialize")));
    let register_table = list(list("pc", pc), list("flag", flag));

    function allocate_register(name) {
        if (is_undefined(assoc(name, register_table))) {
            register_table = pair(list(name, make_register(name)),
                                  register_table);
        } else {
            error(name, "multiply defined register");
        }
        return "register allocated";
    }
    function lookup_register(name) {
        const val = assoc(name, register_table);
        return is_undefined(val)
               ? error(name, "unknown register")
               : head(tail(val));
    }
    function execute() {
        const insts = get_contents(pc);
        if (is_null(insts)) {
            return "done";
        }
        if (!is_null(head(insts))) {
            assoc(instruction_label(head(insts)), labels);
            current_label = instruction_label(head(insts));
            breakpoint_line = tail(assoc(current_label, labels));
            current_line = 0
        }

        current_line = current_line + 1;
        if (breakpoint && current_line === breakpoint_line) {
            breakpoint = false;
            display(list("breakpoint placed here", current_label, current_line));
        }

        breakpoint = true;
        inst_execution_fun(head(insts))();
        return execute();
    }
    function cancel_breakpoint_label(label) {
        function delete_label(cur_labels, orig_labels) {
            if (is_null(orig_labels)) {
                error("Label was not found", label);
            }
            if (head(tail(orig_labels)) === label) {
                cur_labels = append(cur_labels, head(orig_labels));
            } else {
                delete_label(pair(head(orig_labels), cur_labels), tail(orig_labels));
            }
        }
        labels = delete_label(null, labels);
    }
    function dispatch(message) {
        function start() {
            set_contents(pc, the_instruction_sequence);
            return execute();
        }
        return message === "start"
               ? start()
               : message === "install_instruction_sequence"
               ? seq => { the_instruction_sequence = seq; }
               : message === "allocate_register"
               ? allocate_register
               : message === "get_register"
               ? lookup_register
               : message === "install_operations"
               ? ops => { the_ops = append(the_ops, ops); }
               : message === "stack"
               ? stack
               : message === "operations"
               ? the_ops
               : message === "set_breakpoint"
               ? (label, n) => { labels = pair(pair(label, n), labels); }
               : message === "cancel_breakpoint"
               ? label => cancel_breakpoint(label)
               : message === "cancel_all_breakpoints"
               ? labels = null
               : error(message, "unknown request -- machine");
    }
    return dispatch;
}

// breakpoint functions
function set_breakpoint(machine, label, n) {
    return machine("set_breakpoint")(label, n);
}

function cancel_breakpoint(machine, label) {
    return machine("cancel_breakpoint")(label);
}

function cancel_all_breakpoints(machine) {
    return machine("cancel_all_breakpoints")();
}
