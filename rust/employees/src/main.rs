use std::io::{self};
use std::collections::HashMap;

fn main() {
    println!("Employee Directory");
    let mut directory:HashMap<String, Vec<String>> = HashMap::new();

    loop {
        println!("Enter employee data (type q to finish): ");
        let mut emp_data = String::new();
        match io::stdin().read_line(&mut emp_data) {
            Err(_) => {
                println!("There was an error with your input, please try again");
                continue;
            },
            Ok(_) => {},
        };

        if emp_data.trim() == "q" {
            break;
        }

        let data_parts:Vec<&str> = emp_data.split(' ').collect();
        let emp_name = match data_parts.get(1) {
            Some(name) => name,
            None => {
                println!("Using wrong format, please try again");
                continue;
            }
        };
        let emp_dept = match data_parts.get(3) {
            Some(dept_name) => dept_name.trim(),
            None => {
                println!("Using wrong format, please try again");
                continue;
            }
        };
        match directory.get_mut(&emp_dept.to_string()) {
            Some(emp_dept_vec) => emp_dept_vec.push(String::from(*emp_name)),
            None => {
                let mut emp_dept_vec:Vec<String> = Vec::new();
                emp_dept_vec.push(String::from(*emp_name));
                directory.insert(String::from(emp_dept), emp_dept_vec);
            }
        }
        println!("{} added!", emp_name);
    }
    println!("{:?}", directory);
}
