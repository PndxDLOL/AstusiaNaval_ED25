# ⚓ Astucia Naval - V2

Bienvenido a **Astucia Naval**, un juego de estrategia por turnos para dos jugadores inspirado en el clásico *Batalla Naval*.  

---

## 🚀 Ejecutar el juego
En la carpeta del proyecto se encuentra un archivo ejecutable llamado **`astucia_naval_v2.exe`**.  

Puedes iniciarlo de dos formas:

- **Con doble click** sobre el archivo.  
- **Desde la terminal/cmd**:
  ```bash
  ./astucia_naval_v2.exe

Características:
- Este es un juego para dos jugadores 
- Cada jugador ingresa su nombre.
- Colocación manual de barcos con instrucciones y ejemplos de coordenadas (barcos de tamaño 3, 2, 2/Fijos por ahora).
- Turnos alternos con instrucciones claras en las coordenadas para disparar.
- Menú disponible en cualquier turno (ingresando -1 -1):
  1) Nueva Partida
  2) Continuar/cargar Partida (Si encuentra partida guardada, carga. En caso que no, inicia una partida nueva)
  3) Guardar y salir( Guardado: archivo `partida_duelo.txt`)
  4) Salir sin guardar

## Reglas del Juego

  1) Cada jugador coloca sus barcos en el tablero indicando fila, columna y orientación (H = Horizontal, V = Vertical).
  2) Los barcos no se pueden solapar ni salir del tablero.
  3) En cada turno, un jugador dispara a una casilla del tablero enemigo y nos indica:
      * Si impacta 🎯
      * Si falla 🌊
  4) Gana el jugador que logre hundir todos los barcos enemigos.


## Ejemplo colocar barco
Coloca barco de tamaño 3
Ingresa fila (0-7), columna (0-7) y orientación (H=Horizontal, V=Vertical)
Ejemplo: `2 3 H`  → coloca un barco de 3 casillas desde (2,3) hacia la derecha.

## Ejemplo disparar
Turno de Juan
Ingresa fila y columna donde quieres disparar
Ejemplo: `4 5`  → disparas al casillero (4,5).
