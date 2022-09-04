#[derive(Debug)]
struct Meters(u8);

fn add_distances(d1: Meters, d2: Meters) -> Meters {
    Meters(d1.0 + d2.0)
}

fn main() {
    let distance1:Meters = Meters(3);
    let distance2 = Meters(7);

    let distance3 = add_distances(distance1, distance2);
    println!("{:?}", distance3);
}
