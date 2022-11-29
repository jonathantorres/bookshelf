import { display, display_list, list, head, tail, is_null, pair } from 'sicp';

const n = list(1,2,3,4,5);

for_each(x => display(x), n);

function for_each(f, items) {
    if (is_null(items)) {
        return;
    }

    f(head(items));
    for_each(f, tail(items));
}
