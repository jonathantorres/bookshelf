package eval

func (v Var) String() string {
	return Format(v)
}

func (l Literal) String() string {
	return Format(l)
}

func (u unary) String() string {
	return Format(u)
}

func (b binary) String() string {
	return Format(b)
}

func (c call) String() string {
	return Format(c)
}

func (m Min) String() string {
	return Format(m)
}
