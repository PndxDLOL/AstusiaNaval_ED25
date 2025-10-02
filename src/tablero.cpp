#include "tablero.h"
#include <iomanip>

Tablero::Tablero() {}

// Intenta colocar un barco de tamaño 'tam' en la posición (fila, col) con la orientación 'orientacion'.
// 'orientacion' es 'H' para horizontal y 'V' para vertical.
// Devuelve true si el barco se colocó con éxito, false si la posición es inválida o ya ocupada.
bool Tablero::colocarBarco(int fila, int col, int tam, char orientacion) {
    int df = (orientacion == 'V' ? 1 : 0);
    int dc = (orientacion == 'H' ? 1 : 0);
    for (int k = 0; k < tam; k++) {
        int rf = fila + k*df;
        int rc = col + k*dc;
        if (rf < 0 || rf >= FILAS || rc < 0 || rc >= COLUMNAS) return false;
        if (celdas[rf][rc].esBarco()) return false;
    }
    for (int k = 0; k < tam; k++) {
        int rf = fila + k*df;
        int rc = col + k*dc;
        celdas[rf][rc].ponerBarco();
    }
    return true;
}

// Dispara en la posición (fila, col).
// Devuelve true si se impactó un barco, false si fue agua o la posición es inválida.
bool Tablero::dispararEn(int fila, int col) {
    if (fila < 0 || fila >= FILAS || col < 0 || col >= COLUMNAS) return false;
    return celdas[fila][col].disparar();
}

// Verifica si todos los barcos en el tablero han sido hundidos.                
bool Tablero::todosHundidos() const {
    for (int i=0;i<FILAS;i++)
        for (int j = 0; j < COLUMNAS; j++)
            if (celdas[i][j].obtenerEstado()==1) return false;
    return true;
}

//  Muestra el tablero en la consola. Si 'propio' es true, muestra los barcos; si es false, los oculta. 
void Tablero::mostrar(bool propio) const {
    std::cout << "   ";
    for (int j = 0; j < COLUMNAS; j++) std::cout<<std::setw(2)<<j<<' ';
    std::cout<<"\n";
    for (int i = 0; i < FILAS; i++) {
        std::cout<<std::setw(2)<<i<<' ';
        for (int j = 0; j < COLUMNAS; j++) {
            int e = celdas[i][j].obtenerEstado();
            std::string color = BG_AZUL;
            if (e == 2) color = BG_NEGRO;
            else if (e == 3) color = BG_ROJO;
            else if (e == 1 && propio) color = BG_GRIS;
            std::cout<<color<<"  "<<RESET<<' ';
        }
        std::cout<<"\n";
    }
}

void Tablero::guardar(std::ostream &out) const {
    for (int i = 0; i < FILAS; i++){
        for (int j = 0; j < COLUMNAS; j++){
            out<<celdas[i][j].obtenerEstado()<<' ';
        }
        out<<"\n";
    }
}

void Tablero::cargar(std::istream &in) {
    for (int i = 0; i < FILAS; i++){
        for (int j = 0; j < COLUMNAS; j++){
            int v; in>>v;
            celdas[i][j].setEstado(v);
        }
    }
}
