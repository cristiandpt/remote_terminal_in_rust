# remote_terminal_in_rust

* To create a Rust project without install Cargo
* docker run --rm -v $(pwd):/usr/src/remote_terminal -w /usr/src/remote_terminal rust cargo new --bin remote_terminal

* The repository already has the Cargo.toml file, so itś innecesary the above command, so run:
* docker compose build "rust-terminal": It compile the rust project
* docker compose up "rust-terminal": To execute shell terminal already compiled.