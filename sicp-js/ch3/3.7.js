import { display, error } from 'sicp';

const acc = make_account(100, "secret");
const acc_alias = make_joint(acc, "secret", "aliassecret");

display(acc("secret", "withdraw")(60));
display(acc_alias("aliassecret", "withdraw")(10));

display(acc("aliassecret", "withdraw")(10));
display(acc_alias("secret", "withdraw")(10));

function make_joint(orig_account, pass, newpass) {
    // make $0 deposit, to validate the joint account
    if (orig_account(pass, "deposit")(0) === "Incorrect password") {
        return error("cannot create joint account, Incorrect password");
    }
    return (p, m) => {
        if (newpass !== p) {
            return () => {
                return "Incorrect password";
            }
        }
        return orig_account(pass, m);
    };
}

function make_account(balance, acc_pass) {
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
        if (acc_pass !== p) {
            return () => {
                return "Incorrect password";
            }
        }
        return m === "withdraw"
               ? withdraw
               : m === "deposit"
               ? deposit
               : error(m, "unknown request -- make_account");
    }
    return dispatch;
}
