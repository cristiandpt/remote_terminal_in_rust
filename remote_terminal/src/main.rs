use clap::{Arg, Command};

fn main() {
    println!("Hello, remote shell!");

    let app = Command::new("Shell remote")
                .version("0.0.1")
                .about("Client-Server remote shell")
                .author("Cristian Pacheco, Julian Puyo, Sebastian Molina");

    let first_name = Arg::new("command")
                            .long("f")
                            .help("Command to exectue in the remote shell")
                            .required(true);
    
    let last_name = Arg::new("address")
                            .long("l")
                            .help("Address of remote shell")
                            .required(true);

    let age = Arg::new("port")
                    .long("a")
                    .help("Port of the server")
                    .required(true);

    let app = app.arg(first_name).arg(last_name).arg(age);

    let matches = app.get_matches();
    let command = matches.get_one::<String>("command").unwrap();
    let address = matches.get_one::<String>("address").unwrap();
    let port: &i8 = matches.get_one::<i8>("port").unwrap();
    
    println!("{:?}", command); 
    println!("{:?}", address);
    println!("{:?}", port);
                    
}

// matches.get_many::<String>("arg").unwrap().collect::<Vec<_>>(),
