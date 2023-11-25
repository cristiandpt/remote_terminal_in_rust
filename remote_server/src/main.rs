use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};

// Server
fn server() {
    let listener = TcpListener::bind("127.0.0.1:8083").expect("Failed to bind");
    println!("Server listening on port 8083");

    for stream in listener.incoming() {
        match stream {
            Ok(mut stream) => {
                let mut buffer = [0; 1024];
                stream.read(&mut buffer).expect("Failed to read from stream");
                println!("Received message: {}", String::from_utf8_lossy(&buffer));

                stream.write_all(b"Hello from server!").expect("Failed to write to stream");
            }
            Err(e) => {
                println!("Error: {}", e);
            }
        }
    }
}

// Client
fn client() {
    let mut stream = TcpStream::connect("127.0.0.1:8083").expect("Failed to connect to server");

    stream.write_all(b"Hello from client!").expect("Failed to write to stream");

    let mut response = String::new();
    stream.read_to_string(&mut response).expect("Failed to read from stream");
    println!("Received response: {}", response);
}


fn main() {
    // Start server in a separate thread
    std::thread::spawn(server);
     // Wait for a while to let the server start
     std::thread::sleep(std::time::Duration::from_secs(5));
     // Start client
    client();
}



