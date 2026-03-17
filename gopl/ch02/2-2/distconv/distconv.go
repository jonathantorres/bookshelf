package distconv

import "fmt"

type Feet float64
type Meter float64

func FToMeters(feet Feet) Meter {
	return Meter(feet * 0.3048)
}

func MToFeet(meters Meter) Feet {
	return Feet(meters * 3.28084)
}

func (m Meter) String() string {
	return fmt.Sprintf("%gm", m)
}

func (f Feet) String() string {
	return fmt.Sprintf("%gft.", f)
}
