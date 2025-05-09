#include "..\include\mercado.h"
#include <sstream>
#include <iostream>
using namespace std;

string crearMensajeOferta(const Oferta& oferta) {
    ostringstream oss;
    oss << oferta.tipo << " " << oferta.cantidad << " de " << oferta.accion << " a $" << oferta.precio << " (" << oferta.usuario << ")";
    return oss.str();
}

vector<Oferta> procesarMensaje(const string& mensaje, Cliente& cliente, vector<Oferta>& mercado, string& respuesta) {
    stringstream ss(mensaje);
    string comando;
    ss >> comando;

    if (comando == "mostrar") {
        ostringstream estado;
        estado << " Portafolio de " << cliente.nombre << ":\n";
        for (auto& [accion, cantidad] : cliente.acciones) {
            estado << " - " << accion << ": " << cantidad << " acciones\n";
        }
        estado << " Saldo: $" << cliente.saldo;
        respuesta = estado.str();
        return {};
    }

    string accion;
    int cantidad;
    double precio;
    ss >> accion >> cantidad >> precio;

    if (comando != "compra" && comando != "venta") {
        respuesta = " Comando inválido. Usa: compra, venta o mostrar.";
        return {};
    }

    if (cantidad <= 0 || precio <= 0) {
        respuesta = " Cantidad y precio deben ser positivos.";
        return {};
    }

    Oferta nueva = {cliente.nombre, comando, accion, cantidad, precio};
    ostringstream info;

    if (comando == "compra") {
        double total = cantidad * precio;
        if (cliente.saldo >= total) {
            cliente.saldo -= total;
            cliente.acciones[accion] += cantidad;
            info << " Compra realizada: " << cantidad << " de " << accion << " a $" << precio;
        } else {
            respuesta = " Saldo insuficiente para la compra.";
            return {};
        }
    } else if (comando == "venta") {
        if (cliente.acciones[accion] >= cantidad) {
            cliente.acciones[accion] -= cantidad;
            cliente.saldo += cantidad * precio;
            info << " Venta realizada: " << cantidad << " de " << accion << " a $" << precio;
        } else {
            respuesta = " No tienes suficientes acciones para vender.";
            return {};
        }
    }

    string mensajeOferta = crearMensajeOferta(nueva);
    cliente.historial.push_back(mensajeOferta);
    mercado.push_back(nueva);
    respuesta = info.str();

    return {nueva};
}

string mostrarHistorial(const Cliente& cliente) {
    ostringstream out;
    out << " Historial de " << cliente.nombre << ":\n";
    for (const auto& linea : cliente.historial) {
        out << " - " << linea << "\n";
    }
    return out.str();
}