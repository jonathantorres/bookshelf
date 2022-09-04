#[derive(Debug)]
enum Message {
    Quit,
    Move(MoveMessage),
    // Move {x: i32, y: i32},
    Write(String),
    ChangeColor(i32, i32, i32),
}
struct QuitMessage;
#[derive(Debug)]
struct MoveMessage {
    x: i32,
    y: i32,
}
struct WriteMessage(String);
struct ChangeColorMessage(i32, i32, i32);

impl Message {
    fn call(&self) {
        match self {
            Message::Quit => println!("QUIT!"),
            Message::Move(mv) => println!("Using struct x:{},y:{}", mv.x, mv.y),
            // Message::Move{x,y} => println!("Using struct x:{},y:{}", x, y),
            Message::Write(msg) => println!("message is: {}", msg),
            Message::ChangeColor(a,b,c) => println!("Colors {} {} {}", a, b, c),
        };
    }
}
fn main() {
    let mv = MoveMessage{x: 100, y: 200};
    // let m = Message::Write(String::from("hello"));
    // let m = Message::Move{x:10, y:11};
    let m = Message::Move(mv);
    // let m = Message::ChangeColor(1,1,1);
    // let m = Message::Quit;
    m.call();
}


// #[derive(Debug)]
// enum Car {
//     Convertible,
//     Van,
//     Sport,
// }

// fn main() {
//     let conv = Car::Convertible;

//     let v = match conv {
//         Car::Convertible => 0,
//         Car::Van => 1,
//         Car::Sport => 2,
//     };
//     println!("Car type: {:?}", conv);
//     println!("Car type: {:?}", v);
// }
