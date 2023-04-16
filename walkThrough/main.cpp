#include <iostream>

#include <unistd.h> // read & write

#include <sys/socket.h> // socket - bind
#include <arpa/inet.h> // inet_addr

#define SERV_PORT       6667
#define SERV_IP   "10.13.3.5"

int main(void) {
    int fd_s, fd_new;
    struct sockaddr_in serv_struct;
    struct sockaddr_in client_struck;
    int opt_setsock;
    int len_rx, len_tx;
    char buff_rx[1000] = {0};
    unsigned len;


    if ((fd_s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror ("socket");
        return (-1);
    }
    else
        std::cout << "socket creado fd = " << fd_s << std::endl;
    
    memset (&serv_struct, 0, sizeof(serv_struct));

    serv_struct.sin_family = AF_INET;
    serv_struct.sin_addr.s_addr = inet_addr(SERV_IP);
    serv_struct.sin_port = htons(SERV_PORT);

    if (setsockopt(fd_s, SOL_SOCKET, SO_REUSEADDR, &opt_setsock, sizeof(opt_setsock)) == -1) {
        perror("setsockopt");
        return (-1);
    }
    else
        std::cout << "setSocket exitoso = " << opt_setsock << std::endl;

    if ((bind(fd_s, (struct sockaddr *) &serv_struct, sizeof(serv_struct))) != 0) {
        perror("bind");
        return (-1);
    }
    else   
        std::cout << "Socket success binded\n";

     // Listen -- marca el socket como pasivo // aceptando conexion
    if ((listen(fd_s, 10)) != 0)
        std::cout << "Erro Listen\n";
    else
        std::cout << "Server Listen en puerto : " << ntohs(serv_struct.sin_port) << std::endl;

    while (1) {
        std::cout << " +++++++ Waiting for new connection ++++++++ \n";
        fd_new = accept(fd_s, (struct sockaddr *) &client_struck, &len);
        if (fd_new == -1)
            std::cout << "error accept\n";
        else {
            std::cout << "IN Accept client_struck in fd = " << fd_new << std::endl;
            std::cout << "IN client_strucke ADDR " << inet_ntoa(client_struck.sin_addr) << std::endl;
        }
        // write(fd_new, "hello", 5);
        
        len_rx = read(fd_new, buff_rx, sizeof(buff_rx));
        buff_rx[len_rx] = '\0';
        
        std::cout << "Len_rx = " << len_rx << std::endl;
        std::cout << "Buffer = \n" << buff_rx;
        // while (buff_rx != QUIT) {
        //     std::cout << "Extoy segundo while\n";

        // }

    }
    
    return (0);

}