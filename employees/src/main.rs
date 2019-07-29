use std::io::{self};
use std::collections::HashMap;

fn main() {
    println!("Employee Directory");
    let mut _directory:HashMap<String, Vec<String>> = HashMap::new();

    loop {
        println!("Enter employee data: ");
        let mut emp_data = String::new();
        match io::stdin().read_line(&mut emp_data) {
            Err(..) => {},
            Ok(_) => {},
        };
        println!("{}", emp_data);
        break;
    }
}
