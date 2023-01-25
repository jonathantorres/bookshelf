import { display, error } from 'sicp';

const acc = make_account(100, "secret");

display(acc("secret", "withdraw")(60));
display(acc("something", "withdraw")(40));

function make_account(balance, acc_pass) {
    let pass = "";
    function withdraw(amount) {
        if (acc_pass !== pass) {
            return "Incorrect password";
        }
        if (balance >= amount) {
            balance = balance - amount;
            return balance;
        } else {
            return "Insufficient funds";
        }
    }
    function deposit(amount) {
        if (acc_pass !== pass) {
            return "Incorrect password";
        }
        balance = balance + amount;
        return balance;
    }
    function dispatch(p, m) {
        pass = p;
        return m === "withdraw"
               ? withdraw
               : m === "deposit"
               ? deposit
               : error(m, "unknown request -- make_account");
    }
    return dispatch;
}
