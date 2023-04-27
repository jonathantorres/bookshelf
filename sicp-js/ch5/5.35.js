// TODO: changes on append_return_undefined
function append_return_undefined(body) {
    return list("sequence", list(body,
             list("return_statement",
                  list("literal", undefined))));
}
