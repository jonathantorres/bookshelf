import { display, error } from 'sicp';

const acc = make_account(100, "secret");

display(acc("secret", "withdraw")(60));
display(acc("something", "withdraw")(40));

function make_account(balance, password) {
    function withdraw(amount) {
        if (balance >= amount) {
            balance = balance - amount;
            return balance;
        } else {
            return "Insufficient funds";
        }
    }
    function deposit(amount) {
        balance = balance + amount;
        return balance;
    }
    function dispatch(p, m) {
        if (p === password) {
            return m === "withdraw"
               ? withdraw
               : m === "deposit"
               ? deposit
               : error(m, "unknown request -- make_account");
        } else {
            return x => "Incorrect Password";
        }
    }
    return dispatch;
}
