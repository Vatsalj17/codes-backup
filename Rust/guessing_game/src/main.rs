use rand::random_range;
use std::cmp::Ordering;
use std::io::{self, Write};

fn main() {
    let number = random_range(1..=100);
    println!("Guess the Number!");
    let mut count = 0;
    loop {
        print!("Please input your guess: ");
        io::stdout().flush().unwrap();
        let mut guess = String::new();
        io::stdin()
            .read_line(&mut guess)
            .expect("Failed to read line");
        let guess: u32 = match guess.trim().parse() {
            Ok(num) => {num},
            Err(_) => continue,
        };
        // println!("Your Guess: {}", guess);
        match guess.cmp(&number) {
            Ordering::Less => println!("Very Small"),
            Ordering::Equal => {
                println!("You Won");
                break;
            },
            Ordering::Greater => println!("Very Big"),
        }
        count += 1;
    }
    println!("You guessed at attempt no. {}", count);
}
