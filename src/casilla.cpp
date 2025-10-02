#include "casilla.h"

Casilla::Casilla() : estado(0) {}
void Casilla::ponerBarco() { estado = 1; }
bool Casilla::esBarco() const { return estado == 1; }
bool Casilla::disparar() {
    if (estado == 1) { estado = 3; return true; }
    if (estado == 0) { estado = 2; return false; }
    return false;
}

int Casilla::obtenerEstado() const { return estado; }

void Casilla::setEstado(int e) { estado = e; }