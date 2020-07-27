package main

// Exercise 9.1

type Withdrawal struct {
	amount int
	success chan bool
}

var deposits = make(chan int) // send amount to deposit
var balances = make(chan int) // receive balance
var withdrawals = make(chan Withdrawal) // withdraw requests

func Deposit(amount int) { deposits <- amount }
func Balance() int       { return <-balances }

func main() {
	go teller() // start the monitor goroutine
}

func Withdraw(amount int) bool {
	ch := make(chan bool)
	withdrawals <- Withdrawal{
		amount: amount,
		success: ch,
	}
	return <-ch
}

func teller() {
	var balance int // balance is confined to teller goroutine
	for {
		select {
		case amount := <-deposits:
			balance += amount
		case w := <-withdrawals:
			if w.amount > balance {
				w.success <- false
			} else {
				balance -= w.amount
				w.success <- true
			}
		case balances <- balance:
		}
	}
}
