fn main() {
    let w = String::from("John");
    let w2 = String::from("Apple");
    let w3 = String::from("airplane");
    let w4 = String::from("first");
    println!("{}", convert_to_pig(&w));
    println!("{}", convert_to_pig(&w2));
    println!("{}", convert_to_pig(&w3));
    println!("{}", convert_to_pig(&w4));
}

fn convert_to_pig(word:&String) -> String {
    let mut pig_word = String::new();
    let vowels = vec!["a", "A", "e", "E", "i", "I", "o", "O", "u", "U"];
    let mut first_is_vowel = false;

    for c in &vowels {
        if word.starts_with(c) {
            first_is_vowel = true;
        }
    }

    if first_is_vowel {
        pig_word.push_str(word.as_str());
        pig_word.push_str("-hay");
    } else {
        let mut i = 0;
        let first_letter = word.chars().next().unwrap();
        for ch in word.chars() {
            if i != 0 {
                pig_word.push(ch);
            }
            i += 1;
        }
        pig_word.push('-');
        pig_word.push(first_letter);
        pig_word.push_str("ay");
    }
    pig_word
}
