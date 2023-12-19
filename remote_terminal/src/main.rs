use clap::{Arg, Command};
use std::io::{Read, Write};
use std::net::TcpStream;

fn client(command: String, hostname: String, port: String) {

    let server_host = hostname;
    let server_port = port;
    let mut stream = TcpStream::connect(format!("{}:{}", server_host, server_port)).expect("Failed to connect to server");

    stream.write_all(command.as_bytes()).expect("Failed to write to stream");

    let mut response = String::new();
    stream.read_to_string(&mut response).expect("Failed to read from stream");
    println!("Received response: {}", response);
}

fn main() {
    println!("Hello, remote shell!");

    let app = Command::new("Shell remote")
                .version("0.0.1")
                .about("Client-Server remote shell")
                .author("Cristian Pacheco, Julian Puyo, Sebastian Molina");

    let command_arg = Arg::new("command")
                            .long("command")
                            .short('c')
                            .help("Command to exectue in the remote shell")
                            .required(true);
    
    let hostname_arg = Arg::new("hostname")
                            .long("hostname")
                            .short('n')
                            .help("Address of remote shell")
                            .required(false);

    let port_arg = Arg::new("port")
                    .long("port")
                    .short('p')
                    .help("Port of the server")
                    .required(false);

    let app = app.arg(command_arg).arg(hostname_arg).arg(port_arg);

    let matches = app.get_matches();
    let command = matches.get_one::<String>("command").unwrap();
    let hostname = matches.get_one::<String>("hostname").unwrap();
    let port = matches.get_one::<String>("port").unwrap();
    
    println!("{:?}", command); 
    println!("{:?}", hostname);
    println!("{:?}", port);

    client(command.clone(), hostname.clone(), port.clone());
                    
}

// matches.get_many::<String>("arg").unwrap().collect::<Vec<_>>(),
