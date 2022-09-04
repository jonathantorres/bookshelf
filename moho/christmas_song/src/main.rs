fn main() {
    let days = ["first", "second", "third"];
    let gifts = [
        "A Partridge in a Pear Tree",
        "Two Turtle Doves\nand a Partridge in a Pear Tree",
        "Three French Hens\nTwo Turtle Doves\nand a Partridge in a Pear Tree"
    ];
    let mut i = 0;

    for day in days.iter() {
        send_to_me(day.to_string(), gifts[i].to_string());
        i = i+1;
    }
}

fn send_to_me(day: String, gift: String) {
    println!("On the {} day of Christmas", day);
    println!("my true love sent to me: {}", gift);
    println!("");
}
