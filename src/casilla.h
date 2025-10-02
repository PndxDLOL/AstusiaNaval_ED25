#ifndef CASILLA_H
#define CASILLA_H

class Casilla {
public:
    Casilla();
    void ponerBarco();
    bool esBarco() const;
    bool disparar();
    int obtenerEstado() const;
    void setEstado(int e);
private:
    int estado;
};

#endif
