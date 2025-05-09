#include <iostream>
#include <winsock2.h>
#include <thread>
#include <string>
#include <vector>
#include <sstream>

#pragma comment(lib, "ws2_32.lib")
using namespace std;

string seleccionarAccion() {
    cout << "Acciones disponibles:\n";
    cout << "1. Apple\n2. Google\n3. Amazon\n4. Tesla\n";
    cout << "Seleccione una acción: ";
    int opcion;
    cin >> opcion;
    cin.ignore();
    switch (opcion) {
        case 1: return "Apple";
        case 2: return "Google";
        case 3: return "Amazon";
        case 4: return "Tesla";
        default: return "Apple";
    }
}

string crearMensajeOferta(const string& operacion, const string& accion, int cantidad, int precio) {
    ostringstream oss;
    oss << operacion << " " << accion << " " << cantidad << " " << precio;
    return oss.str();
}

void recibirMensajes(SOCKET sock) {
    char buffer[1024];
    while (true) {
        int bytesReceived = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0';
            cout << "\n Notificación: " << buffer << "\n";
        }
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(54000);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (sockaddr*)&server, sizeof(server));

    // Solicitar nombre de usuario
    string nombreUsuario;
    cout << " Ingrese su nombre de usuario: ";
    getline(cin, nombreUsuario);
    send(sock, nombreUsuario.c_str(), nombreUsuario.size() + 1, 0);

    cout << " Conectado al servidor como " << nombreUsuario << "\n";

    thread receptor(recibirMensajes, sock);
    receptor.detach();

    while (true) {
        string operacion;
        cout << "\nIngrese el tipo de operación (compra/venta/mostrar): ";
        getline(cin, operacion);

        string accion;
        int cantidad = 0, precio = 0;

        if (operacion == "compra" || operacion == "venta") {
            accion = seleccionarAccion();
            cout << "Cantidad: ";
            cin >> cantidad;
            cout << "Precio por acción: ";
            cin >> precio;
            cin.ignore();
        }

        string mensaje = crearMensajeOferta(operacion, accion, cantidad, precio);
        send(sock, mensaje.c_str(), mensaje.size() + 1, 0);
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}