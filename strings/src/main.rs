fn main() {
    creating_strings();
    update_strings();
    move_string();
    loop_on_string();
}

fn loop_on_string() {
    let my_str = String::from("Jonathan");
    for s in my_str.chars() {
        println!("char is: {}", s);
    }
    println!("{}", my_str);
}

fn move_string() {
    let mut s1 = String::from("foo");
    let s2 = "bar";
    s1.push_str(s2);
    println!("s2 is {}", s2);
}

fn update_strings() {
    let mut msg: String = String::new();
    msg.push_str("m");
    msg.push_str("essage");
    msg.push('s');
    println!("{}", msg);
}

fn creating_strings() {
    let my_str = String::from("Hola");
    println!("{}", my_str);
}
