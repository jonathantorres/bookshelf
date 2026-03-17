package bank

import (
	"testing"
)

func TestDeposit(t *testing.T) {
	b := Balance()
	if b != 0 {
		t.Fatalf("balance should be %d, got %d\n", 0, b)
	}
	Deposit(100)
	b = Balance()
	if b != 100 {
		t.Fatalf("balance should be %d, got %d\n", 100, b)
	}
}

func TestWithdraw(t *testing.T) {
	ok := Withdraw(50)
	if !ok {
		t.Fatalf("withdraw should be ok\n")
	}
	if b := Balance(); b != 50 {
		t.Fatalf("new balance should be %d, but got %d\n", 50, b)
	}
}

func TestWithdrawInsufficient(t *testing.T) {
	ok := Withdraw(51)
	if ok {
		t.Fatalf("withdraw should not be ok\n")
	}
	if b := Balance(); b != 50 {
		t.Fatalf("balance should be %d, but got %d\n", 50, b)
	}
}
