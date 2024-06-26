package main

import (
	"fmt"
	"strings"
)

type Register struct {
	name     string
	contents *Value
}

func (r *Register) String() string {
	return fmt.Sprintf("%s: %s", r.name, r.contents)
}

// the machine stack
var stack *Stack

// machine registers
var exp *Register = &Register{name: "exp"}
var env *Register = &Register{name: "env"}
var unev *Register = &Register{name: "unev"}
var argl *Register = &Register{name: "argl"}
var proc *Register = &Register{name: "proc"}
var cont *Register = &Register{name: "cont"}
var val *Register = &Register{name: "val"}

// initial environment
var the_empty_environment *Value = nullValue

// some primitives
var primitive_procedures *Value = list(
	list(make_name("+"), make_prim(plus)),
	list(make_name("-"), make_prim(minus)),
	list(make_name("*"), make_prim(mul)),
	list(make_name("="), make_prim(eq)),
	list(make_name("eq?"), make_prim(eq)),
	list(make_name(">"), make_prim(gt)),
	list(make_name("<"), make_prim(lt)),
	list(make_name("or"), make_prim(or)),
	list(make_name("and"), make_prim(and)),
	list(make_name("display"), make_prim(display)),
	list(make_name("newline"), make_prim(newline)),
	list(make_name("list"), make_prim(_list)),
	list(make_name("car"), make_prim(car)),
	list(make_name("cdr"), make_prim(cdr)),
	list(make_name("cddr"), make_prim(cddr)),
	list(make_name("cadr"), make_prim(cadr)),
	list(make_name("cons"), make_prim(_cons)),
	list(make_name("caddr"), make_prim(caddr)),
	list(make_name("cadddr"), make_prim(cadddr)),
	list(make_name("null?"), make_prim(is_null)),
	list(make_name("pair?"), make_prim(is_pair)),
	list(make_name("display"), make_prim(display)),
	list(make_name("not"), make_prim(not)),
	list(make_name("append"), make_prim(_append)),
	list(make_name("set-car!"), make_prim(set_car)),
	list(make_name("set-cdr!"), make_prim(set_cdr)),
	list(make_name("error"), make_prim(_error)),
)

// initial setup of the environment
func get_global_environment() *Value {
	initial_env := extend_environment(
		primitive_procedure_names(),
		primitive_procedure_objs(),
		the_empty_environment)
	tname := &Value{
		kind: Name,
		val:  "true",
	}
	fname := &Value{
		kind: Name,
		val:  "false",
	}

	define_variable(tname, make_true(), initial_env)
	define_variable(fname, make_false(), initial_env)

	return initial_env
}

func primitive_procedure_names() *Value {
	return _map(car, primitive_procedures)
}

func primitive_procedure_objs() *Value {
	f := func(proc *Value) *Value {
		n := &Value{
			kind: Name,
			val:  "primitive",
		}
		return list(n, cadr(proc))
	}
	return _map(f, primitive_procedures)
}

// representing procedures
func make_procedure(parameters *Value, body *Value, env *Value) *Value {
	proc_name := &Value{
		kind: Name,
		val:  "procedure",
	}
	return list(proc_name, parameters, body, env)
}

func procedure_parameters(p *Value) *Value {
	return cadr(p)
}

func procedure_body(p *Value) *Value {
	return caddr(p)
}

func procedure_environment(p *Value) *Value {
	return cadddr(p)
}

func is_primitive_procedure(proc *Value) *Value {
	if is_tagged_list(proc, "primitive") {
		return make_true()
	}
	return make_false()
}

func is_compound_procedure(proc *Value) *Value {
	if is_tagged_list(proc, "procedure") {
		return make_true()
	}
	return make_false()
}

func primitive_implementation(proc *Value) *Value {
	return cadr(proc)
}

func apply_primitive_procedure(proc *Value, args *Value) *Value {
	p := primitive_implementation(proc)
	if p.kind != Function {
		panic(fmt.Sprintf("not a function %s", p))
	}

	fun, ok := p.val.(func(args *Value) *Value)
	if !ok {
		panic(fmt.Sprintf("incorrect primitive function signature %s", fun))
	}

	return fun(args)
}

// compiled procedures
func make_compiled_procedure(entry *Value, env *Value) *Value {
	proc_name := &Value{
		kind: Name,
		val:  "compiled_procedure",
	}
	return list(proc_name, entry, env)
}

func is_compiled_procedure(proc *Value) *Value {
	if is_tagged_list(proc, "compiled_procedure") {
		return make_true()
	}
	return make_false()
}

func compiled_procedure_entry(proc *Value) *Value {
	return cadr(proc)
}

func compiled_procedure_env(proc *Value) *Value {
	return caddr(proc)
}

// environments
func enclosing_environment(env *Value) *Value {
	return cdr(env)
}

func first_frame(env *Value) *Value {
	return car(env)
}

func make_frame(variables *Value, values *Value) *Value {
	return cons(variables, values)
}

func frame_variables(frame *Value) *Value {
	return car(frame)
}

func frame_values(frame *Value) *Value {
	return cdr(frame)
}

func add_binding_to_frame(variable *Value, val *Value, frame *Value) {
	setCar(frame, cons(variable, car(frame)))
	setCdr(frame, cons(val, cdr(frame)))
}

func extend_environment(vars *Value, vals *Value, base_env *Value) *Value {
	varsLen := listLen(vars)
	valsLen := listLen(vals)

	if varsLen == valsLen {
		return cons(make_frame(vars, vals), base_env)
	}

	if varsLen < valsLen {
		panic(fmt.Sprintf("Too many arguments supplied %s %s", vars, vals))
	} else {
		panic(fmt.Sprintf("Too few arguments supplied %s %s", vars, vals))
	}
}

// variable operations
func lookup_variable_value(variable *Value, env *Value) *Value {
	var envLoop func(env *Value) *Value
	envLoop = func(env *Value) *Value {
		var scan func(vars *Value, vals *Value) *Value
		scan = func(vars *Value, vals *Value) *Value {
			if isNull(vars) {
				return envLoop(enclosing_environment(env))
			} else if isEqual(variable, car(vars)) {
				return car(vals)
			} else {
				return scan(cdr(vars), cdr(vals))
			}
		}
		if isEqual(env, the_empty_environment) {
			panic(fmt.Sprintf("Unbound variable %s", variable))
		} else {
			frame := first_frame(env)
			return scan(frame_variables(frame), frame_values(frame))
		}
	}
	return envLoop(env)
}

func set_variable_value(variable *Value, val *Value, env *Value) {
	var envLoop func(env *Value) *Value
	envLoop = func(env *Value) *Value {
		var scan func(vars *Value, vals *Value) *Value
		scan = func(vars *Value, vals *Value) *Value {
			if isNull(vars) {
				return envLoop(enclosing_environment(env))
			} else if isEqual(variable, car(vars)) {
				setCar(vals, variable)
				return nullValue
			} else {
				return scan(cdr(vars), cdr(vals))
			}
		}
		if isEqual(env, the_empty_environment) {
			panic(fmt.Sprintf("Unbound variable -- SET! %s", variable))
		} else {
			frame := first_frame(env)
			return scan(frame_variables(frame), frame_values(frame))
		}
	}
	envLoop(env)
}

func define_variable(variable *Value, val *Value, env *Value) {
	var scan func(vars *Value, vals *Value) *Value
	frame := first_frame(env)
	scan = func(vars *Value, vals *Value) *Value {
		if isNull(vars) {
			add_binding_to_frame(variable, val, frame)
			return nullValue
		} else if isEqual(variable, car(vars)) {
			setCar(vals, variable)
			return nullValue
		} else {
			return scan(cdr(vars), cdr(vals))
		}
	}
	scan(frame_variables(frame), frame_values(frame))
}

func empty_arglist() *Value {
	return nullValue
}

func adjoin_arg(arg *Value, arglist *Value) *Value {
	return listAppend(arglist, list(arg))
}

func user_print(val *Value) {
	res := is_compound_procedure(val)
	if res.val.(bool) == true {
		n := constant("compound_procedure")
		l := list(n, procedure_parameters(val), procedure_body(val), constant("<procedure_env>"))
		display(l)
	} else {
		display(val)
	}
}

func assign(register *Register, value *Value) {
	register.contents = value
}

func save(register Register) {
	stack.push(register)
}

func restore(register *Register) {
	*register = stack.pop().(Register)
}

func initialize_stack() {
	stack = newStack()
}

func reg(r *Register) *Value {
	return r.contents
}

func test(v *Value) bool {
	val, ok := v.val.(bool)
	if !ok {
		panic("not a boolean")
	}

	return val
}

func constant(c string) *Value {
	if c == "()" {
		return nullValue
	}
	if strings.Contains(c, "(") {
		elems := strings.ReplaceAll(c, "(", "")
		elems = strings.ReplaceAll(elems, ")", "")
		items := strings.Split(elems, " ")
		l := list()
		for _, item := range items {
			itemName := &Value{
				kind: Name,
				val:  item,
			}
			l = listAppend(l, list(itemName))
		}
		return l
	}
	return &Value{
		kind: Name,
		val:  c,
	}
}

func label(fun func()) *Value {
	return &Value{
		kind: Function,
		val:  fun,
	}
}

func go_to(fun *Value) {
	f, ok := fun.val.(func())
	if !ok {
		panic(fmt.Sprintf("not a valid function %s", fun))
	}
	f()
}
