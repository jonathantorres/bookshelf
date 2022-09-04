use std::fs::File;
use std::io::Read;
use std::process;

use rand::{thread_rng, Rng};

fn get_word() -> String {
    // Open and read the file
    let mut file = match File::open("words.txt") {
        Ok(file) => file,
        Err(err) => {
            eprintln!("Error! {}", err);
            process::exit(1);
        }
    };

    let mut file_buf = String::new();
    if let Err(err) = file.read_to_string(&mut file_buf) {
        eprintln!("Failed reading file: {}", err);
        process::exit(1);
    };

    let words: Vec<&str> = file_buf.split('\n').collect();
    let word_index: usize = thread_rng().gen_range(0, words.len() - 1);

    String::from(words[word_index])
}

fn display_guess(word_to_guess: &str, guessed_letters: &Vec<char>) {
    print!("Current Guess: ");

    for c in word_to_guess.chars() {
        if guessed_letters.contains(&c) {
            print!("{}", c);
        } else {
            print!("_");
        }
    }
    println!("");
}

fn word_is_guessed(word_to_guess: &str, guessed_letters: &Vec<char>) -> bool {
    let mut is_guessed = true;

    for c in word_to_guess.chars() {
        if !guessed_letters.contains(&c) {
            is_guessed = false;
            break;
        }
    }
    is_guessed
}

fn main() {
    let word_to_guess: String = get_word();
    let mut guessed_letters: Vec<char> = Vec::new();
    let mut used_attempts = 0;
    let max_attempts = word_to_guess.len() * 2;

    println!("Welcome to Hangman! Please enter your guess");
    println!("{}", word_to_guess);

    loop {
        if used_attempts >= max_attempts {
            println!("Game Over! You lost!");
            break;
        }

        if word_is_guessed(&word_to_guess, &guessed_letters) {
            println!("Congrats! You Won!");
            println!("Word was: {}", word_to_guess);
            break;
        }

        display_guess(&word_to_guess, &guessed_letters);

        let mut line: String = String::new();
        if let Err(_) = std::io::stdin().read_line(&mut line) {
            eprintln!("Error reading input, please try again.");
            continue;
        }

        let char_entered: char = line.as_str().chars().next().unwrap();
        if let None = word_to_guess.find(char_entered) {
            used_attempts += 1;
        } else {
            guessed_letters.push(char_entered);
        }
    }
}
