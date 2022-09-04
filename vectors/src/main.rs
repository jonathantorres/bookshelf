fn main() {

}

fn loop_on_vector() {
    let v = vec![10, 11, 21, 31, 41];
    for i in &v {
        println!("num is: {}", i);
    }
    println!("another: {}", v[0]);
}

fn vector_of_strings() {
    let mut strs:Vec<String> = Vec::new();
    strs.push(String::from("hola"));
    strs.push(String::from("again"));
    strs.push(String::from("hello"));
}

fn reading_vectors() {
    let v = vec![1,2,3,4];
    let third:i32 = v[2];
    let second:Option<&i32> = v.get(1);
    match second {
        Some(num) => println!("sec num:{}", num),
        None => println!("Nope!"),
    }
    println!("num:{}", third);
    println!("num:{}", v[2]);
}

fn creating_vectors() {
    let mut v = Vec::new();
    v.push(1);
    v.push(2);
    v.push(3);
    v.push(4);

    let v2:Vec<i32> = Vec::new();
    let v3 = vec![1,2,3,4];
}
