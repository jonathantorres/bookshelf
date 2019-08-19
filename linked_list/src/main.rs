#[derive(Debug)]
struct Node {
    prev: Option<Box<Node>>,
    next: Option<Box<Node>>,
    value: Box<i32>,
}

#[derive(Debug)]
struct LinkedList {
    first: Option<Box<Node>>,
}

impl LinkedList {
    fn new() -> LinkedList {
        LinkedList {
            first: None,
        }
    }

    fn push(&mut self, val: i32) {
        let node = Box::new(Node{
            value: Box::new(val),
            prev: None,
            next: None,
        });

        if let None = self.first {
            self.first = Some(node);
            return;
        }

        let mut cur_node = &self.first;

        while let None = cur_node {
            //
        }

        if let Some(node) = cur_node {
            //
        }
    }
}

fn main() {
    let mut list = LinkedList::new();
    list.push(100);
    list.push(200);
    list.push(200);
    list.push(400);
    println!("{:?}", list);
}
