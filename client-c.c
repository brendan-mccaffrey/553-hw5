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

#define SEND_BUFFER_SIZE 2048


/* TODO: client()
 * Open socket and send message from stdin.
 * Return 0 on success, non-zero on failure
*/
int client(char *server_ip, char *server_port) {
  int sock, numBytes, len;
  char input[SEND_BUFFER_SIZE];
  struct sockaddr_in serv_addr;

  // Create socket (IPv4, TCP)
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1) {
    perror("ERROR: Initializing socket ");
      exit(1);
  }

  
  server_addr.sin_family = AF_INET; // Support IPv4
  serv_addr.sin_addr.s_addr = inet_addr(server_ip); // This would be inet_pton(server_ip) for IPv6
  serv_addr.sin_port = htons(atoi(server_port)); // atoi converts from ASCII to integer
  // htons handles different byte orderings used by different computers

  if (connect(s, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
    perror("ERROR: Connecting to server");
    exit(1);
  } else {
    printf("Connected to server!");
    while (fgets(input, SEND_BUFFER_SIZE, stdin)) {
      len = strlen(input);
      numBytes = send(s, input, len, 0);
      if (numBytes < len) {
        // WE NEED TO RESEND SOME DATA
      }
    }
  }
  close(sock);
  return 0;
}

/*
 * main()
 * Parse command-line arguments and call client function
*/
int main(int argc, char **argv) {
  char *server_ip;
  char *server_port;

  if (argc != 3) {
    fprintf(stderr, "Usage: ./client-c [server IP] [server port] < [message]\n");
    exit(EXIT_FAILURE);
  }

  server_ip = argv[1];
  server_port = argv[2];
  return client(server_ip, server_port);
}
