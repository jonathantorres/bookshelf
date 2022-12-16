import {
    display, display_list, list, head, map, length,
    tail, is_null, pair, is_pair, accumulate, append, filter
} from 'sicp';

const empty_board = null;

display_list(length(queens(4)));

// a solution, looks like this:
// list(pair(2,1), pair(4,2), pair(1,3), pair(3,4))

function queens(board_size) {
    function queen_cols(k) {
        if (k === 0) {
            return list(empty_board);
        }
        return filter(positions => is_safe(k, positions),
                    flatmap(rest_of_queens => {
                        return map(new_row => {
                            return adjoin_position(new_row, k, rest_of_queens);
                        }, enumerate_interval(1, board_size));
                    }, queen_cols(k-1)));
    }
    return queen_cols(board_size);
}

function is_safe(k, positions) {
    display_list(k, "k:");
    display_list(positions, "pos:");
    return true;
}

function adjoin_position(new_row, k, rest_of_queens) {
    return pair(pair(new_row, k), rest_of_queens);
}

function flatmap(f, seq) {
    return accumulate(append, null, map(f, seq));
}

function enumerate_interval(low, high) {
    return low > high
           ? null
           : pair(low, enumerate_interval(low + 1, high));
}
