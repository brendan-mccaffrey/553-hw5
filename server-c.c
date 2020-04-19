#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>

#define QUEUE_LENGTH 10
#define RECV_BUFFER_SIZE 2048

/* TODO: server()
 * Open socket and wait for client to connect
 * Print received message to stdout
 * Return 0 on success, non-zero on failure
*/
int server(char *server_port) {

    int status, sock, client, client_len, numBytes;
    char buf[RECV_BUFFER_SIZE];
    struct sockaddr_in serv_addr;
    struct sockaddr_in client_addr;

    // Support IPv4
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    // atoi converts from ASCII to integer
    // htons handles different byte orderings used by different computers
  	serv_addr.sin_port = htons(atoi(server_port));

  	// Create socket (IPv4 and TCP)
  	sock = socket(serv_addr.sin_family, SOCK_STREAM, 0);
    
	if (sock == -1) {
		perror("ERROR: Initializing socket ");
    	exit(1);
	}
             
    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        perror("ERROR: Binding socket ");
    	exit(1);
    }

    if (listen(sock, QUEUE_LENGTH) == -1) {
		perror("ERROR: Listening");
		exit(1);
	}

	client_len = sizeof(client_addr);

	// Loop indefinitely
	while(1) {

		client = accept(sock, (struct sockaddr *) &client_addr, &client_len);
		if (client == -1) {
			perror("ERROR: Accepting client");
			exit(1);
		}

		// Copy 0s into buffer
		bzero(buf, RECV_BUFFER_SIZE);
		// numBytes is how many bytes were received
		numBytes = read(client, buf, RECV_BUFFER_SIZE);

		if (numBytes < 0) {
			perror("ERROR: Reading from client");
		} else {
			printf("%s", buf);
		}
		fflush(stdout);
	}
}  


/*
 * main():
 * Parse command-line arguments and call server function
*/
int main(int argc, char **argv) {
  char *server_port;

  if (argc != 2) {
    fprintf(stderr, "Usage: ./server-c [server port]\n");
    exit(EXIT_FAILURE);
  }

  server_port = argv[1];
  return server(server_port);
}
