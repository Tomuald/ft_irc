#include <iostream>

#include <unistd.h> // read & write
#include <fcntl.h>

#include <sys/socket.h> // socket - bind
#include <arpa/inet.h> // inet_addr

/*
HardCoding por el momento
server parameters
*/
#define SERV_PORT       8080
#define SERV_IP   "127.0.0.1"
#define BUFF_SIZE       1000 // Buffer rx, tx max size
#define BACKLOG         5 // Max. No client_struckes pendientes en cola

int main() {
    
    int fds, fd_new; // fds de socket y connect
    unsigned int len; // len of client_struck addr - long de struct sockaddr_in
    struct sockaddr_in serv_struck, client_struck;
    int fdope;
    char lec[1053] = {0};

    fdope = open("prueba.html", O_RDONLY);
    std::cout << "fdope = " << fdope << std::endl;
    int leido = read(fdope, lec, 1053);
    std::cout << "leido = " << leido << std::endl;

    // write(1, lec, 1053);

   int  len_rx, len_tx = 0;
//    char hello[BUFF_SIZE] = "HTTP/1.1 200 Ok\nContent-Type: text/plain\nContent-Length: 10\n\nHello Word!@";
   char hello[BUFF_SIZE] = "HTTP/1.1 200 Ok\nContent-Type: text/plain\nContent-Length: 100\n";
   char buff_rx[BUFF_SIZE] = {0}; // Buffers para recepcion

   if ((fds = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return (-1);
   }
   else
    std::cout << "socket creado fd = " << fds << std::endl;

    /* clear struct sockaddr_in*/
    memset(&serv_struck, 0, sizeof(serv_struck));

    // asigno IP, puerto y familia IPV4
    serv_struck.sin_family = AF_INET;
    serv_struck.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_struck.sin_port = htons(SERV_PORT);

    if ((bind(fds, (struct sockaddr *) &serv_struck, sizeof(serv_struck))) != 0) {
        perror("bind");
        return (-1);
    }
    else   
        std::cout << "Socket success binded\n";

    // Listen -- marca el socket como pasivo // aceptando conexion
    if ((listen(fds, BACKLOG)) != 0)
        std::cout << "Erro Listen\n";
    else
        std::cout << "Server Listen en puerto :" << ntohs(serv_struck.sin_port) << std::endl;

   std::cout << "sizeof client_struck = "<< sizeof(client_struck) << std::endl; 

    while (1) {
        std::cout << " +++++++ Waiting for new connection ++++++++ \n";
        fd_new = accept(fds, (struct sockaddr *) &client_struck, &len);
        if (fd_new == -1)
            std::cout << "error accept\n";
        else {
            std::cout << "IN Accept client_struck in fd = " << fd_new << std::endl;
            std::cout << "IN client_strucke ADDR " << inet_ntoa(client_struck.sin_addr) << std::endl;
        }


        len_rx = read(fd_new, buff_rx, sizeof(buff_rx));

        std::cout << "Buffer = \n" << buff_rx; 

        if (len_rx < 0)
            std::cout << "No bytes para leer\n";
        
        write(fd_new, hello, sizeof(hello));
        write(fd_new, lec, 1053);

        
        close(fd_new);
    }
//    no lo puedo usar getaddrinfo()
//     struct addrinfo hints;
//     struct addrinfo *s;
//     memset(&hints, 0, sizeof hints);
//     hints.ai_family = AF_UNSPEC;
//     hints.ai_socktype = SOCK_STREAM;
//     hints.ai_flags = AI_PASSIVE;
//     status = getaddrinfo(NULL, "3490", &hints, &s);


    // Prints
    // std::cout << "sin_fam = " <<  serv_struck.sin_port << std::endl;

    return (0);
} 