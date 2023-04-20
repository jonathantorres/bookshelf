import {
    display, pair, head, tail, is_null, list, append, map, is_undefined,
    accumulate, list_ref, set_head, length, error, is_string, set_tail,
    apply_in_underlying_javascript, is_boolean, for_each, equal, is_pair
} from 'sicp';

const exp_machine = make_machine(
    list("product", "counter", "n", "b"),
    list(
        list("*", (a, b) => a * b),
        list("-", (a, b) => a - b),
        list("=", (a, b) => a === b),
    ),
    list(
        assign("product", constant(1)),
        assign("counter", reg("n")),
        "test_zero",
            test(list(op("="), reg("counter"), constant(0))),
            branch(label("exp_done")),
            assign("product", list(op("*"), reg("b"), reg("product"))),
            assign("counter", list(op("-"), reg("counter"), constant(1))),
            go_to(label("test_zero")),
        "exp_done"
    )
);

set_register_contents(exp_machine, "b", 10);
set_register_contents(exp_machine, "n", 8);
start(exp_machine);
display(get_register_contents(exp_machine, "product"));

// updated lookup_register function
function make_new_machine() {
    const pc = make_register("pc");
    const flag = make_register("flag");
    const stack = make_stack();
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
        if (is_undefined(val)) {
            allocate_register(name);
            return lookup_register(name);
        }
        return head(tail(val));
    }
    function execute() {
        const insts = get_contents(pc);
        if (is_null(insts)) {
            return "done";
        } else {
            inst_execution_fun(head(insts))();
            return execute();
        }
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
               : error(message, "unknown request -- machine");
    }
    return dispatch;
}

function make_execution_function(inst, labels, machine, pc, flag, stack, ops) {
    const inst_type = type(inst);
    return inst_type === "assign"
           ? make_assign_ef(inst, machine, labels, ops, pc)
           : inst_type === "test"
           ? make_test_ef(inst, machine, labels, ops, flag, pc)
           : inst_type === "branch"
           ? make_branch_ef(inst, machine, labels, flag, pc)
           : inst_type === "go_to"
           ? make_go_to_ef(inst, machine, labels, pc)
           : inst_type === "save"
           ? make_save_ef(inst, machine, stack, pc)
           : inst_type === "restore"
           ? make_restore_ef(inst, machine, stack, pc)
           : inst_type === "perform"
           ? make_perform_ef(inst, machine, labels, ops, pc)
           : error(inst, "unknown instruction type -- assemble");
}

function extract_labels(controller, receive) {
    return is_null(controller)
           ? receive(null, null)
           : extract_labels(
                 tail(controller),
                 (insts, labels) => {
                   const next_element = head(controller);
                   return is_string(next_element)
                          ? receive(insts,
                                    pair(make_label_entry(next_element,
                                                          insts),
                                         labels))
                          : receive(pair(make_inst(next_element),
                                         insts),
                                    labels);
                 });
}

function assemble(controller, machine) {
    return extract_labels(controller,
                          (insts, labels) => {
                              update_insts(insts, labels, machine);
                              return insts;
                          });
}

function make_machine(register_names, ops, controller) {
    const machine = make_new_machine();
    for_each(register_name =>
               machine("allocate_register")(register_name),
             register_names);
    machine("install_operations")(ops);
    machine("install_instruction_sequence")
           (assemble(controller, machine));
    return machine;
}

function make_register(name) {
    let contents = "*unassigned*";
    function dispatch(message) {
        return message === "get"
               ? contents
               : message === "set"
               ? value => { contents = value; }
               : error(message, "unknown request -- make_register");
    }
    return dispatch;
}

function update_insts(insts, labels, machine) {
    const pc = get_register(machine, "pc");
    const flag = get_register(machine, "flag");
    const stack = machine("stack");
    const ops = machine("operations");
    return for_each(inst => set_inst_execution_fun(
                                inst,
                                make_execution_function(
                                    inst_controller_instruction(inst),
                                    labels, machine, pc,
                                    flag, stack, ops)),
                    insts);
}

function make_assign_ef(inst, machine, labels, operations, pc) {
    const target = get_register(machine, assign_reg_name(inst));
    const value_exp = assign_value_exp(inst);
    const value_fun =
        is_operation_exp(value_exp)
        ? make_operation_exp_ef(value_exp, machine, labels, operations)
        : make_primitive_exp_ef(value_exp, machine, labels);
    return () => {
               set_contents(target, value_fun());
               advance_pc(pc);
           };
}

function make_branch_ef(inst, machine, labels, flag, pc) {
    const dest = branch_dest(inst);
    if (is_label_exp(dest)) {
        const insts = lookup_label(labels, label_exp_label(dest));
        return () => {
                   if (get_contents(flag)) {
                       set_contents(pc, insts);
                   } else {
                       advance_pc(pc);
                   }
               };
    } else {
        error(inst, "bad branch instruction -- assemble");
    }
}

function make_test_ef(inst, machine, labels, operations, flag, pc) {
    const condition = test_condition(inst);
    if (is_operation_exp(condition)) {
        const condition_fun = make_operation_exp_ef(
                                  condition, machine,
                                  labels, operations);
        return () => {
                   set_contents(flag, condition_fun());
                   advance_pc(pc);
               };
    } else {
        error(inst, "bad test instruction -- assemble");
    }
}

function make_go_to_ef(inst, machine, labels, pc) {
    const dest = go_to_dest(inst);
    if (is_label_exp(dest)) {
        const insts = lookup_label(labels, label_exp_label(dest));
        return () => set_contents(pc, insts);
    } else if (is_register_exp(dest)) {
        const reg = get_register(machine, register_exp_reg(dest));
        return () => set_contents(pc, get_contents(reg));
    } else {
        error(inst, "bad go_to instruction -- assemble");
    }
}

function make_save_ef(inst, machine, stack, pc) {
    const reg = get_register(machine, stack_inst_reg_name(inst));
    return () => {
       push(stack, get_contents(reg));
       advance_pc(pc);
   };
}

function make_perform_ef(inst, machine, labels, operations, pc) {
    const action = perform_action(inst);
    if (is_operation_exp(action)) {
        const action_fun = make_operation_exp_ef(action, machine,
                                                 labels, operations);
        return () => {
                   action_fun();
                   advance_pc(pc);
               };
    } else {
        error(inst, "bad perform instruction -- assemble");
    }
}

function make_restore_ef(inst, machine, stack, pc) {
    const reg = get_register(machine, stack_inst_reg_name(inst));
    return () => {
       set_contents(reg, pop(stack));
       advance_pc(pc);
   };
}

function make_primitive_exp_ef(exp, machine, labels) {
    if (is_constant_exp(exp)) {
        const c = constant_exp_value(exp);
        return () => c;
    } else if (is_label_exp(exp)) {
        const insts = lookup_label(labels, label_exp_label(exp));
        return () => insts;
    } else if (is_register_exp(exp)) {
        const r = get_register(machine, register_exp_reg(exp));
        return () => get_contents(r);
    } else {
        error(exp, "unknown expression type -- assemble");
    }
}

function lookup_prim(symbol, operations) {
    const val = assoc(symbol, operations);
    return is_undefined(val)
           ? error(symbol, "unknown operation -- assemble")
           : head(tail(val));
}

function op(name) { return list("op", name); }

function is_operation_exp(exp) {
    return is_pair(exp) && is_tagged_list(head(exp), "op");
}

function operation_exp_op(op_exp) { return head(tail(head(op_exp))); }

function operation_exp_operands(op_exp) { return tail(op_exp); }

function make_operation_exp_ef(exp, machine, labels, operations) {
    const op = lookup_prim(operation_exp_op(exp), operations);
    const afuns = map(e => make_primitive_exp_ef(e, machine, labels),
                      operation_exp_operands(exp));
    return () => apply_in_underlying_javascript(
                     op, map(f => f(), afuns));
}

function reg(name) { return list("reg", name); }

function is_register_exp(exp) { return is_tagged_list(exp, "reg"); }

function register_exp_reg(exp) { return head(tail(exp)); }

function constant(value) { return list("constant", value); }

function is_tagged_list(component, the_tag) {
    return is_pair(component) && head(component) === the_tag;
}

function is_constant_exp(exp) {
    return is_tagged_list(exp, "constant");
}

function constant_exp_value(exp) { return head(tail(exp)); }

function label(name) { return list("label", name); }

function is_label_exp(exp) { return is_tagged_list(exp, "label"); }

function label_exp_label(exp) { return head(tail(exp)); }

function branch(label) { return list("branch", label); }

function branch_dest(branch_instruction) {
    return head(tail(branch_instruction));
}

function perform(action) { return list("perform", action); }

function perform_action(perform_instruction) {
    return head(tail(perform_instruction));
}

function go_to(label) { return list("go_to", label); }

function go_to_dest(go_to_instruction) {
    return head(tail(go_to_instruction));
}

function save(reg) { return list("save", reg); }

function restore(reg) { return list("restore", reg); }

function stack_inst_reg_name(stack_instruction) {
    return head(tail(stack_instruction));
}

function test(condition) { return list("test", condition); }

function test_condition(test_instruction) {
    return head(tail(test_instruction));
}

function advance_pc(pc) {
    set_contents(pc, tail(get_contents(pc)));
}

function assign(register_name, source) {
    return list("assign", register_name, source);
}

function assign_reg_name(assign_instruction) {
    return head(tail(assign_instruction));
}

function assign_value_exp(assign_instruction) {
    return head(tail(tail(assign_instruction)));
}

function make_inst(inst_controller_instruction) {
    return pair(inst_controller_instruction, null);
}

function inst_controller_instruction(inst) {
    return head(inst);
}

function inst_execution_fun(inst) {
    return tail(inst);
}

function lookup_label(labels, label_name) {
    const val = assoc(label_name, labels);
    return is_undefined(val)
           ? error(label_name, "undefined label -- assemble")
           : tail(val);
}

function make_label_entry(label_name, insts) {
    return pair(label_name, insts);
}

function set_inst_execution_fun(inst, fun) {
    set_tail(inst, fun);
}

function get_contents(register) {
    return register("get");
}

function set_contents(register, value) {
    return register("set")(value);
}

function start(machine) {
    return machine("start");
}

function get_register(machine, reg_name) {
    return machine("get_register")(reg_name);
}

function get_register_contents(machine, register_name) {
    return get_contents(get_register(machine, register_name));
}

function set_register_contents(machine, register_name, value) {
    set_contents(get_register(machine, register_name), value);
    return "done";
}

function type(instruction) { return head(instruction); }

function make_stack() {
    let stack = null;
    function push(x) {
        stack = pair(x, stack);
        return "done";
    }
    function pop() {
        if (is_null(stack)) {
            error("empty stack -- pop");
        } else {
            const top = head(stack);
            stack = tail(stack);
            return top;
        }
    }
    function initialize() {
        stack = null;
        return "done";
    }
    function dispatch(message) {
        return message === "push"
               ? push
               : message === "pop"
               ? pop()
               : message === "initialize"
               ? initialize()
               : error(message, "unknown request -- stack");
    }
    return dispatch;
}

function pop(stack) {
    return stack("pop");
}

function push(stack, value) {
    return stack("push")(value);
}

function lookup(key, table) {
    const record = assoc(key, tail(table));
    return is_undefined(record)
           ? undefined
           : tail(record);
}

function assoc(key, records) {
    return is_null(records)
           ? undefined
           : equal(key, head(head(records)))
           ? head(records)
           : assoc(key, tail(records));
}
