fn main() {
    let mut i:i32 = 1;
    let n:i32 = 10;
    let mut t1:i32 = 0;
    let mut t2:i32 = 1;
    let mut next_term:i32 = 0;

    while i <= n {
        print!("{}, ", t1);
        next_term = t1+t2;
        t1 = t2;
        t2 = next_term;
        i = i + 1;
    }
    println!("");
}
