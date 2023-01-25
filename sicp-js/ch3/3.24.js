import {
    display, is_pair, is_null, list, pair, head, equal, is_undefined,
    tail, set_head, set_tail, error, member, append, display_list
} from 'sicp';

const t = make_table(equal);
const put = t("insert");
const get = t("lookup");
const print_table = t("print");

put("foo", "bar", 100);
put("foo", "baz", 200);
print_table();

display(get("foo", "bar"));
display(get("foo", "baz"));

function make_table(same_key) {
    const local_table = list("*table*");
    function lookup(key_1, key_2) {
        const subtable = assoc(key_1, tail(local_table));
        if (is_undefined(subtable)) {
            return undefined;
        } else {
            const record = assoc(key_2, tail(subtable));
            return is_undefined(record)
                   ? undefined
                   : tail(record);
        }
    }

    function insert(key_1, key_2, value) {
        const subtable = assoc(key_1, tail(local_table));
        if (is_undefined(subtable)) {
            set_tail(local_table,
                     pair(list(key_1, pair(key_2, value)),
                          tail(local_table)));
        } else {
            const record = assoc(key_2, tail(subtable));
            if (is_undefined(record)) {
                set_tail(subtable,
                         pair(pair(key_2, value), tail(subtable)));
            } else {
                set_tail(record, value);
            }
        }
    }

    function print() {
        display(local_table);
    }

    function assoc(key, records) {
        return is_null(records)
               ? undefined
               : same_key(key, head(head(records)))
               ? head(records)
               : assoc(key, tail(records));
    }

    function dispatch(m) {
        return m === "lookup"
               ? lookup
               : m === "insert"
               ? insert
               : m === "print"
               ? print
               : error(m, "unknown operation -- table");
    }

    return dispatch;
}
