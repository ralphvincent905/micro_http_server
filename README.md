# Micro HTTP Server in C

This project is a lightweight HTTP/1.1 server written in C for the CPAN226 Network Programming course. The server listens on a specified port, accepts TCP connections, parses GET requests, loads files from a `www/` directory, and returns valid HTTP responses. It demonstrates low-level socket programming, HTTP parsing, and modular C design.

## Features
- Handles HTTP/1.1 GET requests
- Serves static files from the `www/` directory
- MIME type detection for HTML, CSS, images, and more
- Directory traversal protection
- 404 and 405 error handling
- Windows-compatible (Winsock)

## Project Structure

src/
main.c      # Socket setup, binding, listening, accepting clients
http.c      # Request parsing and response construction
file.c      # File loading and MIME type detection
include/
http.h
file.h
www/
index.html
style.css
Makefile


## How to Build (Windows / MSYS2 MinGW64)
mingw32-make

## How to Run
./micro_http <port> ./www

Example:
./micro_http 8080 ./www


## How It Works
The server creates a TCP socket, binds it to the chosen port, and listens for incoming connections. When a client connects, the server reads the HTTP request, extracts the method and path, loads the requested file, determines the MIME type, and sends a valid HTTP/1.1 response. Unsupported methods return a 405, and missing files return a 404.

## Known Limitations
- Single-threaded
- Blocking I/O
- GET-only support

## Future Improvements
- Multi-threading
- Persistent connections
- POST method support
- Routing system

## Author
Ralph Sampaga  
CPAN226 – Network Programming
