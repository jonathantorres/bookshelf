import {
    display, display_list, pair, head, tail, is_null, error, list, append, parse, map,
    math_PI, stringify, accumulate, is_pair, list_ref, set_head, length,
    apply_in_underlying_javascript, is_boolean, reverse
} from 'sicp';

const prog = "{ function s(a,b) { return a-b; } const i = 5; const v = s(i, 3); v; s(0,0); if (false) { v; } else { v; }}";
const tree = parse(prog);

console.log(unparse(tree));

function unparse(component) {
    return unp(component, 0);
}

function unp(component, depth) {
    return is_literal(component)
           ? literal_value(component)
           : is_name(component)
           ? symbol_of_name(component)
           : is_application(component)
           ? unparse_application(
               unp(function_expression(component), depth),
               list_of_values(arg_expressions(component), depth),
               depth
           )
           : is_operator_combination(component)
           ? unparse_combination(component, depth)
           : is_conditional(component)
           ? unparse_conditional(component, depth)
           : is_lambda_expression(component)
           ? unparse_lambda(lambda_parameter_symbols(component), lambda_body(component), depth)
           : is_sequence(component)
           ? unparse_sequence(sequence_statements(component), depth)
           : is_block(component)
           ? unparse_block(component, depth)
           : is_return_statement(component)
           ? unparse_return_statement(component, depth)
           : is_function_declaration(component)
           ? unparse_function_declaration(component, depth)
           : is_declaration(component)
           ? unparse_declaration(component, depth)
           : is_assignment(component)
           ? unparse_assignment(component, depth)
           : error(component, "unknown syntax -- unparse");
}

function indent(depth) {
    let tab = "    ";
    let ind = "";

    while (depth > 0) {
        ind += tab;
        depth--;
    }

    return ind;
}

function unparse_assignment(component, depth) {
    return assignment_symbol(component) + " = " + assignment_value_expression(component);
}

function unparse_declaration(component, depth) {
    let decl = indent(depth);

    if (is_constant_declaration(component)) {
        decl = "const ";
    }

    if (is_variable_declaration(component)) {
        decl = "let ";
    }

    return decl + declaration_symbol(component) + " = "
        + unp(declaration_value_expression(component), depth);
}

function unparse_function_declaration(component, depth) {
    let i = 0;
    let func = "function ";
    let args = function_declaration_parameters(component);
    func += unp(function_declaration_name(component), depth);
    func += "(";

    map(arg => {
        func += unp(arg, depth);

        if (i < length(args)-1) {
            func += ", ";
        }

        i++;
    }, args);

    func += ") {\n";
    func += indent(depth);
    depth++;
    func += unp(function_declaration_body(component), depth);
    func += "\n" + indent(depth-1) + "}\n";

    return func;
}

function unparse_return_statement(component, depth) {
    return indent(depth-1) + "return " + unp(return_expression(component), 0) + ";";
}

function unparse_block(component, depth) {
    let block = indent(depth) + "{\n";

    depth++;
    block += unp(block_body(component), depth);
    depth--;
    block += indent(depth);
    block += "}\n";

    return block;
}

function unparse_sequence(statements, depth) {
    let seq = "";

    map(s => {
        seq += indent(depth) + unp(s, depth);

        if (!is_function_declaration(s) && !is_conditional_statement(s)) {
            seq += ";";
        }
        seq += "\n";
    }, statements);

    return seq;
}

function unparse_lambda(args, body, depth) {
    let lambda = "(";
    let i = 0;

    map(arg => {
        lambda += unp(arg, depth);

        if (i < length(args)-1) {
            lambda += ", ";
        }

        i++;
    }, args);

    lambda += ") => ";
    lambda += unp(body, depth);

    return lambda;
}

function unparse_application(fun, args, depth) {
    let app = fun + "(";
    let i = 0;

    map(arg => {
        app += arg;

        if (i < length(args)-1) {
            app += ", ";
        }

        i++;
    }, args);

    app += ")";

    return app;
}

function unparse_conditional(component, depth) {
    if (is_conditional_expression(component)) {
        return indent(depth) + unp(conditional_predicate(component), depth) + "? "
            + unp(conditional_consequent(component), depth) + ": "
            + unp(conditional_alternative(component), depth);
    }

    if (is_conditional_statement(component)) {
        let cond = indent(depth-1);
        cond += "if (" + unp(conditional_predicate(component), depth) + ") {\n";
        depth++;
        cond += indent(depth) + unp(conditional_consequent(component), depth) + "\n";
        cond += indent(depth-1) + "} else {\n";
        cond += indent(depth) + unp(conditional_alternative(component), depth) + "\n";
        cond += indent(depth-1) + "}\n";

        return cond;
    }
}

function unparse_combination(component, depth) {
    const operator = operator_symbol(component);
    return is_unary_operator_combination(component)
           ? indent(depth) + operator + unp(first_operand(component), depth)
           : indent(depth) + unp(first_operand(component), depth) + operator + unp(second_operand(component), depth);
}

function make_application(function_expression, argument_expressions) {
    return list("application", function_expression, argument_expressions);
}

function make_name(symbol) {
    return list("name", symbol);
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

function assignment_symbol(component) {
    return head(tail(head(tail(component))));
}

function assignment_value_expression(component) {
    return head(tail(tail(component)));
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

function list_of_values(exps, depth) {
    return map(arg => unp(arg, depth), exps);
}

function is_truthy(x) {
    return is_boolean(x)
           ? x
           : error(x, "boolean expected, received");
}

function is_falsy(x) { return ! is_truthy(x); }

function is_return_statement(component) {
   return is_tagged_list(component, "return_statement");
}

function return_expression(component) {
   return head(tail(component));
}

function is_conditional(component) {
    return is_conditional_expression(component) || is_conditional_statement(component);
}

function is_conditional_expression(component) {
    return is_tagged_list(component, "conditional_expression");
}

function is_conditional_statement(component) {
    return is_tagged_list(component, "conditional_statement");
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

function conditional_predicate(component) {
   return list_ref(component, 1);
}

function conditional_consequent(component) {
   return list_ref(component, 2);
}

function conditional_alternative(component) {
   return list_ref(component, 3);
}

function is_primitive_function(fun) {
    return is_tagged_list(fun, "primitive");
}

function is_constant_declaration(component) {
    return is_tagged_list(component, "constant_declaration");
}

function is_variable_declaration(component) {
    return is_tagged_list(component, "variable_declaration");
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

function is_literal(component) {
    return is_tagged_list(component, "literal");
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

function literal_value(component) {
    return stringify(head(tail(component)));
}

function is_name(component) {
    return is_tagged_list(component, "name");
}

function symbol_of_name(component) {
    return head(tail(component));
}

function is_application(component) {
   return is_tagged_list(component, "application");
}

function is_tagged_list(component, the_tag) {
    return is_pair(component) && head(component) === the_tag;
}
