import { display, error } from 'sicp';

const acc = make_account(100, "secret");

display(acc("secret", "withdraw")(60));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));
display(acc("something", "withdraw")(40));

function make_account(balance, password) {
    let incorrect_count = 0;
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
    function call_the_cops() {
        return "calling the cops now";
    }
    function dispatch(p, m) {
        if (password !== p) {
            return x => {
                incorrect_count = incorrect_count + 1;
                if (incorrect_count > 7) {
                    return call_the_cops();
                }
                return "Incorrect password";
            };
        } else {
            return m === "withdraw"
               ? withdraw
               : m === "deposit"
               ? deposit
               : error(m, "unknown request -- make_account");
        }
    }
    return dispatch;
}
