#include "juego.h"
#include <iostream>
#include <fstream>
#include <cctype>

#include <string>
#include <regex>
#include <limits>

using namespace std;

// Lee un token de la entrada 'in' y lo interpreta como un entero.
// Si la lectura falla o el token no es un entero válido, devuelve false.
// Si la lectura es exitosa, almacena el valor en 'out' y devuelve true.
// Si 'allow_neg' es false, el entero leído debe ser no negativo.   
bool readIntToken(std::istream &in, int &out, bool allow_neg=false){
    std::string tok;
    if(!(in >> tok)) return false;
    std::regex re("^-?[0-9]+$");
    if(!std::regex_match(tok, re)) return false;
    try{ out = std::stoi(tok); } catch(...) { return false; }
    if(!allow_neg && out < 0) return false;
    return true;
}

// Lee un token de la entrada 'in' y lo interpreta como un entero en el rango [minv, maxv].
// Si la lectura falla, el token no es un entero válido o está fuera del rango, devuelve false.
// Si la lectura es exitosa, almacena el valor en 'out' y devuelve true.
// Si 'allow_neg' es false, el entero leído debe ser no negativo.
bool readIntInRange(std::istream &in, int &out, int minv, int maxv, bool allow_neg=false){
    if(!readIntToken(in, out, allow_neg)) return false;
    if(out < minv || out > maxv) return false;
    return true;
}

// Lee un token de la entrada 'in' y lo interpreta como un carácter 'H' o 'V' (mayúscula o minúscula).
// Si la lectura falla o el token no es válido, devuelve false.
// Si la lectura es exitosa, almacena el valor en 'out' (como mayúscula) y devuelve true. 
bool readOrient(std::istream &in, char &out){
    std::string tok;
    if(!(in >> tok)) return false;
    if(tok.size() != 1) return false;
    char c = std::toupper(tok[0]);
    if(c != 'H' && c != 'V') return false;
    out = c;
    return true;
}

using namespace std;

Juego::Juego(){
    b1 = b2 = 0; 
    turnoActual = 1; 
    enCurso = false;
}

// Configura los nombres de los jugadores.
void Juego::configurarJugadores(){
    cout<<"Nombre jugador 1: ";
    getline(cin, n1); if(n1.empty()) getline(cin,n1);
    cout<<"Nombre jugador 2: ";
    getline(cin, n2);
}

// Configura una nueva partida con colocacion manual de barcos por ambos jugadores.
void Juego::nuevaPartidaManual(){
    int tamanios[3]={3, 2, 2};
    cout<<"--- Colocacion de "<<n1<<" ---\n";
    for(int s = 0; s < 3; s++){
        int tam = tamanios[s]; bool ok = false;
        while(!ok){
            t1.mostrar(true);
            cout<<"Coloca barco de tamano "<<tam<<" (fila col orientacion H/V). Ej: 2 3 H\n";
            int f, c; char o;
            while(true){
                if(!readIntInRange(cin, f, 0, FILAS-1) || !readIntInRange(cin, c, 0, COLUMNAS-1)){
                    std::cout << "Entrada incorrecta\n";
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if(!readOrient(cin, o)){
                    std::cout << "Entrada incorrecta\n";
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                break;
            }
            if(t1.colocarBarco(f,c,tam,o)){ok=true;b1+=tam;} else cout<<"Posicion invalida, intenta de nuevo.\n";
        }
    }
    cout<<"--- Colocacion de "<<n2<<" ---\n";
    for(int s = 0; s < 3; s++){
        int tam = tamanios[s]; bool ok=false;
        while(!ok){
            t2.mostrar(true);
            cout<<"Coloca barco de tamano "<<tam<<" (fila col orientacion H/V). Ej: 4 1 V\n";
            int f, c; char o;
            while(true){
                if(!readIntInRange(cin, f, 0, FILAS-1) || !readIntInRange(cin, c, 0, COLUMNAS-1)){
                    std::cout << "Entrada incorrecta\n";
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                if(!readOrient(cin, o)){
                    std::cout << "Entrada incorrecta\n";
                    std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                break;
            }
            if(t2.colocarBarco(f, c, tam, o)){ok = true; b2 += tam; } else cout<<"Posicion invalida, intenta de nuevo.\n";
        }
    }
    turnoActual=1;
    enCurso = true;
}

// Carga una partida desde el archivo en 'ruta'.
void Juego::cargarPartida(const char *ruta){
    ifstream in(ruta);
    if(!in.is_open()){cout<<"No se encontro "<<ruta<<"\n";menuDuranteJuego();}
    getline(in,n1);
    getline(in,n2);
    t1.cargar(in);
    t2.cargar(in);
    in>> b1 >> b2 >> turnoActual;
    in.close();
    cout<<"Partida cargada.\n";
    enCurso = true;
}

// Guarda la partida en el archivo en 'ruta'.
void Juego::guardarPartida(const char *ruta) const{
    ofstream out(ruta);
    out<<n1<<"\n"<<n2<<"\n";
    t1.guardar(out);t2.guardar(out);
    out<<b1<<' '<<b2<<' '<<turnoActual<<"\n";
    out.close();
    cout<<"Partida guardada.\n¡Gracias por jugar!";
}

// Muestra los tableros de ambos jugadores.
void Juego::mostrar() const{
    cout<<n1<<" (propio):\n";t1.mostrar(true);
    cout<<n2<<" (propio):\n";t2.mostrar(true);
}

// Realiza un turno del jugador actual. El jugador puede disparar o ir al menú.
void Juego::turno(){
    if(turnoActual == 1){
        cout<<"Turno de "<<n1<<" (escribe -1 -1 para ir al menu)\n";
        t2.mostrar(false);
        int f,c;
        std::cout << "Ejemplo: para disparar a la fila 3 y columna 5 escribe: 3 5\n";
        while(true){
            if(!readIntInRange(cin, f, -1, FILAS-1, true) || !readIntInRange(cin, c, -1, COLUMNAS-1, true)){
                std::cout << "Entrada incorrecta\n";
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        if(f == -1 && c == -1){menuDuranteJuego(); return; }
        bool hit = t2.dispararEn(f, c);
        if(hit){cout<<"¡Impacto!\n"; b2--; }else cout<<"Agua.\n";
        turnoActual = 2;
    }else{
        cout<<"Turno de "<<n2<<" (escribe -1 -1 para ir al menu)\n";
        t1.mostrar(false);
        int f, c;
        std::cout << "Ejemplo: para disparar a la fila 3 y columna 5 escribe: 3 5\n";
        while(true){
            if(!readIntInRange(cin, f, -1, FILAS-1, true) || !readIntInRange(cin, c, -1, COLUMNAS-1, true)){
                std::cout << "Entrada incorrecta\n";
                std::cin.clear(); std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            break;
        }
        if(f == -1 && c == -1){menuDuranteJuego();return;}
        bool hit = t1.dispararEn(f, c);
        if(hit){cout<<"¡Impacto!\n"; b1--;}else cout<<"Agua.\n";
        turnoActual = 1;
    }
}

// Verifica si el juego ha terminado. Si es así, anuncia el ganador.
bool Juego::finJuego() const{
    if(b1 == 0){
        cout<<n2<<" gana! (todos los barcos enemigos destruidos)\n";
        return true;
    }
    if(b2 == 0){
        cout<<n1<<" gana! (todos los barcos enemigos destruidos)\n";
        return true;
    }
    return false;
}

// Muestra el menú durante el juego, permitiendo iniciar una nueva partida,
// continuar una partida en curso o cargar una partida guardada, guardar y salir,
// o salir sin guardar.
void Juego::menuDuranteJuego(){
    cout<<"--- Menu ---\n1) Nueva Partida\n2) Continuar/Cargar Partida\n3) Guardar y salir\n4) Salir sin guardar\n";
    int op; cin >> op;
    if(op == 1) {
        cin.ignore();
        configurarJugadores();
        nuevaPartidaManual();
    }
    else if(op == 2) {
        if(enCurso) {
            cout << "Continuando partida en curso...\n";
            return;
        } else {
            ifstream test("partida_duelo.txt");
            if(test.is_open()) {
                test.close();
                cargarPartida("partida_duelo.txt");
            } else {
                cout << "No se encontro partida en curso ni guardada.\nIniciando nueva...\n";
                cin.ignore();
                configurarJugadores();
                nuevaPartidaManual();
            }
        }
    }
    else if(op == 3) {
        guardarPartida("partida_duelo.txt");
        exit(0);
    }
    else if(op == 4) {
        cout << "Saliendo sin guardar...\n";
        exit(0);
    }
}
