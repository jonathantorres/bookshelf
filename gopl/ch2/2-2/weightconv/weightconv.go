package weightconv

import "fmt"

type Pound float64
type Kilogram float64

func PToKilo(pounds Pound) Kilogram {
	return Kilogram(pounds * 0.4535924)
}

func KToPound(kilos Kilogram) Pound {
	return Pound(kilos * 2.204623)
}

func (p Pound) String() string {
	return fmt.Sprintf("%glb.", p)
}

func (k Kilogram) String() string {
	return fmt.Sprintf("%gkg.", k)
}
