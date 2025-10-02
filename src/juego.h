#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"
#include <string>

class Juego {
public:
    Juego();
    void configurarJugadores();
    void nuevaPartidaManual();
    void cargarPartida(const char *ruta);
    void guardarPartida(const char *ruta) const;
    void mostrar() const;
    void turno();
    bool finJuego() const;
    void menuDuranteJuego();
private:
    Tablero t1, t2;
    std::string n1, n2;
    bool enCurso;
    int b1, b2;
    int turnoActual; // 1 o 2
};

#endif
