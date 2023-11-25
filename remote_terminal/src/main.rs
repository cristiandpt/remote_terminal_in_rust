use clap::{Arg, Command};
use std::io::{Read, Write};
use std::net::TcpStream;

fn client() {

    let server_host = "remote-server";
    let server_port = "8083";
    let mut stream = TcpStream::connect(format!("{}:{}", server_host, server_port)).expect("Failed to connect to server");

    stream.write_all(b"Hello from client!").expect("Failed to write to stream");

    let mut response = String::new();
    stream.read_to_string(&mut response).expect("Failed to read from stream");
    println!("Received response: {}", response);
}

fn main() {
    println!("Hello, remote shell!");

    /*let app = Command::new("Shell remote")
                .version("0.0.1")
                .about("Client-Server remote shell")
                .author("Cristian Pacheco, Julian Puyo, Sebastian Molina");

    let first_name = Arg::new("command")
                            .long("f")
                            .help("Command to exectue in the remote shell")
                            .required(false);
    
    let last_name = Arg::new("address")
                            .long("l")
                            .help("Address of remote shell")
                            .required(false);

    let age = Arg::new("port")
                    .long("a")
                    .help("Port of the server")
                    .required(false);

    let app = app.arg(first_name).arg(last_name).arg(age);

    let matches = app.get_matches();
    let command = matches.get_one::<String>("command").unwrap();
    let address = matches.get_one::<String>("address").unwrap();
    let port: &i8 = matches.get_one::<i8>("port").unwrap();
    
    println!("{:?}", command); 
    println!("{:?}", address);
    println!("{:?}", port);*/

    client();
                    
}

// matches.get_many::<String>("arg").unwrap().collect::<Vec<_>>(),
