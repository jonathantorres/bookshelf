#[derive(Debug)]
pub struct Car {
}

impl Car {
    pub fn new() -> Car {
        Car{}
    }

    pub fn start(&self) {
        println!("Car is starting...");
    }

    pub fn reverse(&self) {
        println!("Car is doing a reverse!");
    }

    pub fn run(&self) {
        println!("Car is running!!!");
    }
}

#[derive(Debug)]
pub struct Truck {

}

impl Truck {
    pub fn new() -> Truck {
        Truck{}
    }

    pub fn start(&self) {
        println!("Truck is starting and very heavy...");
    }

    pub fn reverse(&self) {
        println!("Truck is doing a reverse and beeping");
    }

    pub fn run(&self) {
        println!("Truck is running and making a lot of noise and smoke!");
    }
}

trait Vehicle {
    fn start(&self);
    fn reverse(&self);
    fn run(&self);
}
