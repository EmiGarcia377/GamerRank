#include "encabezados/main.h"
#include "encabezados/archivos.h"

int contador_id = 0;
int posicionActual = 0;
Jugador lista[100];
int ranking[100][2];
Jugador jugadorActivo;

int main(void) {

    cargarJugadores(lista, &contador_id);
    inicioSesion();

    return 0;
}
