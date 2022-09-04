fn main() {
    let s = String::from("book");

    // Add code here that calls the pluralize function
    let plural = pluralize(s.clone());

    println!(
        "I have one {}, you have two {}",
        s,
        plural,
    );
}

// Add appropriate parameters, return values, and implementation to this function
fn pluralize(mut w: String) -> String {
    w.push_str("s");
    w
}
