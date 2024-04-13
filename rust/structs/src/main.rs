struct Person {
    age:u32,
    first_name: String,
    last_name: String,
}

impl Person {
    const ARMS: u8 = 2;

    fn talk(&mut self) {
        println!("I am: {} {} {}", self.age, self.first_name, self.last_name);
        self.age = self.age + 10;
        println!("I am: {} {} {}", self.age, self.first_name, self.last_name);
    }

    fn walk() {
        println!("Walking...");
    }
}

fn main() {
    let mut john = Person{
        age:34,
        first_name:"Jonathan".to_string(),
        last_name:"Torres".to_string()
    };
    john.talk();
    Person::walk();
    println!("{}", Person::ARMS);
}
