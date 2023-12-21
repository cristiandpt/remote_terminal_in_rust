# Use an official Rust base image as the base image
FROM rust:latest


RUN ["mkdir", "-p", "/home/app/remote_server"]

# Set the working directory inside the container
WORKDIR /home/app/remote_terminal

#RUN ["cargo", "new", "rust_domestik_app"] 

# Copy the Cargo.toml and Cargo.lock files to the container ./domestik_app/Cargo.lock
COPY ./Cargo.toml  ./

# Build the dependencies in a separate step to optimize caching    # --release
#RUN cargo build 

# Copy the source code to the container
COPY ./ .

# Build the application  --release
RUN cargo build 

# Expose the port on which the server will listen
EXPOSE 8083

# Specify the command to run when the container starts "--release"
CMD ["cargo", "run"]
