# Astucia Naval - V2

Características:
- Cada jugador ingresa su nombre.
- Colocación manual de barcos con instrucciones y ejemplos de coordenadas (barcos de tamaño 3, 2, 2/Fijos por ahora).
- Turnos alternos con instrucciones claras en las coordenadas para disparar.
- Opción de menú en cualquier turno (-1 -1) para:
  1) Nueva Partida
  2) Continuar/cargar Partida (Si encuentra partida guardada, carga. En caso que no, inicia una partida nueva)
  3) Guardar y salir( Guardado: archivo `partida_duelo.txt`)
  4) Salir sin guardar


## Ejemplo colocar barco
Coloca barco de tamaño 3
Ingresa fila (0-7), columna (0-7) y orientación (H=Horizontal, V=Vertical)
Ejemplo: `2 3 H`  → coloca un barco de 3 casillas desde (2,3) hacia la derecha.

## Ejemplo disparar
Turno de Juan
Ingresa fila y columna donde quieres disparar
Ejemplo: `4 5`  → disparas al casillero (4,5).
