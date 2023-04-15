#include <iostream>
#include <string>
#include <sstream>

// Función que procesa el mensaje de registro
void processRegistration(std::string message) {
    std::stringstream ss(message);
    std::string command;
    ss >> command;

    // Procesar la contraseña (PASS)
    if (command == "PASS") {
        std::string password;
        ss >> password;
        // Aquí se puede hacer lo que sea necesario con la contraseña recibida
        std::cout << "Contraseña recibida: " << password << std::endl;
    }

    // Procesar el apodo (NICK)
    else if (command == "NICK") {
        std::string nickname;
        ss >> nickname;
        // Aquí se puede hacer lo que sea necesario con el apodo recibido
        std::cout << "Apodo recibido: " << nickname << std::endl;
    }

    // Procesar el usuario (USER)
    else if (command == "USER") {
        std::string username, realname;
        ss >> username;
        ss.ignore();
        std::getline(ss, realname);
        // Aquí se puede hacer lo que sea necesario con el usuario y nombre real recibidos
        std::cout << "Usuario recibido: " << username << std::endl;
        std::cout << "Nombre real recibido: " << realname << std::endl;
    }

    // Mensaje inválido
    else {
        std::cout << "Comando de registro inválido: " << command << std::endl;
    }
}

int main() {
    // Ejemplo de mensajes de registro
    std::string message1 = "PASS         mypassword";
    std::string message2 = "NICK mynickname";
    std::string message3 = "USER myusername myhostname myservername :My real name";

    // Procesar los mensajes de registro
    processRegistration(message1);
    processRegistration(message2);
    processRegistration(message3);

    return 0;
}