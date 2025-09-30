#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
#include "casilla.h"

const int FILAS = 8;
const int COLUMNAS = 8;

class Tablero {
public:
    Tablero();
    bool colocarBarco(int fila, int col, int tam, char orientacion);
    bool dispararEn(int fila, int col);
    bool todosHundidos() const;
    void mostrar(bool propio) const;
    void guardar(std::ostream &out) const;
    void cargar(std::istream &in);
private:
    Casilla celdas[FILAS][COLUMNAS];
    const std::string BG_AZUL = "\x1B[44m";
    const std::string BG_NEGRO = "\x1B[40m";
    const std::string BG_ROJO = "\x1B[41m";
    const std::string BG_GRIS = "\x1B[48;2;128;128;128m";
    const std::string RESET = "\x1B[0m";
};

#endif
