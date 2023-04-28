function lexical_address_lookup(env, address) {
    let frame = list_ref(env, address_frame(address));
    let value = list_ref(frame_values(frame), address_offset(address));

    if (equal(value, "*unassigned*")) {
        return error("the variable is unassigned", address);
    }

    return value;
}

function lexical_address_assign(env, address, value) {
    let frame = address_frame(address);
    let offset = address_offset(address);

    function set_value(f, pos) {
        if (f === 0) {
            set_head(f, value);
            return;
        }
        set_value(tail(f), pos-1);
    }

    set_value(frame, offset);
}

function lexical_address(frame, offset) {
    return pair(frame, offset);
}

function address_frame(address) {
    return head(address);
}

function address_offset(address) {
    return tail(address);
}
