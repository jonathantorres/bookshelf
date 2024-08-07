import {
    display, display_list, pair, head, tail, is_null, error, list, append,
    stringify, accumulate, is_pair, list_ref, set_head, length, parse, map,
    apply_in_underlying_javascript, is_boolean, reverse, set_tail, math_PI
} from 'sicp';

const primitive_functions = list(list("head", head),
                                 list("tail", tail),
                                 list("pair", pair),
                                 list("list", list),
                                 list("display", display),
                                 list("is_null", is_null),
                                 list("+", (x, y) => x + y),
                                 list("-", (x, y) => x - y),
                                 list("*", (x, y) => x * y),
                                 list("<=", (x, y) => x <= y));

const primitive_constants = list(list("undefined", undefined),
                                 list("math_PI", math_PI));

const primitive_function_symbols = map(f => head(f), primitive_functions);
const primitive_function_objects = map(f => list("primitive", head(tail(f))), primitive_functions);
const primitive_constant_symbols = map(c => head(c), primitive_constants);
const primitive_constant_values = map(c => head(tail(c)), primitive_constants);
const the_empty_environment = null;
const the_global_environment = setup_environment();

const prog = `
{
    function cube(x) {
        return x*x*x;
    }
    let x = 500;
    display(cube(x));
}
`;

ambeval(parse(prog), the_global_environment,
    // ambeval success
    (val, next_alternative) => {
        display(to_string(val));
        return;
    },
    // ambeval failure
    () => {
        display("no more values");
        return;
    }
);

function ambeval(component, env, succeed, fail) {
    return analyze(component)(env, succeed, fail);
}

function analyze(component) {
    return is_literal(component)
           ? analyze_literal(component)
           : is_name(component)
           ? analyze_name(component)
           : is_amb(component)
           ? analyze_amb(component)
           : is_application(component)
           ? analyze_application(component)
           : is_operator_combination(component)
           ? analyze(operator_combination_to_application(component))
           : is_conditional(component)
           ? analyze_conditional(component)
           : is_lambda_expression(component)
           ? analyze_lambda_expression(component)
           : is_sequence(component)
           ? analyze_sequence(sequence_statements(component))
           : is_block(component)
           ? analyze_block(component)
           : is_return_statement(component)
           ? analyze_return_statement(component)
           : is_function_declaration(component)
           ? analyze(function_decl_to_constant_decl(component))
           : is_declaration(component)
           ? analyze_declaration(component)
           : is_assignment(component)
           ? analyze_assignment(component)
           : error(component, "unknown syntax -- analyze");
}

function is_amb(component) {
    return is_tagged_list(component, "application") &&
           is_name(function_expression(component)) &&
           symbol_of_name(function_expression(component)) === "amb";
}

function analyze_amb(component) {
    const cfuns = map(analyze, amb_choices(component));
    return (env, succeed, fail) => {
           function try_next(choices) {
               return is_null(choices)
                      ? fail()
                      : head(choices)(env,
                                      succeed,
                                      () =>
                                        try_next(tail(choices)));
           }
           return try_next(cfuns);
       };
}

function analyze_assignment(component) {
    const symbol = assignment_symbol(component);
    const vfun = analyze(assignment_value_expression(component));
    return (env, succeed, fail) =>
         vfun(env,
              (val, fail2) => {
                  const old_value = lookup_symbol_value(symbol, env);
                  assign_symbol_value(symbol, val, env);
                  return succeed(val, () => {
                     assign_symbol_value(symbol, old_value, env);
                     return fail2();
                 });
              },
              fail);
}

function amb_choices(component) {
    return arg_expressions(component);
}

function to_string(object) {
    return is_compound_function(object)
           ? "<compound-function>"
           : is_primitive_function(object)
           ? "<primitive-function>"
           : is_pair(object)
           ? "[" + to_string(head(object)) + ", "
                 + to_string(tail(object)) + "]"
           : stringify(object);
}

function setup_environment() {
    return extend_environment(append(primitive_function_symbols,
                                     primitive_constant_symbols),
                              append(primitive_function_objects,
                                     primitive_constant_values),
                              the_empty_environment);
}

function scan_out_declarations(component) {
    return is_sequence(component)
           ? accumulate(append,
                        null,
                        map(scan_out_declarations,
                            sequence_statements(component)))
           : is_declaration(component)
           ? list(declaration_symbol(component))
           : null;
}

function list_of_unassigned(symbols) {
    return map(symbol => "*unassigned*", symbols);
}

function analyze_literal(component) {
    return (env, succeed, fail) =>
             succeed(literal_value(component), fail);
}

function analyze_name(component) {
    return (env, succeed, fail) =>
             succeed(lookup_symbol_value(symbol_of_name(component),
                                         env),
                     fail);
}

function analyze_lambda_expression(component) {
    const params = lambda_parameter_symbols(component);
    const bfun = analyze(lambda_body(component));
    return (env, succeed, fail) =>
             succeed(make_function(params, bfun, env),
                     fail);
}

function analyze_conditional(component) {
    const pfun = analyze(conditional_predicate(component));
    const cfun = analyze(conditional_consequent(component));
    const afun = analyze(conditional_alternative(component));
    return (env, succeed, fail) =>
             pfun(env,
                  // success continuation for evaluating the predicate
                  // to obtain pred_value
                  (pred_value, fail2) =>
                    is_truthy(pred_value)
                    ? cfun(env, succeed, fail2)
                    : afun(env, succeed, fail2),
                  // failure continuation for evaluating the predicate
                  fail);
}

function analyze_sequence(stmts) {
    function sequentially(a, b) {
        return (env, succeed, fail) =>
                 a(env,
                   // success continuation for calling a
                   (a_value, fail2) =>
                     is_return_value(a_value)
                     ? succeed(a_value, fail2)
                     : b(env, succeed, fail2),
                   // failure continuation for calling a
                   fail);
    }
    function loop(first_fun, rest_funs) {
        return is_null(rest_funs)
               ? first_fun
               : loop(sequentially(first_fun, head(rest_funs)), tail(rest_funs));
    }
    const funs = map(analyze, stmts);
    return is_null(funs)
           ? env => undefined
           : loop(head(funs), tail(funs));
}

function analyze_declaration(component) {
    const symbol = declaration_symbol(component);
    const vfun = analyze(declaration_value_expression(component));
    return (env, succeed, fail) =>
             vfun(env,
                  (val, fail2) => {
                      assign_symbol_value(symbol, val, env);
                      return succeed(undefined, fail2);
                  },
                  fail);
}

function analyze_return_statement(component) {
    const rfun = analyze(return_expression(component));
    return (env, succeed, fail) =>
             rfun(env,
                  (val, fail2) =>
                    succeed(make_return_value(val), fail2),
                  fail);
}

function analyze_block(component) {
    const body = block_body(component);
    const locals = scan_out_declarations(body);
    const unassigneds = list_of_unassigned(locals);
    const bfun = analyze(body);
    return (env, succeed, fail) =>
             bfun(extend_environment(locals, unassigneds, env),
                  succeed,
                  fail);
}

function analyze_application(component) {
    const ffun = analyze(function_expression(component));
    const afuns = map(analyze, arg_expressions(component));
    return (env, succeed, fail) =>
         ffun(env,
              (fun, fail2) =>
                get_args(afuns,
                         env,
                         (args, fail3) =>
                           execute_application(fun,
                                               args,
                                               succeed,
                                               fail3),
                         fail2),
              fail);
}

function get_args(afuns, env, succeed, fail) {
    return is_null(afuns)
           ? succeed(null, fail)
           : head(afuns)(env,
             // success continuation for this afun
             (arg, fail2) =>
               get_args(tail(afuns),
                        env,
                        // success continuation for
                        // recursive call to get_args
                        (args, fail3) =>
                          succeed(pair(arg, args),
                                  fail3),
                        fail2),
             fail);
}

function execute_application(fun, args, succeed, fail) {
    return is_primitive_function(fun)
           ? succeed(apply_primitive_function(fun, args),
                     fail)
           : is_compound_function(fun)
           ? function_body(fun)(
                 extend_environment(function_parameters(fun),
                                    args,
                                    function_environment(fun)),
                 (body_result, fail2) =>
                   succeed(is_return_value(body_result)
                           ? return_value_content(body_result)
                           : undefined,
                           fail2),
                 fail)
           : error(fun, "unknown function type - execute_application");
}

function is_literal(component) {
    return is_tagged_list(component, "literal");
}

function is_tagged_list(component, the_tag) {
    return is_pair(component) && head(component) === the_tag;
}

function literal_value(component) {
    return head(tail(component));
}

function make_literal(value) {
    return list("literal", value);
}

function make_name(symbol) {
    return list("name", symbol);
}

function is_name(component) {
    return is_tagged_list(component, "name");
}

function symbol_of_name(component) {
    return head(tail(component));
}

function make_application(function_expression, argument_expressions) {
    return list("application", function_expression, argument_expressions);
}

function is_application(component) {
   return is_tagged_list(component, "application");
}

function function_expression(component) {
   return head(tail(component));
}

function arg_expressions(component) {
   return head(tail(tail(component)));
}

function lambda_parameter_symbols(component) {
    return map(symbol_of_name, head(tail(component)));
}

function is_lambda_expression(component) {
    return is_tagged_list(component, "lambda_expression");
}

function lambda_body(component) {
    return head(tail(tail(component)));
}

function make_lambda_expression(parameters, body) {
    return list("lambda_expression", parameters, body);
}

function is_sequence(stmt) {
   return is_tagged_list(stmt, "sequence");
}

function sequence_statements(stmt) {
   return head(tail(stmt));
}

function first_statement(stmts) {
    return head(stmts);
}

function rest_statements(stmts) {
    return tail(stmts);
}

function is_empty_sequence(stmts) {
    return is_null(stmts);
}

function is_last_statement(stmts) {
    return is_null(tail(stmts));
}

function is_block(component) {
    return is_tagged_list(component, "block");
}

function block_body(component) {
    return head(tail(component));
}

function make_block(statement) {
    return list("block", statement);
}

function is_operator_combination(component) {
    return is_unary_operator_combination(component) ||
           is_binary_operator_combination(component);
}

function is_unary_operator_combination(component) {
    return is_tagged_list(component, "unary_operator_combination");
}

function is_binary_operator_combination(component) {
    return is_tagged_list(component, "binary_operator_combination");
}

function operator_symbol(component) {
    return list_ref(component, 1);
}

function first_operand(component) {
    return list_ref(component, 2);
}

function second_operand(component) {
    return list_ref(component, 3);
}

function declaration_symbol(component) {
    return symbol_of_name(head(tail(component)));
}

function declaration_value_expression(component) {
    return head(tail(tail(component)));
}

function make_constant_declaration(name, value_expression) {
    return list("constant_declaration", name, value_expression);
}

function is_assignment(component) {
    return is_tagged_list(component, "assignment");
}

function assignment_symbol(component) {
    return head(tail(head(tail(component))));
}

function assignment_value_expression(component) {
    return head(tail(tail(component)));
}

function is_declaration(component) {
    return is_tagged_list(component, "constant_declaration") ||
           is_tagged_list(component, "variable_declaration") ||
           is_tagged_list(component, "function_declaration");
}

function is_function_declaration(component) {
    return is_tagged_list(component, "function_declaration");
}

function function_declaration_name(component) {
    return list_ref(component, 1);
}

function function_declaration_parameters(component) {
    return list_ref(component, 2);
}

function function_declaration_body(component) {
    return list_ref(component, 3);
}

function function_decl_to_constant_decl(component) {
    return make_constant_declaration(
               function_declaration_name(component),
               make_lambda_expression(
                   function_declaration_parameters(component),
                   function_declaration_body(component)));
}

function is_return_statement(component) {
   return is_tagged_list(component, "return_statement");
}

function return_expression(component) {
   return head(tail(component));
}

function is_conditional(component) {
    return is_tagged_list(component, "conditional_expression") ||
           is_tagged_list(component, "conditional_statement");
}

function conditional_predicate(component) {
   return list_ref(component, 1);
}

function conditional_consequent(component) {
   return list_ref(component, 2);
}

function conditional_alternative(component) {
   return list_ref(component, 3);
}

function operator_combination_to_application(component) {
    const operator = operator_symbol(component);
    return is_unary_operator_combination(component)
           ? make_application(make_name(operator),
                              list(first_operand(component)))
           : make_application(make_name(operator),
                              list(first_operand(component),
                                   second_operand(component)));
}

function is_truthy(x) {
    return is_boolean(x)
           ? x
           : error(x, "boolean expected, received");
}

function is_falsy(x) { return ! is_truthy(x); }

function make_function(parameters, body, env) {
    return list("compound_function", parameters, body, env);
}

function is_compound_function(f) {
    return is_tagged_list(f, "compound_function");
}

function function_parameters(f) { return list_ref(f, 1); }

function function_body(f) { return list_ref(f, 2); }

function function_environment(f) { return list_ref(f, 3); }

function make_return_value(content) {
    return list("return_value", content);
}

function is_return_value(value) {
    return is_tagged_list(value, "return_value");
}

function return_value_content(value) {
    return head(tail(value));
}

function enclosing_environment(env) { return tail(env); }

function first_frame(env) { return head(env); }

function make_frame(symbols, values) { return pair(symbols, values); }

function frame_symbols(frame) { return head(frame); }

function frame_values(frame) { return tail(frame); }

function extend_environment(symbols, vals, base_env) {
    return length(symbols) === length(vals)
           ? pair(make_frame(symbols, vals), base_env)
           : error(pair(symbols, vals),
                   length(symbols) < length(vals)
                   ? "too many arguments supplied"
                   : "too few arguments supplied");
}

function lookup_symbol_value(symbol, env) {
    function env_loop(env) {
        function scan(symbols, vals) {
            return is_null(symbols)
                   ? env_loop(enclosing_environment(env))
                   : symbol === head(symbols)
                   ? head(vals)
                   : scan(tail(symbols), tail(vals));
        }
        if (env === the_empty_environment) {
            error(symbol, "unbound name");
        } else {
            const frame = first_frame(env);
            return scan(frame_symbols(frame), frame_values(frame));
        }
    }
    return env_loop(env);
}

function assign_symbol_value(symbol, val, env) {
    function env_loop(env) {
        function scan(symbols, vals) {
            return is_null(symbols)
                   ? env_loop(enclosing_environment(env))
                   : symbol === head(symbols)
                   ? set_head(vals, val)
                   : scan(tail(symbols), tail(vals));
        }
        if (env === the_empty_environment) {
            error(symbol, "unbound name -- assignment");
        } else {
            const frame = first_frame(env);
            return scan(frame_symbols(frame), frame_values(frame));
        }
    }
    return env_loop(env);
}

function is_primitive_function(fun) {
    return is_tagged_list(fun, "primitive");
}

function primitive_implementation(fun) { return head(tail(fun)); }

function apply_primitive_function(fun, arglist) {
    return apply_in_underlying_javascript(
               primitive_implementation(fun), arglist);
}
