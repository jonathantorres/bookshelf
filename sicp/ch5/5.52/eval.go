package main

func startEval() {
	initialize_stack()
	assign(env, get_global_environment())
	assign(val, make_compiled_procedure(label(entry1), reg(env)))
	go_to(label(after_lambda2))
}

func entry1() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc l)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("l"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch6()
		return
	}
	go_to(label(compiled_branch7))
}

func compiled_branch7() {
	assign(cont, label(after_call8))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch6() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call8))
}

func after_call8() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch4()
		return
	}
	go_to(label(true_branch3))
}

func true_branch3() {
	assign(val, constant("()"))
	go_to(reg(cont))
}

func false_branch4() {
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("map"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("l"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch15()
		return
	}
	go_to(label(compiled_branch16))
}

func compiled_branch16() {
	assign(cont, label(after_call17))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch15() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call17))
}

func after_call17() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch18()
		return
	}
	go_to(label(compiled_branch19))
}

func compiled_branch19() {
	assign(cont, label(after_call20))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch18() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call20))
}

func after_call20() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("proc"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("l"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch9()
		return
	}
	go_to(label(compiled_branch10))
}

func compiled_branch10() {
	assign(cont, label(after_call11))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch9() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call11))
}

func after_call11() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch12()
		return
	}
	go_to(label(compiled_branch13))
}

func compiled_branch13() {
	assign(cont, label(after_call14))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch12() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call14))
}

func after_call14() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch21()
		return
	}
	go_to(label(compiled_branch22))
}

func compiled_branch22() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch21() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call23() {
	go_to(label(after_if5))
}

func after_if5() {
	go_to(label(after_lambda2))
}

func after_lambda2() {
	define_variable(constant("map"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry24), reg(env)))
	go_to(label(after_lambda25))
}

func entry24() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(l)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("l"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch29()
		return
	}
	go_to(label(compiled_branch30))
}

func compiled_branch30() {
	assign(cont, label(after_call31))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch29() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call31))
}

func after_call31() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch27()
		return
	}
	go_to(label(true_branch26))
}

func true_branch26() {
	assign(val, constant("0"))
	go_to(reg(cont))
}

func false_branch27() {
	assign(proc, lookup_variable_value(constant("+"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("length"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("l"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch32()
		return
	}
	go_to(label(compiled_branch33))
}

func compiled_branch33() {
	assign(cont, label(after_call34))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch32() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call34))
}

func after_call34() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch35()
		return
	}
	go_to(label(compiled_branch36))
}

func compiled_branch36() {
	assign(cont, label(after_call37))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch35() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call37))
}

func after_call37() {
	assign(argl, list(reg(val)))
	assign(val, constant("1"))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch38()
		return
	}
	go_to(label(compiled_branch39))
}

func compiled_branch39() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch38() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call40() {
	go_to(label(after_if28))
}

func after_if28() {
	go_to(label(after_lambda25))
}

func after_lambda25() {
	define_variable(constant("length"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry41), reg(env)))
	go_to(label(after_lambda42))
}

func entry41() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exps env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("no-operands?"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch46()
		return
	}
	go_to(label(compiled_branch47))
}

func compiled_branch47() {
	assign(cont, label(after_call48))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch46() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call48))
}

func after_call48() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch44()
		return
	}
	go_to(label(true_branch43))
}

func true_branch43() {
	assign(val, constant("()"))
	go_to(reg(cont))
}

func false_branch44() {
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("list-of-values"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("rest-operands"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch55()
		return
	}
	go_to(label(compiled_branch56))
}

func compiled_branch56() {
	assign(cont, label(after_call57))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch55() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call57))
}

func after_call57() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch58()
		return
	}
	go_to(label(compiled_branch59))
}

func compiled_branch59() {
	assign(cont, label(after_call60))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch58() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call60))
}

func after_call60() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("first-operand"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch49()
		return
	}
	go_to(label(compiled_branch50))
}

func compiled_branch50() {
	assign(cont, label(after_call51))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch49() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call51))
}

func after_call51() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch52()
		return
	}
	go_to(label(compiled_branch53))
}

func compiled_branch53() {
	assign(cont, label(after_call54))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch52() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call54))
}

func after_call54() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch61()
		return
	}
	go_to(label(compiled_branch62))
}

func compiled_branch62() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch61() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call63() {
	go_to(label(after_if45))
}

func after_if45() {
	go_to(label(after_lambda42))
}

func after_lambda42() {
	define_variable(constant("list-of-values"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry64), reg(env)))
	go_to(label(after_lambda65))
}

func entry64() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("true?"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("if-predicate"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch69()
		return
	}
	go_to(label(compiled_branch70))
}

func compiled_branch70() {
	assign(cont, label(after_call71))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch69() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call71))
}

func after_call71() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch72()
		return
	}
	go_to(label(compiled_branch73))
}

func compiled_branch73() {
	assign(cont, label(after_call74))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch72() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call74))
}

func after_call74() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch75()
		return
	}
	go_to(label(compiled_branch76))
}

func compiled_branch76() {
	assign(cont, label(after_call77))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch75() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call77))
}

func after_call77() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch67()
		return
	}
	go_to(label(true_branch66))
}

func true_branch66() {
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("if-consequent"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch78()
		return
	}
	go_to(label(compiled_branch79))
}

func compiled_branch79() {
	assign(cont, label(after_call80))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch78() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call80))
}

func after_call80() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch81()
		return
	}
	go_to(label(compiled_branch82))
}

func compiled_branch82() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch81() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call83() {
	go_to(label(false_branch67))
}

func false_branch67() {
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("if-alternative"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch84()
		return
	}
	go_to(label(compiled_branch85))
}

func compiled_branch85() {
	assign(cont, label(after_call86))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch84() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call86))
}

func after_call86() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch87()
		return
	}
	go_to(label(compiled_branch88))
}

func compiled_branch88() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch87() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call89() {
	go_to(label(after_if68))
}

func after_if68() {
	go_to(label(after_lambda65))
}

func after_lambda65() {
	define_variable(constant("eval-if"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry90), reg(env)))
	go_to(label(after_lambda91))
}

func entry90() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exps env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("last-exp?"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch95()
		return
	}
	go_to(label(compiled_branch96))
}

func compiled_branch96() {
	assign(cont, label(after_call97))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch95() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call97))
}

func after_call97() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch93()
		return
	}
	go_to(label(true_branch92))
}

func true_branch92() {
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("first-exp"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch98()
		return
	}
	go_to(label(compiled_branch99))
}

func compiled_branch99() {
	assign(cont, label(after_call100))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch98() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call100))
}

func after_call100() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch101()
		return
	}
	go_to(label(compiled_branch102))
}

func compiled_branch102() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch101() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call103() {
	go_to(label(false_branch93))
}

func false_branch93() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("first-exp"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch104()
		return
	}
	go_to(label(compiled_branch105))
}

func compiled_branch105() {
	assign(cont, label(after_call106))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch104() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call106))
}

func after_call106() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch107()
		return
	}
	go_to(label(compiled_branch108))
}

func compiled_branch108() {
	assign(cont, label(after_call109))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch107() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call109))
}

func after_call109() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("eval-sequence"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("rest-exps"), reg(env)))
	assign(val, lookup_variable_value(constant("exps"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch110()
		return
	}
	go_to(label(compiled_branch111))
}

func compiled_branch111() {
	assign(cont, label(after_call112))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch110() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call112))
}

func after_call112() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch113()
		return
	}
	go_to(label(compiled_branch114))
}

func compiled_branch114() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch113() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call115() {
	go_to(label(after_if94))
}

func after_if94() {
	go_to(label(after_lambda91))
}

func after_lambda91() {
	define_variable(constant("eval-sequence"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry116), reg(env)))
	go_to(label(after_lambda117))
}

func entry116() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp env)"), reg(argl), reg(env)))
	save(*cont)
	assign(proc, lookup_variable_value(constant("set-variable-value!"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("assignment-value"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch121()
		return
	}
	go_to(label(compiled_branch122))
}

func compiled_branch122() {
	assign(cont, label(after_call123))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch121() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call123))
}

func after_call123() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch124()
		return
	}
	go_to(label(compiled_branch125))
}

func compiled_branch125() {
	assign(cont, label(after_call126))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch124() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call126))
}

func after_call126() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("assignment-variable"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch118()
		return
	}
	go_to(label(compiled_branch119))
}

func compiled_branch119() {
	assign(cont, label(after_call120))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch118() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call120))
}

func after_call120() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch127()
		return
	}
	go_to(label(compiled_branch128))
}

func compiled_branch128() {
	assign(cont, label(after_call129))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch127() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call129))
}

func after_call129() {
	restore(cont)
	assign(val, constant("ok"))
	go_to(reg(cont))
}

func after_lambda117() {
	define_variable(constant("eval-assignment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry130), reg(env)))
	go_to(label(after_lambda131))
}

func entry130() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp env)"), reg(argl), reg(env)))
	save(*cont)
	assign(proc, lookup_variable_value(constant("define-variable!"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("definition-value"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch135()
		return
	}
	go_to(label(compiled_branch136))
}

func compiled_branch136() {
	assign(cont, label(after_call137))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch135() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call137))
}

func after_call137() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch138()
		return
	}
	go_to(label(compiled_branch139))
}

func compiled_branch139() {
	assign(cont, label(after_call140))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch138() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call140))
}

func after_call140() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("definition-variable"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch132()
		return
	}
	go_to(label(compiled_branch133))
}

func compiled_branch133() {
	assign(cont, label(after_call134))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch132() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call134))
}

func after_call134() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch141()
		return
	}
	go_to(label(compiled_branch142))
}

func compiled_branch142() {
	assign(cont, label(after_call143))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch141() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call143))
}

func after_call143() {
	restore(cont)
	assign(val, constant("ok"))
	go_to(reg(cont))
}

func after_lambda131() {
	define_variable(constant("eval-definition"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry144), reg(env)))
	go_to(label(after_lambda145))
}

func entry144() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("number?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch149()
		return
	}
	go_to(label(compiled_branch150))
}

func compiled_branch150() {
	assign(cont, label(after_call151))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch149() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call151))
}

func after_call151() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch147()
		return
	}
	go_to(label(true_branch146))
}

func true_branch146() {
	assign(val, lookup_variable_value(constant("true"), reg(env)))
	go_to(reg(cont))
}

func false_branch147() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("string?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch155()
		return
	}
	go_to(label(compiled_branch156))
}

func compiled_branch156() {
	assign(cont, label(after_call157))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch155() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call157))
}

func after_call157() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch153()
		return
	}
	go_to(label(true_branch152))
}

func true_branch152() {
	assign(val, lookup_variable_value(constant("true"), reg(env)))
	go_to(reg(cont))
}

func false_branch153() {
	assign(val, lookup_variable_value(constant("false"), reg(env)))
	go_to(reg(cont))
}

func after_if154() {
	go_to(label(after_if148))
}

func after_if148() {
	go_to(label(after_lambda145))
}

func after_lambda145() {
	define_variable(constant("self-evaluating?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry158), reg(env)))
	go_to(label(after_lambda159))
}

func entry158() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("symbol?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch160()
		return
	}
	go_to(label(compiled_branch161))
}

func compiled_branch161() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch160() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call162() {
	go_to(label(after_lambda159))
}

func after_lambda159() {
	define_variable(constant("variable?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry163), reg(env)))
	go_to(label(after_lambda164))
}

func entry163() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("quote"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch165()
		return
	}
	go_to(label(compiled_branch166))
}

func compiled_branch166() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch165() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call167() {
	go_to(label(after_lambda164))
}

func after_lambda164() {
	define_variable(constant("quoted?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry168), reg(env)))
	go_to(label(after_lambda169))
}

func entry168() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch170()
		return
	}
	go_to(label(compiled_branch171))
}

func compiled_branch171() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch170() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call172() {
	go_to(label(after_lambda169))
}

func after_lambda169() {
	define_variable(constant("text-of-quotation"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry173), reg(env)))
	go_to(label(after_lambda174))
}

func entry173() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp tag)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("pair?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch178()
		return
	}
	go_to(label(compiled_branch179))
}

func compiled_branch179() {
	assign(cont, label(after_call180))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch178() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call180))
}

func after_call180() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch176()
		return
	}
	go_to(label(true_branch175))
}

func true_branch175() {
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("tag"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch181()
		return
	}
	go_to(label(compiled_branch182))
}

func compiled_branch182() {
	assign(cont, label(after_call183))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch181() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call183))
}

func after_call183() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch184()
		return
	}
	go_to(label(compiled_branch185))
}

func compiled_branch185() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch184() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call186() {
	go_to(label(false_branch176))
}

func false_branch176() {
	assign(val, lookup_variable_value(constant("false"), reg(env)))
	go_to(reg(cont))
}

func after_if177() {
	go_to(label(after_lambda174))
}

func after_lambda174() {
	define_variable(constant("tagged-list?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry187), reg(env)))
	go_to(label(after_lambda188))
}

func entry187() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("set!"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch189()
		return
	}
	go_to(label(compiled_branch190))
}

func compiled_branch190() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch189() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call191() {
	go_to(label(after_lambda188))
}

func after_lambda188() {
	define_variable(constant("assignment?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry192), reg(env)))
	go_to(label(after_lambda193))
}

func entry192() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch194()
		return
	}
	go_to(label(compiled_branch195))
}

func compiled_branch195() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch194() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call196() {
	go_to(label(after_lambda193))
}

func after_lambda193() {
	define_variable(constant("assignment-variable"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry197), reg(env)))
	go_to(label(after_lambda198))
}

func entry197() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("caddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch199()
		return
	}
	go_to(label(compiled_branch200))
}

func compiled_branch200() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch199() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call201() {
	go_to(label(after_lambda198))
}

func after_lambda198() {
	define_variable(constant("assignment-value"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry202), reg(env)))
	go_to(label(after_lambda203))
}

func entry202() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("define"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch204()
		return
	}
	go_to(label(compiled_branch205))
}

func compiled_branch205() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch204() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call206() {
	go_to(label(after_lambda203))
}

func after_lambda203() {
	define_variable(constant("definition?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry207), reg(env)))
	go_to(label(after_lambda208))
}

func entry207() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("symbol?"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch212()
		return
	}
	go_to(label(compiled_branch213))
}

func compiled_branch213() {
	assign(cont, label(after_call214))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch212() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call214))
}

func after_call214() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch215()
		return
	}
	go_to(label(compiled_branch216))
}

func compiled_branch216() {
	assign(cont, label(after_call217))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch215() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call217))
}

func after_call217() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch210()
		return
	}
	go_to(label(true_branch209))
}

func true_branch209() {
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch218()
		return
	}
	go_to(label(compiled_branch219))
}

func compiled_branch219() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch218() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call220() {
	go_to(label(false_branch210))
}

func false_branch210() {
	assign(proc, lookup_variable_value(constant("caadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch221()
		return
	}
	go_to(label(compiled_branch222))
}

func compiled_branch222() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch221() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call223() {
	go_to(label(after_if211))
}

func after_if211() {
	go_to(label(after_lambda208))
}

func after_lambda208() {
	define_variable(constant("definition-variable"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry224), reg(env)))
	go_to(label(after_lambda225))
}

func entry224() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("symbol?"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch229()
		return
	}
	go_to(label(compiled_branch230))
}

func compiled_branch230() {
	assign(cont, label(after_call231))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch229() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call231))
}

func after_call231() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch232()
		return
	}
	go_to(label(compiled_branch233))
}

func compiled_branch233() {
	assign(cont, label(after_call234))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch232() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call234))
}

func after_call234() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch227()
		return
	}
	go_to(label(true_branch226))
}

func true_branch226() {
	assign(proc, lookup_variable_value(constant("caddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch235()
		return
	}
	go_to(label(compiled_branch236))
}

func compiled_branch236() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch235() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call237() {
	go_to(label(false_branch227))
}

func false_branch227() {
	assign(proc, lookup_variable_value(constant("make-lambda"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch241()
		return
	}
	go_to(label(compiled_branch242))
}

func compiled_branch242() {
	assign(cont, label(after_call243))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch241() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call243))
}

func after_call243() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("cdadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch238()
		return
	}
	go_to(label(compiled_branch239))
}

func compiled_branch239() {
	assign(cont, label(after_call240))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch238() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call240))
}

func after_call240() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch244()
		return
	}
	go_to(label(compiled_branch245))
}

func compiled_branch245() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch244() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call246() {
	go_to(label(after_if228))
}

func after_if228() {
	go_to(label(after_lambda225))
}

func after_lambda225() {
	define_variable(constant("definition-value"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry247), reg(env)))
	go_to(label(after_lambda248))
}

func entry247() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("lambda"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch249()
		return
	}
	go_to(label(compiled_branch250))
}

func compiled_branch250() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch249() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call251() {
	go_to(label(after_lambda248))
}

func after_lambda248() {
	define_variable(constant("lambda?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry252), reg(env)))
	go_to(label(after_lambda253))
}

func entry252() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch254()
		return
	}
	go_to(label(compiled_branch255))
}

func compiled_branch255() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch254() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call256() {
	go_to(label(after_lambda253))
}

func after_lambda253() {
	define_variable(constant("lambda-parameters"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry257), reg(env)))
	go_to(label(after_lambda258))
}

func entry257() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch259()
		return
	}
	go_to(label(compiled_branch260))
}

func compiled_branch260() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch259() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call261() {
	go_to(label(after_lambda258))
}

func after_lambda258() {
	define_variable(constant("lambda-body"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry262), reg(env)))
	go_to(label(after_lambda263))
}

func entry262() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(parameters body)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	assign(val, lookup_variable_value(constant("body"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("parameters"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch264()
		return
	}
	go_to(label(compiled_branch265))
}

func compiled_branch265() {
	assign(cont, label(after_call266))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch264() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call266))
}

func after_call266() {
	assign(argl, list(reg(val)))
	assign(val, constant("lambda"))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch267()
		return
	}
	go_to(label(compiled_branch268))
}

func compiled_branch268() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch267() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call269() {
	go_to(label(after_lambda263))
}

func after_lambda263() {
	define_variable(constant("make-lambda"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry270), reg(env)))
	go_to(label(after_lambda271))
}

func entry270() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("if"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch272()
		return
	}
	go_to(label(compiled_branch273))
}

func compiled_branch273() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch272() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call274() {
	go_to(label(after_lambda271))
}

func after_lambda271() {
	define_variable(constant("if?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry275), reg(env)))
	go_to(label(after_lambda276))
}

func entry275() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch277()
		return
	}
	go_to(label(compiled_branch278))
}

func compiled_branch278() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch277() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call279() {
	go_to(label(after_lambda276))
}

func after_lambda276() {
	define_variable(constant("if-predicate"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry280), reg(env)))
	go_to(label(after_lambda281))
}

func entry280() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("caddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch282()
		return
	}
	go_to(label(compiled_branch283))
}

func compiled_branch283() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch282() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call284() {
	go_to(label(after_lambda281))
}

func after_lambda281() {
	define_variable(constant("if-consequent"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry285), reg(env)))
	go_to(label(after_lambda286))
}

func entry285() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("not"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("cdddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch290()
		return
	}
	go_to(label(compiled_branch291))
}

func compiled_branch291() {
	assign(cont, label(after_call292))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch290() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call292))
}

func after_call292() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch293()
		return
	}
	go_to(label(compiled_branch294))
}

func compiled_branch294() {
	assign(cont, label(after_call295))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch293() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call295))
}

func after_call295() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch296()
		return
	}
	go_to(label(compiled_branch297))
}

func compiled_branch297() {
	assign(cont, label(after_call298))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch296() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call298))
}

func after_call298() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch288()
		return
	}
	go_to(label(true_branch287))
}

func true_branch287() {
	assign(proc, lookup_variable_value(constant("cadddr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch299()
		return
	}
	go_to(label(compiled_branch300))
}

func compiled_branch300() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch299() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call301() {
	go_to(label(false_branch288))
}

func false_branch288() {
	assign(val, constant("false"))
	go_to(reg(cont))
}

func after_if289() {
	go_to(label(after_lambda286))
}

func after_lambda286() {
	define_variable(constant("if-alternative"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry302), reg(env)))
	go_to(label(after_lambda303))
}

func entry302() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(predicate consequent alternative)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("alternative"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("consequent"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, lookup_variable_value(constant("predicate"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("if"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch304()
		return
	}
	go_to(label(compiled_branch305))
}

func compiled_branch305() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch304() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call306() {
	go_to(label(after_lambda303))
}

func after_lambda303() {
	define_variable(constant("make-if"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry307), reg(env)))
	go_to(label(after_lambda308))
}

func entry307() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("begin"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch309()
		return
	}
	go_to(label(compiled_branch310))
}

func compiled_branch310() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch309() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call311() {
	go_to(label(after_lambda308))
}

func after_lambda308() {
	define_variable(constant("begin?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry312), reg(env)))
	go_to(label(after_lambda313))
}

func entry312() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch314()
		return
	}
	go_to(label(compiled_branch315))
}

func compiled_branch315() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch314() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call316() {
	go_to(label(after_lambda313))
}

func after_lambda313() {
	define_variable(constant("begin-actions"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry317), reg(env)))
	go_to(label(after_lambda318))
}

func entry317() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(seq)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch319()
		return
	}
	go_to(label(compiled_branch320))
}

func compiled_branch320() {
	assign(cont, label(after_call321))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch319() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call321))
}

func after_call321() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch322()
		return
	}
	go_to(label(compiled_branch323))
}

func compiled_branch323() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch322() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call324() {
	go_to(label(after_lambda318))
}

func after_lambda318() {
	define_variable(constant("last-exp?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry325), reg(env)))
	go_to(label(after_lambda326))
}

func entry325() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(seq)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch327()
		return
	}
	go_to(label(compiled_branch328))
}

func compiled_branch328() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch327() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call329() {
	go_to(label(after_lambda326))
}

func after_lambda326() {
	define_variable(constant("first-exp"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry330), reg(env)))
	go_to(label(after_lambda331))
}

func entry330() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(seq)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch332()
		return
	}
	go_to(label(compiled_branch333))
}

func compiled_branch333() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch332() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call334() {
	go_to(label(after_lambda331))
}

func after_lambda331() {
	define_variable(constant("rest-exps"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry335), reg(env)))
	go_to(label(after_lambda336))
}

func entry335() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(seq)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch340()
		return
	}
	go_to(label(compiled_branch341))
}

func compiled_branch341() {
	assign(cont, label(after_call342))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch340() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call342))
}

func after_call342() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch338()
		return
	}
	go_to(label(true_branch337))
}

func true_branch337() {
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	go_to(reg(cont))
}

func false_branch338() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("last-exp?"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch346()
		return
	}
	go_to(label(compiled_branch347))
}

func compiled_branch347() {
	assign(cont, label(after_call348))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch346() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call348))
}

func after_call348() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch344()
		return
	}
	go_to(label(true_branch343))
}

func true_branch343() {
	assign(proc, lookup_variable_value(constant("first-exp"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch349()
		return
	}
	go_to(label(compiled_branch350))
}

func compiled_branch350() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch349() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call351() {
	go_to(label(false_branch344))
}

func false_branch344() {
	assign(proc, lookup_variable_value(constant("make-begin"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch352()
		return
	}
	go_to(label(compiled_branch353))
}

func compiled_branch353() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch352() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call354() {
	go_to(label(after_if345))
}

func after_if345() {
	go_to(label(after_if339))
}

func after_if339() {
	go_to(label(after_lambda336))
}

func after_lambda336() {
	define_variable(constant("sequence->exp"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry355), reg(env)))
	go_to(label(after_lambda356))
}

func entry355() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(seq)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	assign(val, lookup_variable_value(constant("seq"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("begin"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch357()
		return
	}
	go_to(label(compiled_branch358))
}

func compiled_branch358() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch357() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call359() {
	go_to(label(after_lambda356))
}

func after_lambda356() {
	define_variable(constant("make-begin"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry360), reg(env)))
	go_to(label(after_lambda361))
}

func entry360() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("pair?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch362()
		return
	}
	go_to(label(compiled_branch363))
}

func compiled_branch363() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch362() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call364() {
	go_to(label(after_lambda361))
}

func after_lambda361() {
	define_variable(constant("application?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry365), reg(env)))
	go_to(label(after_lambda366))
}

func entry365() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch367()
		return
	}
	go_to(label(compiled_branch368))
}

func compiled_branch368() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch367() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call369() {
	go_to(label(after_lambda366))
}

func after_lambda366() {
	define_variable(constant("operator"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry370), reg(env)))
	go_to(label(after_lambda371))
}

func entry370() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch372()
		return
	}
	go_to(label(compiled_branch373))
}

func compiled_branch373() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch372() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call374() {
	go_to(label(after_lambda371))
}

func after_lambda371() {
	define_variable(constant("operands"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry375), reg(env)))
	go_to(label(after_lambda376))
}

func entry375() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("s"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("ops"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch377()
		return
	}
	go_to(label(compiled_branch378))
}

func compiled_branch378() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch377() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call379() {
	go_to(label(after_lambda376))
}

func after_lambda376() {
	define_variable(constant("no-operands?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry380), reg(env)))
	go_to(label(after_lambda381))
}

func entry380() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("s"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("ops"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch382()
		return
	}
	go_to(label(compiled_branch383))
}

func compiled_branch383() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch382() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call384() {
	go_to(label(after_lambda381))
}

func after_lambda381() {
	define_variable(constant("first-operand"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry385), reg(env)))
	go_to(label(after_lambda386))
}

func entry385() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("s"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("ops"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch387()
		return
	}
	go_to(label(compiled_branch388))
}

func compiled_branch388() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch387() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call389() {
	go_to(label(after_lambda386))
}

func after_lambda386() {
	define_variable(constant("rest-operands"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry390), reg(env)))
	go_to(label(after_lambda391))
}

func entry390() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("cond"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch392()
		return
	}
	go_to(label(compiled_branch393))
}

func compiled_branch393() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch392() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call394() {
	go_to(label(after_lambda391))
}

func after_lambda391() {
	define_variable(constant("cond?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry395), reg(env)))
	go_to(label(after_lambda396))
}

func entry395() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch397()
		return
	}
	go_to(label(compiled_branch398))
}

func compiled_branch398() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch397() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call399() {
	go_to(label(after_lambda396))
}

func after_lambda396() {
	define_variable(constant("cond-clauses"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry400), reg(env)))
	go_to(label(after_lambda401))
}

func entry400() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(clause)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, constant("else"))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("cond-predicate"), reg(env)))
	assign(val, lookup_variable_value(constant("clause"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch402()
		return
	}
	go_to(label(compiled_branch403))
}

func compiled_branch403() {
	assign(cont, label(after_call404))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch402() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call404))
}

func after_call404() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch405()
		return
	}
	go_to(label(compiled_branch406))
}

func compiled_branch406() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch405() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call407() {
	go_to(label(after_lambda401))
}

func after_lambda401() {
	define_variable(constant("cond-else-clause?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry408), reg(env)))
	go_to(label(after_lambda409))
}

func entry408() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(clause)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("clause"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch410()
		return
	}
	go_to(label(compiled_branch411))
}

func compiled_branch411() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch410() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call412() {
	go_to(label(after_lambda409))
}

func after_lambda409() {
	define_variable(constant("cond-predicate"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry413), reg(env)))
	go_to(label(after_lambda414))
}

func entry413() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(clause)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("clause"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch415()
		return
	}
	go_to(label(compiled_branch416))
}

func compiled_branch416() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch415() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call417() {
	go_to(label(after_lambda414))
}

func after_lambda414() {
	define_variable(constant("cond-actions"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry418), reg(env)))
	go_to(label(after_lambda419))
}

func entry418() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("expand-clauses"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("cond-clauses"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch420()
		return
	}
	go_to(label(compiled_branch421))
}

func compiled_branch421() {
	assign(cont, label(after_call422))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch420() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call422))
}

func after_call422() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch423()
		return
	}
	go_to(label(compiled_branch424))
}

func compiled_branch424() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch423() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call425() {
	go_to(label(after_lambda419))
}

func after_lambda419() {
	define_variable(constant("cond->if"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry426), reg(env)))
	go_to(label(after_lambda427))
}

func entry426() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(clauses)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("clauses"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch431()
		return
	}
	go_to(label(compiled_branch432))
}

func compiled_branch432() {
	assign(cont, label(after_call433))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch431() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call433))
}

func after_call433() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch429()
		return
	}
	go_to(label(true_branch428))
}

func true_branch428() {
	assign(val, constant("false"))
	go_to(reg(cont))
}

func false_branch429() {
	assign(proc, make_compiled_procedure(label(entry434), reg(env)))
	go_to(label(after_lambda435))
}

func entry434() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(first rest)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("cond-else-clause?"), reg(env)))
	assign(val, lookup_variable_value(constant("first"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch439()
		return
	}
	go_to(label(compiled_branch440))
}

func compiled_branch440() {
	assign(cont, label(after_call441))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch439() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call441))
}

func after_call441() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch437()
		return
	}
	go_to(label(true_branch436))
}

func true_branch436() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("rest"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch445()
		return
	}
	go_to(label(compiled_branch446))
}

func compiled_branch446() {
	assign(cont, label(after_call447))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch445() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call447))
}

func after_call447() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch443()
		return
	}
	go_to(label(true_branch442))
}

func true_branch442() {
	assign(proc, lookup_variable_value(constant("sequence->exp"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("cond-actions"), reg(env)))
	assign(val, lookup_variable_value(constant("first"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch448()
		return
	}
	go_to(label(compiled_branch449))
}

func compiled_branch449() {
	assign(cont, label(after_call450))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch448() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call450))
}

func after_call450() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch451()
		return
	}
	go_to(label(compiled_branch452))
}

func compiled_branch452() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch451() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call453() {
	go_to(label(false_branch443))
}

func false_branch443() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("clauses"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("ELSE clause isn't last -- COND->IF"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch454()
		return
	}
	go_to(label(compiled_branch455))
}

func compiled_branch455() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch454() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call456() {
	go_to(label(after_if444))
}

func after_if444() {
	go_to(label(false_branch437))
}

func false_branch437() {
	assign(proc, lookup_variable_value(constant("make-if"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("expand-clauses"), reg(env)))
	assign(val, lookup_variable_value(constant("rest"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch466()
		return
	}
	go_to(label(compiled_branch467))
}

func compiled_branch467() {
	assign(cont, label(after_call468))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch466() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call468))
}

func after_call468() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("sequence->exp"), reg(env)))
	save(*proc)
	assign(proc, lookup_variable_value(constant("cond-actions"), reg(env)))
	assign(val, lookup_variable_value(constant("first"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch460()
		return
	}
	go_to(label(compiled_branch461))
}

func compiled_branch461() {
	assign(cont, label(after_call462))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch460() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call462))
}

func after_call462() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch463()
		return
	}
	go_to(label(compiled_branch464))
}

func compiled_branch464() {
	assign(cont, label(after_call465))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch463() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call465))
}

func after_call465() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("cond-predicate"), reg(env)))
	assign(val, lookup_variable_value(constant("first"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch457()
		return
	}
	go_to(label(compiled_branch458))
}

func compiled_branch458() {
	assign(cont, label(after_call459))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch457() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call459))
}

func after_call459() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch469()
		return
	}
	go_to(label(compiled_branch470))
}

func compiled_branch470() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch469() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call471() {
	go_to(label(after_if438))
}

func after_if438() {
	go_to(label(after_lambda435))
}

func after_lambda435() {
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("clauses"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch475()
		return
	}
	go_to(label(compiled_branch476))
}

func compiled_branch476() {
	assign(cont, label(after_call477))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch475() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call477))
}

func after_call477() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("clauses"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch472()
		return
	}
	go_to(label(compiled_branch473))
}

func compiled_branch473() {
	assign(cont, label(after_call474))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch472() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call474))
}

func after_call474() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch478()
		return
	}
	go_to(label(compiled_branch479))
}

func compiled_branch479() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch478() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call480() {
	go_to(label(after_if430))
}

func after_if430() {
	go_to(label(after_lambda427))
}

func after_lambda427() {
	define_variable(constant("expand-clauses"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry481), reg(env)))
	go_to(label(after_lambda482))
}

func entry481() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(x)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("not"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	assign(val, lookup_variable_value(constant("false"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("x"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch483()
		return
	}
	go_to(label(compiled_branch484))
}

func compiled_branch484() {
	assign(cont, label(after_call485))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch483() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call485))
}

func after_call485() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch486()
		return
	}
	go_to(label(compiled_branch487))
}

func compiled_branch487() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch486() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call488() {
	go_to(label(after_lambda482))
}

func after_lambda482() {
	define_variable(constant("true?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry489), reg(env)))
	go_to(label(after_lambda490))
}

func entry489() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(x)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	assign(val, lookup_variable_value(constant("false"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("x"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch491()
		return
	}
	go_to(label(compiled_branch492))
}

func compiled_branch492() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch491() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call493() {
	go_to(label(after_lambda490))
}

func after_lambda490() {
	define_variable(constant("false?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry494), reg(env)))
	go_to(label(after_lambda495))
}

func entry494() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(parameters body env)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("body"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, lookup_variable_value(constant("parameters"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("procedure"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch496()
		return
	}
	go_to(label(compiled_branch497))
}

func compiled_branch497() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch496() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call498() {
	go_to(label(after_lambda495))
}

func after_lambda495() {
	define_variable(constant("make-procedure"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry499), reg(env)))
	go_to(label(after_lambda500))
}

func entry499() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(p)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("procedure"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("p"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch501()
		return
	}
	go_to(label(compiled_branch502))
}

func compiled_branch502() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch501() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call503() {
	go_to(label(after_lambda500))
}

func after_lambda500() {
	define_variable(constant("compound-procedure?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry504), reg(env)))
	go_to(label(after_lambda505))
}

func entry504() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(p)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("p"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch506()
		return
	}
	go_to(label(compiled_branch507))
}

func compiled_branch507() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch506() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call508() {
	go_to(label(after_lambda505))
}

func after_lambda505() {
	define_variable(constant("procedure-parameters"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry509), reg(env)))
	go_to(label(after_lambda510))
}

func entry509() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(p)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("caddr"), reg(env)))
	assign(val, lookup_variable_value(constant("p"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch511()
		return
	}
	go_to(label(compiled_branch512))
}

func compiled_branch512() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch511() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call513() {
	go_to(label(after_lambda510))
}

func after_lambda510() {
	define_variable(constant("procedure-body"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry514), reg(env)))
	go_to(label(after_lambda515))
}

func entry514() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(p)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadddr"), reg(env)))
	assign(val, lookup_variable_value(constant("p"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch516()
		return
	}
	go_to(label(compiled_branch517))
}

func compiled_branch517() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch516() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call518() {
	go_to(label(after_lambda515))
}

func after_lambda515() {
	define_variable(constant("procedure-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry519), reg(env)))
	go_to(label(after_lambda520))
}

func entry519() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(env)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch521()
		return
	}
	go_to(label(compiled_branch522))
}

func compiled_branch522() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch521() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call523() {
	go_to(label(after_lambda520))
}

func after_lambda520() {
	define_variable(constant("enclosing-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry524), reg(env)))
	go_to(label(after_lambda525))
}

func entry524() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(env)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch526()
		return
	}
	go_to(label(compiled_branch527))
}

func compiled_branch527() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch526() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call528() {
	go_to(label(after_lambda525))
}

func after_lambda525() {
	define_variable(constant("first-frame"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, constant("()"))
	define_variable(constant("the-empty-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry529), reg(env)))
	go_to(label(after_lambda530))
}

func entry529() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(variables values)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	assign(val, lookup_variable_value(constant("values"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("variables"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch531()
		return
	}
	go_to(label(compiled_branch532))
}

func compiled_branch532() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch531() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call533() {
	go_to(label(after_lambda530))
}

func after_lambda530() {
	define_variable(constant("make-frame"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry534), reg(env)))
	go_to(label(after_lambda535))
}

func entry534() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(frame)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch536()
		return
	}
	go_to(label(compiled_branch537))
}

func compiled_branch537() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch536() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call538() {
	go_to(label(after_lambda535))
}

func after_lambda535() {
	define_variable(constant("frame-variables"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry539), reg(env)))
	go_to(label(after_lambda540))
}

func entry539() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(frame)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch541()
		return
	}
	go_to(label(compiled_branch542))
}

func compiled_branch542() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch541() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call543() {
	go_to(label(after_lambda540))
}

func after_lambda540() {
	define_variable(constant("frame-values"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry544), reg(env)))
	go_to(label(after_lambda545))
}

func entry544() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(var val frame)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("set-car!"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch546()
		return
	}
	go_to(label(compiled_branch547))
}

func compiled_branch547() {
	assign(cont, label(after_call548))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch546() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call548))
}

func after_call548() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch549()
		return
	}
	go_to(label(compiled_branch550))
}

func compiled_branch550() {
	assign(cont, label(after_call551))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch549() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call551))
}

func after_call551() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch552()
		return
	}
	go_to(label(compiled_branch553))
}

func compiled_branch553() {
	assign(cont, label(after_call554))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch552() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call554))
}

func after_call554() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("set-cdr!"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch555()
		return
	}
	go_to(label(compiled_branch556))
}

func compiled_branch556() {
	assign(cont, label(after_call557))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch555() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call557))
}

func after_call557() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("val"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch558()
		return
	}
	go_to(label(compiled_branch559))
}

func compiled_branch559() {
	assign(cont, label(after_call560))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch558() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call560))
}

func after_call560() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch561()
		return
	}
	go_to(label(compiled_branch562))
}

func compiled_branch562() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch561() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call563() {
	go_to(label(after_lambda545))
}

func after_lambda545() {
	define_variable(constant("add-binding-to-frame!"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry564), reg(env)))
	go_to(label(after_lambda565))
}

func entry564() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(vars vals base-env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("="), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("length"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch572()
		return
	}
	go_to(label(compiled_branch573))
}

func compiled_branch573() {
	assign(cont, label(after_call574))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch572() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call574))
}

func after_call574() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("length"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch569()
		return
	}
	go_to(label(compiled_branch570))
}

func compiled_branch570() {
	assign(cont, label(after_call571))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch569() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call571))
}

func after_call571() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch575()
		return
	}
	go_to(label(compiled_branch576))
}

func compiled_branch576() {
	assign(cont, label(after_call577))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch575() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call577))
}

func after_call577() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch567()
		return
	}
	go_to(label(true_branch566))
}

func true_branch566() {
	assign(proc, lookup_variable_value(constant("cons"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("base-env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("make-frame"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch578()
		return
	}
	go_to(label(compiled_branch579))
}

func compiled_branch579() {
	assign(cont, label(after_call580))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch578() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call580))
}

func after_call580() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch581()
		return
	}
	go_to(label(compiled_branch582))
}

func compiled_branch582() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch581() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call583() {
	go_to(label(false_branch567))
}

func false_branch567() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("<"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("length"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch590()
		return
	}
	go_to(label(compiled_branch591))
}

func compiled_branch591() {
	assign(cont, label(after_call592))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch590() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call592))
}

func after_call592() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("length"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch587()
		return
	}
	go_to(label(compiled_branch588))
}

func compiled_branch588() {
	assign(cont, label(after_call589))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch587() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call589))
}

func after_call589() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch593()
		return
	}
	go_to(label(compiled_branch594))
}

func compiled_branch594() {
	assign(cont, label(after_call595))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch593() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call595))
}

func after_call595() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch585()
		return
	}
	go_to(label(true_branch584))
}

func true_branch584() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("Too many arguments supplied"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch596()
		return
	}
	go_to(label(compiled_branch597))
}

func compiled_branch597() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch596() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call598() {
	go_to(label(false_branch585))
}

func false_branch585() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("Too few arguments supplied"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch599()
		return
	}
	go_to(label(compiled_branch600))
}

func compiled_branch600() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch599() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call601() {
	go_to(label(after_if586))
}

func after_if586() {
	go_to(label(after_if568))
}

func after_if568() {
	go_to(label(after_lambda565))
}

func after_lambda565() {
	define_variable(constant("extend-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry602), reg(env)))
	go_to(label(after_lambda603))
}

func entry602() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(var env)"), reg(argl), reg(env)))
	assign(val, make_compiled_procedure(label(entry604), reg(env)))
	go_to(label(after_lambda605))
}

func entry604() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(env)"), reg(argl), reg(env)))
	assign(val, make_compiled_procedure(label(entry606), reg(env)))
	go_to(label(after_lambda607))
}

func entry606() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(vars vals)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch611()
		return
	}
	go_to(label(compiled_branch612))
}

func compiled_branch612() {
	assign(cont, label(after_call613))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch611() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call613))
}

func after_call613() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch609()
		return
	}
	go_to(label(true_branch608))
}

func true_branch608() {
	assign(proc, lookup_variable_value(constant("env-loop"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("enclosing-environment"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch614()
		return
	}
	go_to(label(compiled_branch615))
}

func compiled_branch615() {
	assign(cont, label(after_call616))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch614() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call616))
}

func after_call616() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch617()
		return
	}
	go_to(label(compiled_branch618))
}

func compiled_branch618() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch617() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call619() {
	go_to(label(false_branch609))
}

func false_branch609() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch623()
		return
	}
	go_to(label(compiled_branch624))
}

func compiled_branch624() {
	assign(cont, label(after_call625))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch623() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call625))
}

func after_call625() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch626()
		return
	}
	go_to(label(compiled_branch627))
}

func compiled_branch627() {
	assign(cont, label(after_call628))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch626() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call628))
}

func after_call628() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch621()
		return
	}
	go_to(label(true_branch620))
}

func true_branch620() {
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch629()
		return
	}
	go_to(label(compiled_branch630))
}

func compiled_branch630() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch629() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call631() {
	go_to(label(false_branch621))
}

func false_branch621() {
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch635()
		return
	}
	go_to(label(compiled_branch636))
}

func compiled_branch636() {
	assign(cont, label(after_call637))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch635() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call637))
}

func after_call637() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch632()
		return
	}
	go_to(label(compiled_branch633))
}

func compiled_branch633() {
	assign(cont, label(after_call634))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch632() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call634))
}

func after_call634() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch638()
		return
	}
	go_to(label(compiled_branch639))
}

func compiled_branch639() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch638() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call640() {
	go_to(label(after_if622))
}

func after_if622() {
	go_to(label(after_if610))
}

func after_if610() {
	go_to(label(after_lambda607))
}

func after_lambda607() {
	define_variable(constant("scan"), reg(val), reg(env))
	assign(val, constant("ok"))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	assign(val, lookup_variable_value(constant("the-empty-environment"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch644()
		return
	}
	go_to(label(compiled_branch645))
}

func compiled_branch645() {
	assign(cont, label(after_call646))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch644() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call646))
}

func after_call646() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch642()
		return
	}
	go_to(label(true_branch641))
}

func true_branch641() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("Unbound variable"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch647()
		return
	}
	go_to(label(compiled_branch648))
}

func compiled_branch648() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch647() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call649() {
	go_to(label(false_branch642))
}

func false_branch642() {
	assign(proc, make_compiled_procedure(label(entry650), reg(env)))
	go_to(label(after_lambda651))
}

func entry650() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(frame)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("frame-values"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch655()
		return
	}
	go_to(label(compiled_branch656))
}

func compiled_branch656() {
	assign(cont, label(after_call657))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch655() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call657))
}

func after_call657() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("frame-variables"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch652()
		return
	}
	go_to(label(compiled_branch653))
}

func compiled_branch653() {
	assign(cont, label(after_call654))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch652() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call654))
}

func after_call654() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch658()
		return
	}
	go_to(label(compiled_branch659))
}

func compiled_branch659() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch658() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call660() {
	go_to(label(after_lambda651))
}

func after_lambda651() {
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("first-frame"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch661()
		return
	}
	go_to(label(compiled_branch662))
}

func compiled_branch662() {
	assign(cont, label(after_call663))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch661() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call663))
}

func after_call663() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch664()
		return
	}
	go_to(label(compiled_branch665))
}

func compiled_branch665() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch664() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call666() {
	go_to(label(after_if643))
}

func after_if643() {
	go_to(label(after_lambda605))
}

func after_lambda605() {
	define_variable(constant("env-loop"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(proc, lookup_variable_value(constant("env-loop"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch667()
		return
	}
	go_to(label(compiled_branch668))
}

func compiled_branch668() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch667() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call669() {
	go_to(label(after_lambda603))
}

func after_lambda603() {
	define_variable(constant("lookup-variable-value"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry670), reg(env)))
	go_to(label(after_lambda671))
}

func entry670() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(var val env)"), reg(argl), reg(env)))
	assign(val, make_compiled_procedure(label(entry672), reg(env)))
	go_to(label(after_lambda673))
}

func entry672() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(env)"), reg(argl), reg(env)))
	assign(val, make_compiled_procedure(label(entry674), reg(env)))
	go_to(label(after_lambda675))
}

func entry674() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(vars vals)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch679()
		return
	}
	go_to(label(compiled_branch680))
}

func compiled_branch680() {
	assign(cont, label(after_call681))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch679() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call681))
}

func after_call681() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch677()
		return
	}
	go_to(label(true_branch676))
}

func true_branch676() {
	assign(proc, lookup_variable_value(constant("env-loop"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("enclosing-environment"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch682()
		return
	}
	go_to(label(compiled_branch683))
}

func compiled_branch683() {
	assign(cont, label(after_call684))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch682() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call684))
}

func after_call684() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch685()
		return
	}
	go_to(label(compiled_branch686))
}

func compiled_branch686() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch685() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call687() {
	go_to(label(false_branch677))
}

func false_branch677() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch691()
		return
	}
	go_to(label(compiled_branch692))
}

func compiled_branch692() {
	assign(cont, label(after_call693))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch691() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call693))
}

func after_call693() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch694()
		return
	}
	go_to(label(compiled_branch695))
}

func compiled_branch695() {
	assign(cont, label(after_call696))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch694() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call696))
}

func after_call696() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch689()
		return
	}
	go_to(label(true_branch688))
}

func true_branch688() {
	assign(proc, lookup_variable_value(constant("set-car!"), reg(env)))
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch697()
		return
	}
	go_to(label(compiled_branch698))
}

func compiled_branch698() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch697() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call699() {
	go_to(label(false_branch689))
}

func false_branch689() {
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch703()
		return
	}
	go_to(label(compiled_branch704))
}

func compiled_branch704() {
	assign(cont, label(after_call705))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch703() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call705))
}

func after_call705() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch700()
		return
	}
	go_to(label(compiled_branch701))
}

func compiled_branch701() {
	assign(cont, label(after_call702))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch700() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call702))
}

func after_call702() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch706()
		return
	}
	go_to(label(compiled_branch707))
}

func compiled_branch707() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch706() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call708() {
	go_to(label(after_if690))
}

func after_if690() {
	go_to(label(after_if678))
}

func after_if678() {
	go_to(label(after_lambda675))
}

func after_lambda675() {
	define_variable(constant("scan"), reg(val), reg(env))
	assign(val, constant("ok"))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	assign(val, lookup_variable_value(constant("the-empty-environment"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch712()
		return
	}
	go_to(label(compiled_branch713))
}

func compiled_branch713() {
	assign(cont, label(after_call714))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch712() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call714))
}

func after_call714() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch710()
		return
	}
	go_to(label(true_branch709))
}

func true_branch709() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("Unbound variable -- SET"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch715()
		return
	}
	go_to(label(compiled_branch716))
}

func compiled_branch716() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch715() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call717() {
	go_to(label(false_branch710))
}

func false_branch710() {
	assign(proc, make_compiled_procedure(label(entry718), reg(env)))
	go_to(label(after_lambda719))
}

func entry718() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(frame)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("frame-values"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch723()
		return
	}
	go_to(label(compiled_branch724))
}

func compiled_branch724() {
	assign(cont, label(after_call725))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch723() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call725))
}

func after_call725() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("frame-variables"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch720()
		return
	}
	go_to(label(compiled_branch721))
}

func compiled_branch721() {
	assign(cont, label(after_call722))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch720() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call722))
}

func after_call722() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch726()
		return
	}
	go_to(label(compiled_branch727))
}

func compiled_branch727() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch726() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call728() {
	go_to(label(after_lambda719))
}

func after_lambda719() {
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("first-frame"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch729()
		return
	}
	go_to(label(compiled_branch730))
}

func compiled_branch730() {
	assign(cont, label(after_call731))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch729() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call731))
}

func after_call731() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch732()
		return
	}
	go_to(label(compiled_branch733))
}

func compiled_branch733() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch732() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call734() {
	go_to(label(after_if711))
}

func after_if711() {
	go_to(label(after_lambda673))
}

func after_lambda673() {
	define_variable(constant("env-loop"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(proc, lookup_variable_value(constant("env-loop"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch735()
		return
	}
	go_to(label(compiled_branch736))
}

func compiled_branch736() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch735() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call737() {
	go_to(label(after_lambda671))
}

func after_lambda671() {
	define_variable(constant("set-variable-value!"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry738), reg(env)))
	go_to(label(after_lambda739))
}

func entry738() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(var val env)"), reg(argl), reg(env)))
	assign(proc, make_compiled_procedure(label(entry740), reg(env)))
	go_to(label(after_lambda741))
}

func entry740() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(frame)"), reg(argl), reg(env)))
	assign(val, make_compiled_procedure(label(entry742), reg(env)))
	go_to(label(after_lambda743))
}

func entry742() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(vars vals)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("null?"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch747()
		return
	}
	go_to(label(compiled_branch748))
}

func compiled_branch748() {
	assign(cont, label(after_call749))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch747() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call749))
}

func after_call749() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch745()
		return
	}
	go_to(label(true_branch744))
}

func true_branch744() {
	assign(proc, lookup_variable_value(constant("add-binding-to-frame!"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("val"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch750()
		return
	}
	go_to(label(compiled_branch751))
}

func compiled_branch751() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch750() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call752() {
	go_to(label(false_branch745))
}

func false_branch745() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("eq?"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("car"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch756()
		return
	}
	go_to(label(compiled_branch757))
}

func compiled_branch757() {
	assign(cont, label(after_call758))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch756() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call758))
}

func after_call758() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("var"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch759()
		return
	}
	go_to(label(compiled_branch760))
}

func compiled_branch760() {
	assign(cont, label(after_call761))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch759() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call761))
}

func after_call761() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch754()
		return
	}
	go_to(label(true_branch753))
}

func true_branch753() {
	assign(proc, lookup_variable_value(constant("set-car!"), reg(env)))
	assign(val, lookup_variable_value(constant("val"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch762()
		return
	}
	go_to(label(compiled_branch763))
}

func compiled_branch763() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch762() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call764() {
	go_to(label(false_branch754))
}

func false_branch754() {
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vals"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch768()
		return
	}
	go_to(label(compiled_branch769))
}

func compiled_branch769() {
	assign(cont, label(after_call770))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch768() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call770))
}

func after_call770() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("cdr"), reg(env)))
	assign(val, lookup_variable_value(constant("vars"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch765()
		return
	}
	go_to(label(compiled_branch766))
}

func compiled_branch766() {
	assign(cont, label(after_call767))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch765() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call767))
}

func after_call767() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch771()
		return
	}
	go_to(label(compiled_branch772))
}

func compiled_branch772() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch771() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call773() {
	go_to(label(after_if755))
}

func after_if755() {
	go_to(label(after_if746))
}

func after_if746() {
	go_to(label(after_lambda743))
}

func after_lambda743() {
	define_variable(constant("scan"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(proc, lookup_variable_value(constant("scan"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("frame-values"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch777()
		return
	}
	go_to(label(compiled_branch778))
}

func compiled_branch778() {
	assign(cont, label(after_call779))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch777() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call779))
}

func after_call779() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("frame-variables"), reg(env)))
	assign(val, lookup_variable_value(constant("frame"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch774()
		return
	}
	go_to(label(compiled_branch775))
}

func compiled_branch775() {
	assign(cont, label(after_call776))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch774() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call776))
}

func after_call776() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch780()
		return
	}
	go_to(label(compiled_branch781))
}

func compiled_branch781() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch780() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call782() {
	go_to(label(after_lambda741))
}

func after_lambda741() {
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("first-frame"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch783()
		return
	}
	go_to(label(compiled_branch784))
}

func compiled_branch784() {
	assign(cont, label(after_call785))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch783() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call785))
}

func after_call785() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch786()
		return
	}
	go_to(label(compiled_branch787))
}

func compiled_branch787() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch786() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call788() {
	go_to(label(after_lambda739))
}

func after_lambda739() {
	define_variable(constant("define-variable!"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry789), reg(env)))
	go_to(label(after_lambda790))
}

func entry789() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc args)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("primitive-procedure?"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch794()
		return
	}
	go_to(label(compiled_branch795))
}

func compiled_branch795() {
	assign(cont, label(after_call796))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch794() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call796))
}

func after_call796() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch792()
		return
	}
	go_to(label(true_branch791))
}

func true_branch791() {
	assign(proc, lookup_variable_value(constant("apply-primitive-procedure"), reg(env)))
	assign(val, lookup_variable_value(constant("args"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch797()
		return
	}
	go_to(label(compiled_branch798))
}

func compiled_branch798() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch797() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call799() {
	go_to(label(false_branch792))
}

func false_branch792() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("compound-procedure?"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch803()
		return
	}
	go_to(label(compiled_branch804))
}

func compiled_branch804() {
	assign(cont, label(after_call805))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch803() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call805))
}

func after_call805() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch801()
		return
	}
	go_to(label(true_branch800))
}

func true_branch800() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("procedure-body"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch806()
		return
	}
	go_to(label(compiled_branch807))
}

func compiled_branch807() {
	assign(cont, label(proc_return809))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func proc_return809() {
	assign(proc, reg(val))
	go_to(label(after_call808))
}

func primitive_branch806() {
	assign(proc, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call808))
}

func after_call808() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("extend-environment"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("procedure-environment"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch813()
		return
	}
	go_to(label(compiled_branch814))
}

func compiled_branch814() {
	assign(cont, label(after_call815))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch813() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call815))
}

func after_call815() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("args"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("procedure-parameters"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch810()
		return
	}
	go_to(label(compiled_branch811))
}

func compiled_branch811() {
	assign(cont, label(after_call812))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch810() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call812))
}

func after_call812() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch816()
		return
	}
	go_to(label(compiled_branch817))
}

func compiled_branch817() {
	assign(cont, label(after_call818))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch816() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call818))
}

func after_call818() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch819()
		return
	}
	go_to(label(compiled_branch820))
}

func compiled_branch820() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch819() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call821() {
	go_to(label(false_branch801))
}

func false_branch801() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("Unknown procedure type -- EXECUTE-APPLICATION"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch822()
		return
	}
	go_to(label(compiled_branch823))
}

func compiled_branch823() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch822() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call824() {
	go_to(label(after_if802))
}

func after_if802() {
	go_to(label(after_if793))
}

func after_if793() {
	go_to(label(after_lambda790))
}

func after_lambda790() {
	define_variable(constant("execute-application"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry825), reg(env)))
	go_to(label(after_lambda826))
}

func entry825() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(exp env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("self-evaluating?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch830()
		return
	}
	go_to(label(compiled_branch831))
}

func compiled_branch831() {
	assign(cont, label(after_call832))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch830() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call832))
}

func after_call832() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch828()
		return
	}
	go_to(label(true_branch827))
}

func true_branch827() {
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	go_to(reg(cont))
}

func false_branch828() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("variable?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch836()
		return
	}
	go_to(label(compiled_branch837))
}

func compiled_branch837() {
	assign(cont, label(after_call838))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch836() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call838))
}

func after_call838() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch834()
		return
	}
	go_to(label(true_branch833))
}

func true_branch833() {
	assign(proc, lookup_variable_value(constant("lookup-variable-value"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch839()
		return
	}
	go_to(label(compiled_branch840))
}

func compiled_branch840() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch839() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call841() {
	go_to(label(false_branch834))
}

func false_branch834() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("quoted?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch845()
		return
	}
	go_to(label(compiled_branch846))
}

func compiled_branch846() {
	assign(cont, label(after_call847))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch845() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call847))
}

func after_call847() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch843()
		return
	}
	go_to(label(true_branch842))
}

func true_branch842() {
	assign(proc, lookup_variable_value(constant("text-of-quotation"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch848()
		return
	}
	go_to(label(compiled_branch849))
}

func compiled_branch849() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch848() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call850() {
	go_to(label(false_branch843))
}

func false_branch843() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("assignment?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch854()
		return
	}
	go_to(label(compiled_branch855))
}

func compiled_branch855() {
	assign(cont, label(after_call856))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch854() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call856))
}

func after_call856() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch852()
		return
	}
	go_to(label(true_branch851))
}

func true_branch851() {
	assign(proc, lookup_variable_value(constant("eval-assignment"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch857()
		return
	}
	go_to(label(compiled_branch858))
}

func compiled_branch858() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch857() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call859() {
	go_to(label(false_branch852))
}

func false_branch852() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("definition?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch863()
		return
	}
	go_to(label(compiled_branch864))
}

func compiled_branch864() {
	assign(cont, label(after_call865))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch863() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call865))
}

func after_call865() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch861()
		return
	}
	go_to(label(true_branch860))
}

func true_branch860() {
	assign(proc, lookup_variable_value(constant("eval-definition"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch866()
		return
	}
	go_to(label(compiled_branch867))
}

func compiled_branch867() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch866() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call868() {
	go_to(label(false_branch861))
}

func false_branch861() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("if?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch872()
		return
	}
	go_to(label(compiled_branch873))
}

func compiled_branch873() {
	assign(cont, label(after_call874))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch872() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call874))
}

func after_call874() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch870()
		return
	}
	go_to(label(true_branch869))
}

func true_branch869() {
	assign(proc, lookup_variable_value(constant("eval-if"), reg(env)))
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch875()
		return
	}
	go_to(label(compiled_branch876))
}

func compiled_branch876() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch875() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call877() {
	go_to(label(false_branch870))
}

func false_branch870() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("lambda?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch881()
		return
	}
	go_to(label(compiled_branch882))
}

func compiled_branch882() {
	assign(cont, label(after_call883))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch881() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call883))
}

func after_call883() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch879()
		return
	}
	go_to(label(true_branch878))
}

func true_branch878() {
	assign(proc, lookup_variable_value(constant("make-procedure"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("lambda-body"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch887()
		return
	}
	go_to(label(compiled_branch888))
}

func compiled_branch888() {
	assign(cont, label(after_call889))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch887() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call889))
}

func after_call889() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("lambda-parameters"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch884()
		return
	}
	go_to(label(compiled_branch885))
}

func compiled_branch885() {
	assign(cont, label(after_call886))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch884() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call886))
}

func after_call886() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch890()
		return
	}
	go_to(label(compiled_branch891))
}

func compiled_branch891() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch890() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call892() {
	go_to(label(false_branch879))
}

func false_branch879() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("begin?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch896()
		return
	}
	go_to(label(compiled_branch897))
}

func compiled_branch897() {
	assign(cont, label(after_call898))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch896() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call898))
}

func after_call898() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch894()
		return
	}
	go_to(label(true_branch893))
}

func true_branch893() {
	assign(proc, lookup_variable_value(constant("eval-sequence"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("begin-actions"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch899()
		return
	}
	go_to(label(compiled_branch900))
}

func compiled_branch900() {
	assign(cont, label(after_call901))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch899() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call901))
}

func after_call901() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch902()
		return
	}
	go_to(label(compiled_branch903))
}

func compiled_branch903() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch902() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call904() {
	go_to(label(false_branch894))
}

func false_branch894() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("cond?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch908()
		return
	}
	go_to(label(compiled_branch909))
}

func compiled_branch909() {
	assign(cont, label(after_call910))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch908() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call910))
}

func after_call910() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch906()
		return
	}
	go_to(label(true_branch905))
}

func true_branch905() {
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("cond->if"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch911()
		return
	}
	go_to(label(compiled_branch912))
}

func compiled_branch912() {
	assign(cont, label(after_call913))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch911() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call913))
}

func after_call913() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch914()
		return
	}
	go_to(label(compiled_branch915))
}

func compiled_branch915() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch914() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call916() {
	go_to(label(false_branch906))
}

func false_branch906() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("application?"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch920()
		return
	}
	go_to(label(compiled_branch921))
}

func compiled_branch921() {
	assign(cont, label(after_call922))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch920() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call922))
}

func after_call922() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch918()
		return
	}
	go_to(label(true_branch917))
}

func true_branch917() {
	assign(proc, lookup_variable_value(constant("apply"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("list-of-values"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("operands"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch929()
		return
	}
	go_to(label(compiled_branch930))
}

func compiled_branch930() {
	assign(cont, label(after_call931))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch929() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call931))
}

func after_call931() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch932()
		return
	}
	go_to(label(compiled_branch933))
}

func compiled_branch933() {
	assign(cont, label(after_call934))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch932() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call934))
}

func after_call934() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("env"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("operator"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch923()
		return
	}
	go_to(label(compiled_branch924))
}

func compiled_branch924() {
	assign(cont, label(after_call925))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch923() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call925))
}

func after_call925() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch926()
		return
	}
	go_to(label(compiled_branch927))
}

func compiled_branch927() {
	assign(cont, label(after_call928))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch926() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call928))
}

func after_call928() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch935()
		return
	}
	go_to(label(compiled_branch936))
}

func compiled_branch936() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch935() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call937() {
	go_to(label(false_branch918))
}

func false_branch918() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("exp"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("Unknown expression type -- EVAL"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch938()
		return
	}
	go_to(label(compiled_branch939))
}

func compiled_branch939() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch938() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call940() {
	go_to(label(after_if919))
}

func after_if919() {
	go_to(label(after_if907))
}

func after_if907() {
	go_to(label(after_if895))
}

func after_if895() {
	go_to(label(after_if880))
}

func after_if880() {
	go_to(label(after_if871))
}

func after_if871() {
	go_to(label(after_if862))
}

func after_if862() {
	go_to(label(after_if853))
}

func after_if853() {
	go_to(label(after_if844))
}

func after_if844() {
	go_to(label(after_if835))
}

func after_if835() {
	go_to(label(after_if829))
}

func after_if829() {
	go_to(label(after_lambda826))
}

func after_lambda826() {
	define_variable(constant("eval"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry941), reg(env)))
	go_to(label(after_lambda942))
}

func entry941() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(procedure arguments)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("primitive-procedure?"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch946()
		return
	}
	go_to(label(compiled_branch947))
}

func compiled_branch947() {
	assign(cont, label(after_call948))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch946() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call948))
}

func after_call948() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch944()
		return
	}
	go_to(label(true_branch943))
}

func true_branch943() {
	assign(proc, lookup_variable_value(constant("apply-primitive-procedure"), reg(env)))
	assign(val, lookup_variable_value(constant("arguments"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch949()
		return
	}
	go_to(label(compiled_branch950))
}

func compiled_branch950() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch949() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call951() {
	go_to(label(false_branch944))
}

func false_branch944() {
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("compound-procedure?"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch955()
		return
	}
	go_to(label(compiled_branch956))
}

func compiled_branch956() {
	assign(cont, label(after_call957))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch955() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call957))
}

func after_call957() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch953()
		return
	}
	go_to(label(true_branch952))
}

func true_branch952() {
	assign(proc, lookup_variable_value(constant("eval-sequence"), reg(env)))
	save(*cont)
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("extend-environment"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("procedure-environment"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch964()
		return
	}
	go_to(label(compiled_branch965))
}

func compiled_branch965() {
	assign(cont, label(after_call966))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch964() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call966))
}

func after_call966() {
	assign(argl, list(reg(val)))
	restore(env)
	assign(val, lookup_variable_value(constant("arguments"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("procedure-parameters"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch961()
		return
	}
	go_to(label(compiled_branch962))
}

func compiled_branch962() {
	assign(cont, label(after_call963))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch961() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call963))
}

func after_call963() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch967()
		return
	}
	go_to(label(compiled_branch968))
}

func compiled_branch968() {
	assign(cont, label(after_call969))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch967() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call969))
}

func after_call969() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("procedure-body"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch958()
		return
	}
	go_to(label(compiled_branch959))
}

func compiled_branch959() {
	assign(cont, label(after_call960))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch958() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call960))
}

func after_call960() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch970()
		return
	}
	go_to(label(compiled_branch971))
}

func compiled_branch971() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch970() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call972() {
	go_to(label(false_branch953))
}

func false_branch953() {
	assign(proc, lookup_variable_value(constant("error"), reg(env)))
	assign(val, lookup_variable_value(constant("procedure"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("Unknown procedure type -- APPLY"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch973()
		return
	}
	go_to(label(compiled_branch974))
}

func compiled_branch974() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch973() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call975() {
	go_to(label(after_if954))
}

func after_if954() {
	go_to(label(after_if945))
}

func after_if945() {
	go_to(label(after_lambda942))
}

func after_lambda942() {
	define_variable(constant("apply"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry976), reg(env)))
	go_to(label(after_lambda977))
}

func entry976() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("tagged-list?"), reg(env)))
	assign(val, constant("primitive"))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch978()
		return
	}
	go_to(label(compiled_branch979))
}

func compiled_branch979() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch978() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call980() {
	go_to(label(after_lambda977))
}

func after_lambda977() {
	define_variable(constant("primitive-procedure?"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry981), reg(env)))
	go_to(label(after_lambda982))
}

func entry981() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch983()
		return
	}
	go_to(label(compiled_branch984))
}

func compiled_branch984() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch983() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call985() {
	go_to(label(after_lambda982))
}

func after_lambda982() {
	define_variable(constant("primitive-implementation"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry986), reg(env)))
	go_to(label(after_lambda987))
}

func entry986() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc args)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("apply-in-underlying-scheme"), reg(env)))
	save(*cont)
	save(*proc)
	assign(val, lookup_variable_value(constant("args"), reg(env)))
	assign(argl, list(reg(val)))
	save(*argl)
	assign(proc, lookup_variable_value(constant("primitive-implementation"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch988()
		return
	}
	go_to(label(compiled_branch989))
}

func compiled_branch989() {
	assign(cont, label(after_call990))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch988() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call990))
}

func after_call990() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch991()
		return
	}
	go_to(label(compiled_branch992))
}

func compiled_branch992() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch991() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call993() {
	go_to(label(after_lambda987))
}

func after_lambda987() {
	define_variable(constant("apply-primitive-procedure"), reg(val), reg(env))
	assign(val, constant("ok"))
	save(*env)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	save(*proc)
	save(*env)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("*"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("*"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1048()
		return
	}
	go_to(label(compiled_branch1049))
}

func compiled_branch1049() {
	assign(cont, label(after_call1050))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1048() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1050))
}

func after_call1050() {
	assign(argl, list(reg(val)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("-"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("-"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1045()
		return
	}
	go_to(label(compiled_branch1046))
}

func compiled_branch1046() {
	assign(cont, label(after_call1047))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1045() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1047))
}

func after_call1047() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("+"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("+"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1042()
		return
	}
	go_to(label(compiled_branch1043))
}

func compiled_branch1043() {
	assign(cont, label(after_call1044))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1042() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1044))
}

func after_call1044() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant(">"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant(">"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1039()
		return
	}
	go_to(label(compiled_branch1040))
}

func compiled_branch1040() {
	assign(cont, label(after_call1041))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1039() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1041))
}

func after_call1041() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("<"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("<"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1036()
		return
	}
	go_to(label(compiled_branch1037))
}

func compiled_branch1037() {
	assign(cont, label(after_call1038))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1036() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1038))
}

func after_call1038() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("="), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("="))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1033()
		return
	}
	go_to(label(compiled_branch1034))
}

func compiled_branch1034() {
	assign(cont, label(after_call1035))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1033() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1035))
}

func after_call1035() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("pair?"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("pair?"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1030()
		return
	}
	go_to(label(compiled_branch1031))
}

func compiled_branch1031() {
	assign(cont, label(after_call1032))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1030() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1032))
}

func after_call1032() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("eq?"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("eq?"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1027()
		return
	}
	go_to(label(compiled_branch1028))
}

func compiled_branch1028() {
	assign(cont, label(after_call1029))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1027() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1029))
}

func after_call1029() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("append"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("append"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1024()
		return
	}
	go_to(label(compiled_branch1025))
}

func compiled_branch1025() {
	assign(cont, label(after_call1026))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1024() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1026))
}

func after_call1026() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("newline"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1021()
		return
	}
	go_to(label(compiled_branch1022))
}

func compiled_branch1022() {
	assign(cont, label(after_call1023))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1021() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1023))
}

func after_call1023() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("not"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("not"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1018()
		return
	}
	go_to(label(compiled_branch1019))
}

func compiled_branch1019() {
	assign(cont, label(after_call1020))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1018() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1020))
}

func after_call1020() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("list"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("list"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1015()
		return
	}
	go_to(label(compiled_branch1016))
}

func compiled_branch1016() {
	assign(cont, label(after_call1017))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1015() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1017))
}

func after_call1017() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("display"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("display"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1012()
		return
	}
	go_to(label(compiled_branch1013))
}

func compiled_branch1013() {
	assign(cont, label(after_call1014))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1012() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1014))
}

func after_call1014() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("null?"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("null?"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1009()
		return
	}
	go_to(label(compiled_branch1010))
}

func compiled_branch1010() {
	assign(cont, label(after_call1011))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1009() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1011))
}

func after_call1011() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("cons"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("cons"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1006()
		return
	}
	go_to(label(compiled_branch1007))
}

func compiled_branch1007() {
	assign(cont, label(after_call1008))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1006() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1008))
}

func after_call1008() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("cadr"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("cadr"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1003()
		return
	}
	go_to(label(compiled_branch1004))
}

func compiled_branch1004() {
	assign(cont, label(after_call1005))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1003() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1005))
}

func after_call1005() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("cddr"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("cddr"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1000()
		return
	}
	go_to(label(compiled_branch1001))
}

func compiled_branch1001() {
	assign(cont, label(after_call1002))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1000() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1002))
}

func after_call1002() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("cdr"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("cdr"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch997()
		return
	}
	go_to(label(compiled_branch998))
}

func compiled_branch998() {
	assign(cont, label(after_call999))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch997() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call999))
}

func after_call999() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	assign(val, lookup_variable_value(constant("car"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, constant("car"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch994()
		return
	}
	go_to(label(compiled_branch995))
}

func compiled_branch995() {
	assign(cont, label(after_call996))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch994() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call996))
}

func after_call996() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1051()
		return
	}
	go_to(label(compiled_branch1052))
}

func compiled_branch1052() {
	assign(cont, label(after_call1053))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1051() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1053))
}

func after_call1053() {
	restore(env)
	define_variable(constant("primitive-procedures"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1054), reg(env)))
	go_to(label(after_lambda1055))
}

func entry1054() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("()"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("map"), reg(env)))
	assign(val, lookup_variable_value(constant("primitive-procedures"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("car"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1056()
		return
	}
	go_to(label(compiled_branch1057))
}

func compiled_branch1057() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1056() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1058() {
	go_to(label(after_lambda1055))
}

func after_lambda1055() {
	define_variable(constant("primitive-procedure-names"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1059), reg(env)))
	go_to(label(after_lambda1060))
}

func entry1059() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("()"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("map"), reg(env)))
	assign(val, lookup_variable_value(constant("primitive-procedures"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, make_compiled_procedure(label(entry1061), reg(env)))
	go_to(label(after_lambda1062))
}

func entry1061() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(proc)"), reg(argl), reg(env)))
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("cadr"), reg(env)))
	assign(val, lookup_variable_value(constant("proc"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1063()
		return
	}
	go_to(label(compiled_branch1064))
}

func compiled_branch1064() {
	assign(cont, label(after_call1065))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1063() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1065))
}

func after_call1065() {
	assign(argl, list(reg(val)))
	assign(val, constant("primitive"))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1066()
		return
	}
	go_to(label(compiled_branch1067))
}

func compiled_branch1067() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1066() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1068() {
	go_to(label(after_lambda1062))
}

func after_lambda1062() {
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1069()
		return
	}
	go_to(label(compiled_branch1070))
}

func compiled_branch1070() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1069() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1071() {
	go_to(label(after_lambda1060))
}

func after_lambda1060() {
	define_variable(constant("primitive-procedure-objects"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1072), reg(env)))
	go_to(label(after_lambda1073))
}

func entry1072() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("()"), reg(argl), reg(env)))
	assign(proc, make_compiled_procedure(label(entry1074), reg(env)))
	go_to(label(after_lambda1075))
}

func entry1074() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(initial-env)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("define-variable!"), reg(env)))
	assign(val, lookup_variable_value(constant("initial-env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("true"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("true"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1076()
		return
	}
	go_to(label(compiled_branch1077))
}

func compiled_branch1077() {
	assign(cont, label(after_call1078))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1076() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1078))
}

func after_call1078() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("define-variable!"), reg(env)))
	assign(val, lookup_variable_value(constant("initial-env"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("false"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("false"))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1079()
		return
	}
	go_to(label(compiled_branch1080))
}

func compiled_branch1080() {
	assign(cont, label(after_call1081))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1079() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1081))
}

func after_call1081() {
	restore(env)
	restore(cont)
	assign(val, lookup_variable_value(constant("initial-env"), reg(env)))
	go_to(reg(cont))
}

func after_lambda1075() {
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("extend-environment"), reg(env)))
	save(*proc)
	assign(val, lookup_variable_value(constant("the-empty-environment"), reg(env)))
	assign(argl, list(reg(val)))
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("primitive-procedure-objects"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1085()
		return
	}
	go_to(label(compiled_branch1086))
}

func compiled_branch1086() {
	assign(cont, label(after_call1087))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1085() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1087))
}

func after_call1087() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("primitive-procedure-names"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1082()
		return
	}
	go_to(label(compiled_branch1083))
}

func compiled_branch1083() {
	assign(cont, label(after_call1084))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1082() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1084))
}

func after_call1084() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1088()
		return
	}
	go_to(label(compiled_branch1089))
}

func compiled_branch1089() {
	assign(cont, label(after_call1090))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1088() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1090))
}

func after_call1090() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1091()
		return
	}
	go_to(label(compiled_branch1092))
}

func compiled_branch1092() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1091() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1093() {
	go_to(label(after_lambda1073))
}

func after_lambda1073() {
	define_variable(constant("setup-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	save(*env)
	assign(proc, lookup_variable_value(constant("setup-environment"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1094()
		return
	}
	go_to(label(compiled_branch1095))
}

func compiled_branch1095() {
	assign(cont, label(after_call1096))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1094() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1096))
}

func after_call1096() {
	restore(env)
	define_variable(constant("the-global-environment"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, constant(";;; M_Eval input:"))
	define_variable(constant("input-prompt"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, constant(";;; M_Eval value:"))
	define_variable(constant("output-prompt"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1097), reg(env)))
	go_to(label(after_lambda1098))
}

func entry1097() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(string)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1099()
		return
	}
	go_to(label(compiled_branch1100))
}

func compiled_branch1100() {
	assign(cont, label(after_call1101))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1099() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1101))
}

func after_call1101() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1102()
		return
	}
	go_to(label(compiled_branch1103))
}

func compiled_branch1103() {
	assign(cont, label(after_call1104))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1102() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1104))
}

func after_call1104() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("display"), reg(env)))
	assign(val, lookup_variable_value(constant("string"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1105()
		return
	}
	go_to(label(compiled_branch1106))
}

func compiled_branch1106() {
	assign(cont, label(after_call1107))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1105() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1107))
}

func after_call1107() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1108()
		return
	}
	go_to(label(compiled_branch1109))
}

func compiled_branch1109() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1108() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1110() {
	go_to(label(after_lambda1098))
}

func after_lambda1098() {
	define_variable(constant("prompt-for-input"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1111), reg(env)))
	go_to(label(after_lambda1112))
}

func entry1111() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(string)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1113()
		return
	}
	go_to(label(compiled_branch1114))
}

func compiled_branch1114() {
	assign(cont, label(after_call1115))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1113() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1115))
}

func after_call1115() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("display"), reg(env)))
	assign(val, lookup_variable_value(constant("string"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1116()
		return
	}
	go_to(label(compiled_branch1117))
}

func compiled_branch1117() {
	assign(cont, label(after_call1118))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1116() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1118))
}

func after_call1118() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("newline"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1119()
		return
	}
	go_to(label(compiled_branch1120))
}

func compiled_branch1120() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1119() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1121() {
	go_to(label(after_lambda1112))
}

func after_lambda1112() {
	define_variable(constant("announce-output"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1122), reg(env)))
	go_to(label(after_lambda1123))
}

func entry1122() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(object)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("compound-procedure?"), reg(env)))
	assign(val, lookup_variable_value(constant("object"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1127()
		return
	}
	go_to(label(compiled_branch1128))
}

func compiled_branch1128() {
	assign(cont, label(after_call1129))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1127() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1129))
}

func after_call1129() {
	restore(env)
	restore(cont)
	if test(is_false(reg(val))) {
		false_branch1125()
		return
	}
	go_to(label(true_branch1124))
}

func true_branch1124() {
	assign(proc, lookup_variable_value(constant("display"), reg(env)))
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("list"), reg(env)))
	save(*proc)
	assign(val, constant("<procedure_env>"))
	assign(argl, list(reg(val)))
	save(*env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("procedure-body"), reg(env)))
	assign(val, lookup_variable_value(constant("object"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1133()
		return
	}
	go_to(label(compiled_branch1134))
}

func compiled_branch1134() {
	assign(cont, label(after_call1135))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1133() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1135))
}

func after_call1135() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	restore(env)
	save(*argl)
	assign(proc, lookup_variable_value(constant("procedure-parameters"), reg(env)))
	assign(val, lookup_variable_value(constant("object"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1130()
		return
	}
	go_to(label(compiled_branch1131))
}

func compiled_branch1131() {
	assign(cont, label(after_call1132))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1130() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1132))
}

func after_call1132() {
	restore(argl)
	assign(argl, cons(reg(val), reg(argl)))
	assign(val, constant("compound_procedure"))
	assign(argl, cons(reg(val), reg(argl)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1136()
		return
	}
	go_to(label(compiled_branch1137))
}

func compiled_branch1137() {
	assign(cont, label(after_call1138))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1136() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1138))
}

func after_call1138() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1139()
		return
	}
	go_to(label(compiled_branch1140))
}

func compiled_branch1140() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1139() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1141() {
	go_to(label(false_branch1125))
}

func false_branch1125() {
	assign(proc, lookup_variable_value(constant("display"), reg(env)))
	assign(val, lookup_variable_value(constant("object"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1142()
		return
	}
	go_to(label(compiled_branch1143))
}

func compiled_branch1143() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1142() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1144() {
	go_to(label(after_if1126))
}

func after_if1126() {
	go_to(label(after_lambda1123))
}

func after_lambda1123() {
	define_variable(constant("user-print"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(val, make_compiled_procedure(label(entry1145), reg(env)))
	go_to(label(after_lambda1146))
}

func entry1145() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("()"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("prompt-for-input"), reg(env)))
	assign(val, lookup_variable_value(constant("input-prompt"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1147()
		return
	}
	go_to(label(compiled_branch1148))
}

func compiled_branch1148() {
	assign(cont, label(after_call1149))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1147() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1149))
}

func after_call1149() {
	restore(env)
	restore(cont)
	save(*cont)
	save(*env)
	assign(proc, make_compiled_procedure(label(entry1150), reg(env)))
	go_to(label(after_lambda1151))
}

func entry1150() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(input)"), reg(argl), reg(env)))
	assign(proc, make_compiled_procedure(label(entry1152), reg(env)))
	go_to(label(after_lambda1153))
}

func entry1152() {
	assign(env, compiled_procedure_env(reg(proc)))
	assign(env, extend_environment(constant("(output)"), reg(argl), reg(env)))
	save(*cont)
	save(*env)
	assign(proc, lookup_variable_value(constant("announce-output"), reg(env)))
	assign(val, lookup_variable_value(constant("output-prompt"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1154()
		return
	}
	go_to(label(compiled_branch1155))
}

func compiled_branch1155() {
	assign(cont, label(after_call1156))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1154() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1156))
}

func after_call1156() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("user-print"), reg(env)))
	assign(val, lookup_variable_value(constant("output"), reg(env)))
	assign(argl, list(reg(val)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1157()
		return
	}
	go_to(label(compiled_branch1158))
}

func compiled_branch1158() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1157() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1159() {
	go_to(label(after_lambda1153))
}

func after_lambda1153() {
	save(*cont)
	save(*proc)
	assign(proc, lookup_variable_value(constant("eval"), reg(env)))
	assign(val, lookup_variable_value(constant("the-global-environment"), reg(env)))
	assign(argl, list(reg(val)))
	assign(val, lookup_variable_value(constant("input"), reg(env)))
	assign(argl, cons(reg(val), reg(argl)))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1160()
		return
	}
	go_to(label(compiled_branch1161))
}

func compiled_branch1161() {
	assign(cont, label(after_call1162))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1160() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1162))
}

func after_call1162() {
	assign(argl, list(reg(val)))
	restore(proc)
	restore(cont)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1163()
		return
	}
	go_to(label(compiled_branch1164))
}

func compiled_branch1164() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1163() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1165() {
	go_to(label(after_lambda1151))
}

func after_lambda1151() {
	save(*proc)
	assign(proc, lookup_variable_value(constant("read"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1166()
		return
	}
	go_to(label(compiled_branch1167))
}

func compiled_branch1167() {
	assign(cont, label(after_call1168))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1166() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1168))
}

func after_call1168() {
	assign(argl, list(reg(val)))
	restore(proc)
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1169()
		return
	}
	go_to(label(compiled_branch1170))
}

func compiled_branch1170() {
	assign(cont, label(after_call1171))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1169() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1171))
}

func after_call1171() {
	restore(env)
	restore(cont)
	assign(proc, lookup_variable_value(constant("driver-loop"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1172()
		return
	}
	go_to(label(compiled_branch1173))
}

func compiled_branch1173() {
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1172() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(reg(cont))
}

func after_call1174() {
	go_to(label(after_lambda1146))
}

func after_lambda1146() {
	define_variable(constant("driver-loop"), reg(val), reg(env))
	assign(val, constant("ok"))
	assign(proc, lookup_variable_value(constant("driver-loop"), reg(env)))
	assign(argl, constant("()"))
	if test(is_primitive_procedure(reg(proc))) {
		primitive_branch1175()
		return
	}
	go_to(label(compiled_branch1176))
}

func compiled_branch1176() {
	assign(cont, label(after_call1177))
	assign(val, compiled_procedure_entry(reg(proc)))
	go_to(reg(val))
}

func primitive_branch1175() {
	assign(val, apply_primitive_procedure(reg(proc), reg(argl)))
	go_to(label(after_call1177))
}

func after_call1177() {
}
