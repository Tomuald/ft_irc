#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

const int BUFFER_SIZE = 1024;

int main(int argc, char* argv[]) {
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <server> <port> <nickname>" << endl;
        exit(1);
    }

    char* server = argv[1];
    char* port = argv[2];
    char* nickname = argv[3];

    // create socket
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }

    // resolve server address
    struct hostent* he = gethostbyname(server);
    if (he == NULL) {
        perror("gethostbyname");
        exit(1);
    }

    // set up server address
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(port));
    server_addr.sin_addr = *((struct in_addr*)he->h_addr);

    // connect to server
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(1);
    }

    // send nickname to server
    char buffer[BUFFER_SIZE];
    snprintf(buffer, BUFFER_SIZE, "NICK %s\r\n", nickname);
    if (send(sock, buffer, strlen(buffer), 0) == -1) {
        perror("send");
        exit(1);
    }

    // send user info to server
    snprintf(buffer, BUFFER_SIZE, "USER %s 0 * :IRC client\r\n", nickname);
    if (send(sock, buffer, strlen(buffer), 0) == -1) {
        perror("send");
        exit(1);
    }

    char buff[1024];
    fgets(buff, sizeof(buff), stdin);
    send(sock, buff, sizeof(buff), 0);
    // read messages from server
    while (true) {
        int nbytes = recv(sock, buffer, BUFFER_SIZE - 1, 0);
        if (nbytes == -1) {
            perror("recv");
            exit(1);
        }
        if (nbytes == 0) {
            cout << "Disconnected from server." << endl;
            break;
        }
        buffer[nbytes] = '\0';
        cout << buffer;
    }

    // close socket
    close(sock);

    return 0;
}
