extern crate car;

use car::{Car,Truck};

fn main() {
    let small_car = Car::new();
    small_car.start();
    small_car.run();

    let big_truck = Truck::new();
    big_truck.start();
    big_truck.reverse();
    big_truck.run();
}
