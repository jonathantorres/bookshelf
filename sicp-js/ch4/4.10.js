import {
    display, display_list, pair, head, tail, is_null, error, list, append, parse, map,
    math_PI, stringify, accumulate, is_pair, list_ref, set_head, length,
    apply_in_underlying_javascript, is_boolean, reverse
} from 'sicp';

const primitive_functions = list(list("head", head),
                                 list("tail", tail),
                                 list("pair", pair),
                                 list("list", list),
                                 list("display", display),
                                 list("is_null", is_null),
                                 list("+", (x, y) => x + y),
                                 list("-", (x, y) => x - y),
                                 list("*", (x, y) => x * y));

const primitive_constants = list(list("undefined", undefined),
                                 list("math_PI", math_PI));

const primitive_function_symbols = map(f => head(f), primitive_functions);
const primitive_function_objects = map(f => list("primitive", head(tail(f))), primitive_functions);
const primitive_constant_symbols = map(c => head(c), primitive_constants);
const primitive_constant_values = map(c => head(tail(c)), primitive_constants);
const the_empty_environment = null;
const the_global_environment = setup_environment();

const prog = "{ let y = 100; y = y*100; display(y); }";
const tree = parse(prog);

display(evaluate(tree, the_global_environment));

function evaluate(component, env) {
    return is_literal(component)
           ? literal_value(component)
           : is_name(component)
           ? lookup_symbol_value(symbol_of_name(component), env)
           : is_application(component)
           ? apply(evaluate(function_expression(component), env),
                   list_of_values(arg_expressions(component), env))
           : is_operator_combination(component)
           ? evaluate(operator_combination_to_application(component), env)
           : is_conditional(component)
           ? eval_conditional(component, env)
           : is_lambda_expression(component)
           ? make_function(lambda_parameter_symbols(component),
                           lambda_body(component), env)
           : is_sequence(component)
           ? eval_sequence(sequence_statements(component), env)
           : is_block(component)
           ? eval_block(component, env)
           : is_return_statement(component)
           ? eval_return_statement(component, env)
           : is_function_declaration(component)
           ? evaluate(function_decl_to_constant_decl(component), env)
           : is_declaration(component)
           ? eval_declaration(component, env)
           : is_assignment(component)
           ? eval_assignment(component, env)
           : error(component, "unknown syntax -- evaluate");
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


function setup_environment() {
    return extend_environment(append(primitive_function_symbols,
                                     primitive_constant_symbols),
                              append(primitive_function_objects,
                                     primitive_constant_values),
                              the_empty_environment);
}

function apply(fun, args) {
    if (is_primitive_function(fun)) {
        return apply_primitive_function(fun, args);
    } else if (is_compound_function(fun)) {
        const result = evaluate(function_body(fun),
                                extend_environment(
                                    function_parameters(fun),
                                    args,
                                    function_environment(fun)));
        return is_return_value(result)
               ? return_value_content(result)
               : undefined;
    } else {
        error(fun, "unknown function type -- apply");
    }
}

function eval_conditional(component, env) {
    return is_truthy(evaluate(conditional_predicate(component), env))
           ? evaluate(conditional_consequent(component), env)
           : evaluate(conditional_alternative(component), env);
}

function eval_sequence(stmts, env) {
    if (is_empty_sequence(stmts)) {
        return undefined;
    } else if (is_last_statement(stmts)) {
        return evaluate(first_statement(stmts), env);
    } else {
        const first_stmt_value = evaluate(first_statement(stmts), env);
        if (is_return_value(first_stmt_value)) {
            return first_stmt_value;
        } else {
            return eval_sequence(rest_statements(stmts), env);
        }
    }
}

function eval_block(component, env) {
    const body = block_body(component);
    const locals = scan_out_declarations(body);
    const unassigneds = list_of_unassigned(locals);
    return evaluate(body, extend_environment(locals, unassigneds, env));
}

function list_of_unassigned(symbols) {
    return map(symbol => "*unassigned*", symbols);
}

function list_of_values(exps, env) {
    return map(arg => evaluate(arg, env), exps);
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

function eval_return_statement(component, env) {
    return make_return_value(evaluate(return_expression(component), env));
}

function eval_assignment(component, env) {
    const value = evaluate(assignment_value_expression(component), env);
    assign_symbol_value(assignment_symbol(component), value, env);
    return value;
}

function eval_declaration(component, env) {
    assign_symbol_value(
        declaration_symbol(component),
        evaluate(declaration_value_expression(component), env),
        env);
    return undefined;
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

function is_primitive_function(fun) {
    return is_tagged_list(fun, "primitive");
}

function primitive_implementation(fun) { return head(tail(fun)); }

function apply_primitive_function(fun, arglist) {
    return apply_in_underlying_javascript(
               primitive_implementation(fun), arglist);
}
