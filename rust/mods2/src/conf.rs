pub struct Conf {
    path: i32,
}

impl Conf {
    pub fn new() -> Self {
        println!("Creating a new conf");
        Conf { path: 33 }
    }

    pub fn load(&self) {
        println!("The configuration file has been loaded");
    }
}
