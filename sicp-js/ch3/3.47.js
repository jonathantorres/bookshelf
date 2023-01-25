import { display, list, head, set_head, error, display_list } from 'sicp';

// make a semaphore using test_and_set
const s = make_semaphore(1);
s("acquire");
s("release");

// make a semaphore using a mutex
const sem = make_semaphore_mu(1);
sem("acquire");
sem("release");

function make_semaphore(n) {
    const cell = list(0);
    function the_semaphore(m) {
        return m === "acquire"
               ? test_and_set_sem(cell, n)
                 ? the_semaphore("acquire") // retry
                 : true
               : m === "release"
               ? release(cell)
               : error(m, "unknown request -- semaphore");
    }
    return the_semaphore;
}

function make_semaphore_mu(n) {
    const mutex = make_mutex();
    function the_semaphore(m) {
        if (m === "acquire") {
           mutex(m);
           if (n > 0) {
                n = n-1;
                mutex("release");
                return true;
           } else {
                mutex("release");
                the_semaphore("acquire"); // retry
           }
        } else if (m === "release") {
            mutex("acquire");
            n = n+1;
            mutex("release");
        } else {
            error(m, "unknown request -- semaphore");
        }
    }
    return the_semaphore;
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

function test_and_set_sem(cell, n) {
    if (head(cell) < n) {
        set_head(cell, head(cell) + 1);
        return false;
    } else {
        return true;
    }
}

function release(cell) {
    if (head(cell) > 0) {
        set_head(cell, head(cell) - 1);
    }
}

function clear(cell) {
    set_head(cell, false);
}

