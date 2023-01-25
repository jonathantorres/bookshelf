import {
    display, is_pair, is_null, list, pair, head, equal, is_undefined,
    tail, set_head, set_tail, error, member, append, display_list
} from 'sicp';

const t = make_table();
const put = t("insert");
const get = t("lookup");
const print = t("print");

put(list("foo", "bar"), 100);
put(list("foo", "baz"), 200);
print();

display(get(list("foo", "bar")));
display(get(list("foo", "baz")));
display(get(list("foo", "paz")));
display(get(list("one", "two", "three")));

function make_table() {
    const local_table = list("*table*");
    function lookup(table_keys) {
        function loop(keys, cur_table) {
            const subtable = assoc(head(keys), tail(cur_table));
            if (is_undefined(subtable)) {
                return undefined;
            } else {
                if (!is_pair(tail(subtable))) {
                    return tail(subtable);
                } else {
                    return loop(tail(keys), subtable);
                }
            }
        }
        return loop(table_keys, local_table);
    }

    function insert(table_keys, value) {
        function loop(keys, cur_table) {
            const subtable = assoc(head(keys), tail(cur_table));
            if (is_undefined(subtable)) {
                if (is_null(tail(keys))) {
                    set_tail(cur_table, pair(pair(head(keys), value), null), tail(cur_table));
                } else {
                    const next_table = pair(pair(head(keys), null), tail(cur_table));
                    set_tail(cur_table, next_table);
                    loop(tail(keys), head(next_table));
                }
            } else {
                if (!is_pair(tail(subtable))) {
                    set_tail(subtable, value);
                } else {
                    loop(tail(keys), tail(subtable));
                }
            }
        }
        loop(table_keys, local_table);
    }

    function assoc(key, records) {
        return is_null(records)
               ? undefined
               : equal(key, head(head(records)))
               ? head(records)
               : assoc(key, tail(records));
    }

    function print() {
        display(local_table);
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
