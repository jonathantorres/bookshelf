import {
    display, list, head, tail, set_head, set_tail, error, display_list
} from 'sicp';

// used to generate an account number
let last_acc_number = 0;
const acc_number_lock = make_mutex();

const acc1 = make_account(100);
const acc2 = make_account(50);

display(acc1("balance"), "acc1: ");
display(acc2("balance"), "acc2: ");

serialized_exchange(acc1, acc2);

display(acc1("balance"), "acc1: ");
display(acc2("balance"), "acc2: ");

function serialized_exchange(account1, account2) {
    let serializer1 = account1("serializer");
    let serializer2 = account2("serializer");
    let exchanger = null;

    if (account1("number") < account2("number")) {
        exchanger = serializer1(serializer2(exchange));
    } else {
        exchanger = serializer2(serializer1(exchange));
    }

    exchanger(account1, account2);
}

function generate_acc_number() {
    acc_number_lock("acquire");
    let number = last_acc_number;
    last_acc_number = last_acc_number+1;
    acc_number_lock("release");

    return number;
}

function make_account(balance) {
    let number = generate_acc_number();
    let serializer = make_serializer();

    function withdraw(amount) {
        if (balance >= amount) {
            balance = balance-amount;
            return balance;
        }
        return "Insufficient funds";
    }

    function deposit(amount) {
        balance = balance+amount;
        return balance;
    }

    function dispatch(m) {
       if (m === "withdraw")  {
           return withdraw;
       } else if (m === "deposit") {
           return deposit;
       } else if (m === "balance") {
           return balance;
       } else if (m === "serializer") {
           return serializer;
       } else if (m === "number") {
           return number;
       } else {
           error("Unknown request - make_account");
       }
    }

    return dispatch;
}

function exchange(account1, account2) {
    const difference = account1("balance") - account2("balance");
    account1("withdraw")(difference);
    account2("deposit")(difference);
}

function make_serializer() {
    const mutex = make_mutex();
    return f => {
        function serialized_f(...args) {
           mutex("acquire");
           const val = f(...args);
           mutex("release");
           return val;
        }
        return serialized_f;
    };
}

function make_mutex() {
    const cell = list(false);
    function the_mutex(m) {
        return m === "acquire"
               ? test_and_set(cell)
                 ? the_mutex("acquire") // retry
                 : true
               : m === "release"
               ? clear(cell)
               : error(m, "unknown request -- mutex");
    }
    return the_mutex;
}

function test_and_set(cell) {
    if (head(cell)) {
        return true;
    } else {
        set_head(cell, true);
        return false;
    }
}

function clear(cell) {
    set_head(cell, false);
}

