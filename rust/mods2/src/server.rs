use ftr;
use session::Session;

pub struct Server {
    foo: i32,
    bar: i32,
}

impl Server {
    pub fn new() -> Self {
        println!("Creating a new server!");
        do_it();
        ftr::something_general();
        Server { foo: 100, bar: 200 }
    }

    pub fn start(&self) {
        println!("Starting the server!");
    }
}

fn do_it() {
    let s = Session::new();
    println!("creating new session {:?}", s);
}

#[cfg(test)]
mod tests {
    #[test]
    fn run_test() {}
}
