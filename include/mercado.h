#ifndef MERCADO_H
#define MERCADO_H

#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
struct Oferta {
    string usuario;
    string tipo;     // "compra" o "venta"
    string accion;
    int cantidad;
    double precio;
};

struct Cliente {
    string nombre;
    double saldo = 100.0;
    unordered_map<string, int> acciones;
    vector<string> historial;

    Cliente() = default;
    Cliente(const string& nombreUsuario) : nombre(nombreUsuario), saldo(100.0) {}
};

string crearMensajeOferta(const Oferta& oferta);
vector<Oferta> procesarMensaje(const string& mensaje, Cliente& cliente, vector<Oferta>& mercado, string& respuesta);
string mostrarHistorial(const Cliente& cliente);

#endif