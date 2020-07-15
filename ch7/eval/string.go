package eval

// Exercise 7.13
// Exercise 7.14

import (
	"fmt"
)

func (v Var) String() string {
	return string(v)
}

func (l literal) String() string {
	return fmt.Sprintf("%.2f", l)
}

func (u unary) String() string {
	return string(u.op) + u.x.String()
}

func (b binary) String() string {
	return b.x.String() + string(b.op) + b.y.String()
}

func (c call) String() string {
	callStr := ""+c.fn+"("
	for i, expr := range c.args {
		if i != 0 {
			callStr += ", "
		}
		callStr += expr.String()
	}
	callStr += ")"
	return callStr
}

func (m min) String() string {
	return "min("+m.x.String()+","+m.y.String()+")"
}
