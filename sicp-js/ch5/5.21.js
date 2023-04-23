const append = make_machine(
    list("x", "y", "val", "continue", "temp"),
    list(
        list("is_null", is_null),
        list("pair", pair),
        list("head", head),
        list("tail", tail),
    ),
    list(
        "start",
            assign("x", register("x")),
            assign("y", register("y")),
            assign("continue", label("done")),
            save("continue"),
        "append",
            test(list(op("is_null"), reg("x"))),
            branch(label("null")),
            assign("temp", list(op("head"), register("x"))),
            save("temp"),
            assign("continue", label("after")),
            save("continue"),
            assign("x", list(op("tail"), register("x"))),
            go_to(label("append")),
        "after",
            restore("x"),
            assign("val", list(op("pair"), register("x"), register("val"))),
            restore("continue"),
            go_to(register("continue")),
        "null",
            assign("val", register("y")),
            restore("continue"),
            go_to(register("continue")),
        "done"
    )
);

const append_mutator = make_machine(
    list("x", "y", "val", "temp"),
    list(
        list("is_null", is_null),
        list("set_tail", set_tail),
        list("tail", tail),
    ),
    list(
        "start",
            assign("x", register("x")),
            assign("y", register("y")),
            assign("temp", register("x")),
            go_to(label("pair")),
        "append",
            assign("temp", list(op("set_tail"), register("temp"), register("y"))),
            go_to(label("done")),
        "pair",
            assign("temp", list(op("tail"), register("temp"))),
            test(list(op("is_null"), reg("temp"))),
            branch(label("null")),
            assign("temp", list(op("tail"), register("temp"))),
        "null",
            go_to(label("append")),
        "done"
    )
);
