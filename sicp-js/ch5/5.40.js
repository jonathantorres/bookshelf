// changes on preserving
function preserving(regs, seq1, seq2) {
    if (is_null(regs)) {
        return append_instruction_sequences(seq1, seq2);
    } else {
        const first_reg = head(regs);
        return preserving(tail(regs),
                     make_instruction_sequence(
                         list_union(list(first_reg), registers_needed(seq1)),
                         list_difference(registers_modified(seq1), list(first_reg)),
                         append(list(save(first_reg)),
                                append(instructions(seq1),
                                       list(restore(first_reg))))),
                     seq2);
    }
}
