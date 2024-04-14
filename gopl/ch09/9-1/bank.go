package bank

var deposits = make(chan int)     // send amount to deposit
var balances = make(chan int)     // receive balance
var withdrawals = make(chan slip) // send slip with amount to withdraw

type slip struct {
	amount int
	ok     chan bool
}

func init() {
	go teller() // start the monitor goroutine
}

func Deposit(amount int) { deposits <- amount }
func Balance() int       { return <-balances }

func Withdraw(amount int) bool {
	s := slip{amount, make(chan bool)}
	withdrawals <- s
	return <-s.ok
}

func teller() {
	var balance int // balance is confined to teller goroutine
	for {
		select {
		case amount := <-deposits:
			balance += amount
		case balances <- balance:
		case s := <-withdrawals:
			if balance >= s.amount {
				balance -= s.amount
				s.ok <- true
			} else {
				s.ok <- false
			}
		}
	}
}
