import { display, display_list, list, head, tail, is_null, pair } from 'sicp';

const us_coins = list(50, 25, 10, 5, 1);
const uk_coins = list(100, 50, 20, 10, 5, 2, 1);

display(cc(100, us_coins)); // 292
display(cc(100, uk_coins)); // 4563

function cc(amount, coin_values) {
    return amount === 0
           ? 1
           : amount < 0 || no_more(coin_values)
           ? 0
           : cc(amount, except_first_denomination(coin_values)) +
             cc(amount - first_denomination(coin_values), coin_values);
}

function except_first_denomination(coin_values) {
    return tail(coin_values);
}

function first_denomination(coin_values) {
    return head(coin_values);
}

function no_more(coin_values) {
    return is_null(coin_values);
}

