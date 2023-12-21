use std::net::{TcpListener, TcpStream};
use std::io::{Read, Write};
use std::sync::mpsc;
use std::thread;

fn handle_client(mut stream: TcpStream) {
    let mut buffer = [0; 1024];

    while match stream.read(&mut buffer) {
        Ok(size) => {
            // Echo back to client
            stream.write_all(&buffer[0..size]).unwrap();
            true
        }
        Err(_) => {
            // Handle error (e.g., connection closed)
            println!("An error occurred, terminating connection with {}", stream.peer_addr().unwrap());
            stream.shutdown(std::net::Shutdown::Both).unwrap();
            false
        }
    } {}
}

fn main() -> std::io::Result<()> {
    let listener = TcpListener::bind("127.0.0.1:8080")?;
    let (tx, rx) = mpsc::channel();

    // Thread for handling client connections
    thread::spawn(move || {
        for stream in rx {
            thread::spawn(|| {
                handle_client(stream);
            });
        }
    });

    println!("Server listening on port 8080");

    // Accept connections and send them to the handler thread
    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                let tx = tx.clone();
                tx.send(stream).expect("Failed to send stream to handler");
            }
            Err(e) => {
                eprintln!("Connection failed: {}", e);
            }
        }
    }

    Ok(())
}
