use std::io::{Read, Write};
use std::net::TcpListener;

fn main() {
    let listener = TcpListener::bind("127.0.0.1:9090").unwrap();
    loop {
        let (mut stream, addr) = listener.accept().unwrap();
        let mut s = String::new();
        println!("new stream: {:?}", stream);
        println!("new client: {:?}", addr);
        stream.write(b"Hola\n").unwrap();
        stream.read_to_string(&mut s).unwrap();
        println!("Got data: {}", s);
    }
}
