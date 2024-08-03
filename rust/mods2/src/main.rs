mod conf;
mod ftr;
mod server;
mod session;

use conf::Conf;
use server::Server;
use std::collections::HashMap;

fn main() {
    let map: HashMap<String, String> = HashMap::new();
    let conf = Conf::new();
    let server = Server::new();

    // load and test the configuration file
    conf.load();

    // start the server
    server.start();

    println!("The HashMap: {:?}", map);
}
