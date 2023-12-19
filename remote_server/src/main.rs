use std::io::{Read, Write};
use std::net::{TcpListener, TcpStream};
use std::process::Command;

// Server
fn server() {
    let listener = TcpListener::bind("0.0.0.0:8083").expect("Failed to bind");
    println!("Server listening on port 8083");

    for stream in listener.incoming() {
        match stream {
            Ok(mut stream) => {
                let mut buffer = [0; 1024];
                stream.read(&mut buffer).expect("Failed to read from stream");
                println!("Received message: {}", String::from_utf8_lossy(&buffer));

                let output = if cfg!(target_os = "windows") {
                    Command::new("cmd")
                        .args(["/C", "echo hello"])
                       // .spawn()
                        .output()
                        .expect("failed to execute process")
                } else {
                    Command::new("sh")
                        .arg("-c")
                        .arg("echo hello")
                        //.spawn()
                        .output()
                        .expect("failed to execute process")
                };
                
                let hello = output.stdout;

                stream.write_all(b"Hello from server!").expect("Failed to write to stream");
            }
            Err(e) => {
                println!("Error: {}", e);
            }
        }
    }
}


fn main() {
    // Start server in a separate thread
    std::thread::spawn(server);
     // Wait for a while to let the server start
     std::thread::sleep(std::time::Duration::from_secs(30));
     // Start client
}



