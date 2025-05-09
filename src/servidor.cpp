#include <iostream>
#include <winsock2.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <mutex>
#include "../include/mercado.h"

#pragma comment(lib, "ws2_32.lib")
using namespace std;

unordered_map<SOCKET, Cliente> clientesConectados;
vector<Oferta> mercado;
mutex mtx;

void enviarATodos(const string& mensaje, SOCKET emisor = INVALID_SOCKET) {
    for (const auto& par : clientesConectados) {
        SOCKET clienteSock = par.first;
        if (clienteSock != emisor) {
            send(clienteSock, mensaje.c_str(), mensaje.size() + 1, 0);
        }
    }
}

void manejarCliente(SOCKET clienteSock) {
    char buffer[1024];

    // Recibir el nombre del cliente
    int bytesRecibidos = recv(clienteSock, buffer, sizeof(buffer), 0);
    if (bytesRecibidos <= 0) {
        closesocket(clienteSock);
        return;
    }
    buffer[bytesRecibidos] = '\0';
    string nombre(buffer);

    {
        lock_guard<mutex> lock(mtx);
        clientesConectados[clienteSock] = Cliente(nombre);
        cout << " Cliente conectado: " << nombre << endl;
    }

    string bienvenida = " Bienvenido al mercado, " + nombre + "!";
    send(clienteSock, bienvenida.c_str(), bienvenida.size() + 1, 0);

    while (true) {
        int bytesRecibidos = recv(clienteSock, buffer, sizeof(buffer), 0);
        if (bytesRecibidos <= 0) {
            lock_guard<mutex> lock(mtx);
            cout << " Cliente desconectado: " << nombre << endl;
            clientesConectados.erase(clienteSock);
            closesocket(clienteSock);
            break;
        }

        buffer[bytesRecibidos] = '\0';
        string mensaje(buffer);

        string respuesta;
        vector<Oferta> nuevasOfertas;

        {
            lock_guard<mutex> lock(mtx);
            nuevasOfertas = procesarMensaje(mensaje, clientesConectados[clienteSock], mercado, respuesta);
        }

        send(clienteSock, respuesta.c_str(), respuesta.size() + 1, 0);

        for (const auto& oferta : nuevasOfertas) {
            string notificacion = " Nueva oferta: " + crearMensajeOferta(oferta);
            enviarATodos(notificacion, clienteSock);
        }
    }
}

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    SOCKET servidor = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in direccionServidor;
    direccionServidor.sin_family = AF_INET;
    direccionServidor.sin_port = htons(54000);
    direccionServidor.sin_addr.s_addr = INADDR_ANY;

    bind(servidor, (sockaddr*)&direccionServidor, sizeof(direccionServidor));
    listen(servidor, SOMAXCONN);

    cout << " Servidor esperando conexiones en el puerto 54000...\n";

    while (true) {
        SOCKET clienteSock = accept(servidor, nullptr, nullptr);
        thread hiloCliente(manejarCliente, clienteSock);
        hiloCliente.detach();
    }

    closesocket(servidor);
    WSACleanup();
    return 0;
}