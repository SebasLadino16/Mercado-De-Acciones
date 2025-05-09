#ifndef MERCADO_H
#define MERCADO_H

#include <string>
#include <vector>
#include <unordered_map>

struct Oferta {
    std::string usuario;
    std::string tipo;     // "compra" o "venta"
    std::string accion;
    int cantidad;
    double precio;
};

struct Cliente {
    std::string nombre;
    double saldo = 100.0;
    std::unordered_map<std::string, int> acciones;
    std::vector<std::string> historial;

    Cliente() = default;
    Cliente(const std::string& nombreUsuario) : nombre(nombreUsuario), saldo(100.0) {}
};

std::string crearMensajeOferta(const Oferta& oferta);
std::vector<Oferta> procesarMensaje(const std::string& mensaje, Cliente& cliente, std::vector<Oferta>& mercado, std::string& respuesta);
std::string mostrarHistorial(const Cliente& cliente);

#endif