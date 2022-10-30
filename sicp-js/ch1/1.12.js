import { display } from 'sicp';

display(pascal(4, 2));
display(pascal(25, 12));
// display_triangle(25);

function pascal(row, col) {
    if (row == col || col == 0) {
        return 1;
    }
    return pascal(row-1, col-1) + pascal(row-1, col);
}

function display_triangle(h) {
    for (var i = 0; i < h; i++) {
        var row = "";
        for (var j = 0; j <= i; j++) {
            row += pascal(i, j) + " ";
        }
        console.log(row);
    }
}
