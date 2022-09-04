use std::collections::HashMap;

fn main() {
    create_hashmaps();
    get_values();
    iterate_over_it();
}

fn iterate_over_it() {
    let mut scores:HashMap<String, i32> = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 20);

    for (key,value) in &scores {
        println!("{}: {}", key, value);
    }
}

fn get_values() {
    let mut scores = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 20);

    let key = String::from("Blue");
    let cur_score = match scores.get(&key) {
        Some(score) => score,
        None => &0,
    };
    println!("score is: {}", cur_score);
}

fn create_hashmaps() {
    let mut scores = HashMap::new();
    scores.insert(String::from("Blue"), 10);
    scores.insert(String::from("Yellow"), 20);
}
