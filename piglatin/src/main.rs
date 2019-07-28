fn main() {
    let w = String::from("John");
    let w2 = String::from("Apple");
    let w3 = String::from("airplane");
    println!("{}", convert_to_pig(&w));
    println!("{}", convert_to_pig(&w2));
    println!("{}", convert_to_pig(&w3));
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

    }
    pig_word
}
