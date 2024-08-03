use std::collections::LinkedList;
use std::io::{Error, ErrorKind};

fn main() {
    loop {
        let mut line = String::new();
        let bytes_read = std::io::stdin().read_line(&mut line);
        match bytes_read {
            Ok(n) => {
                if n == 0 {
                    break;
                }

                match calculate(line) {
                    Ok(n) => println!("= {}", n),
                    Err(e) => {
                        println!("error reading token: {}", e);
                        continue;
                    }
                }
            }
            Err(e) => {
                println!("error reading input: {}", e);
                continue;
            }
        }
    }
}

struct Stack {
    items: LinkedList<f64>,
}

impl Stack {
    fn new() -> Self {
        Stack {
            items: LinkedList::new(),
        }
    }

    fn push(&mut self, item: f64) {
        self.items.push_front(item);
    }

    fn pop(&mut self) -> f64 {
        match self.items.pop_front() {
            Some(n) => n,
            None => {
                panic!("poping from an empty stack!");
            }
        }
    }
}

fn calculate(line: String) -> Result<f64, std::io::Error> {
    let tokens: Vec<&str> = line.trim().split(' ').collect();
    let mut stack = Stack::new();

    for tok in tokens {
        if tok == "+" {
            let op1 = stack.pop();
            let op2 = stack.pop();
            stack.push(op1 + op2);
        } else if tok == "-" {
            let op2 = stack.pop();
            let op1 = stack.pop();
            stack.push(op1 - op2);
        } else if tok == "*" {
            let op1 = stack.pop();
            let op2 = stack.pop();
            stack.push(op1 * op2);
        } else {
            // could be a number try to parse it
            match tok.parse::<f64>() {
                Ok(n) => {
                    stack.push(n);
                }
                Err(e) => {
                    return Err(Error::new(
                        ErrorKind::Other,
                        format!("error parsing the token: {}", e),
                    ));
                }
            }
        }
    }
    Ok(stack.pop())
}
