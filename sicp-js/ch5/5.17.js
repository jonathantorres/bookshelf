// changes on the make_register function
function make_register(name) {
    let contents = "*unassigned*";
    let trace = false;
    function dispatch(message) {
        return message === "get"
               ? contents
               : message === "set"
               ? value => {
                   if (trace) {
                       display(name + " " + contents + " " + value);
                   }
                   contents = value;
               }
               : message === "trace_on"
               ? trace = true
               : message === "trace_off"
               ? trace = false
               : error(message, "unknown request -- make_register");
    }
    return dispatch;
}
