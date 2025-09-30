#include <iostream>
#include "juego.h"

#include <string>
#include <regex>
#include <limits>
#include <iostream>

// Lee un token de la entrada estándar y lo interpreta como un entero.
// Si la lectura falla o el token no es un entero válido, devuelve false
// y limpia la entrada estándar. Si la lectura es exitosa, almacena el
// valor en 'out' y devuelve true.
bool readIntToken(int &out){
    std::string tok; if(!(std::cin>>tok)) return false;
    std::regex re("^-?[0-9]+$");
    if(!std::regex_match(tok,re)) { 
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        std::cout<<"Entrada incorrecta\n"; 
        return false; 
    }
    try{ out = std::stoi(tok); 
        return true;
    } 
    catch(...){ 
        std::cout<<"Entrada incorrecta\n"; 
        return false; 
    }
}

using namespace std;

// Función principal que inicia el juego y maneja el flujo principal.
int main(){
    Juego j;
    cout<<"Astucia Naval\n";
    j.menuDuranteJuego();
    while(true){if(j.finJuego())break;j.turno();}
    cout<<"Fin del juego.\n";
    return 0;
}