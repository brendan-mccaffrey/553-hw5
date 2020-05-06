# Project 5: Socket Programming

This is a homework project I completed with my good friend and project partner Manny Kuflik.

##### Server specification
* The server program should listen on a socket, wait for a client to connect, receive a stream of bytes from the client, print those bytes directly to stdout, and then wait for the next client indefinitely.
* The server should take one command-line argument: the port number to listen on for client connections.
* The server should accept and process client communications in an infinite loop, allowing multiple clients to send messages to the same server. The server should only exit in response to an external signal (e.g. SIGINT from pressing `ctrl-c`).
* The server should maintain a 10 client connection queue and handle multiple client connection attempts sequentially. In real applications, a TCP server would fork a new process to handle each client connection concurrently, but that is not necessary for this assignment.
* The server should gracefully handle error values potentially returned by socket programming library functions (see specifics for each language below).

##### Client specification
* The client program should contact a server, read some bytes from stdin, send the bytes, and exit.
* The client should read and send the message *exactly* as it appears in stdin until reaching an EOF (end-of-file).  This implies that messages do not contain EOFs.
* The client should take two command-line arguments: the IP address of the server and the port number of the server.
* The client must be able to handle arbitrarily large messages by iteratively reading and sending chunks of the message, rather than reading the whole message into memory first.
* The client should handle partial sends (when a socket only transmits part of the data given in the last `send` call) by attempting to re-send the rest of the data until it has all been sent.
* The client should gracefully handle error values potentially returned by socket programming library functions.

# Credit
This project adapted, with permission, from Nick Feamster [feamster -at- uchicago . edu].

