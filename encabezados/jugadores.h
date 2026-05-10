#ifndef PIA_PROGRAMACION_ESTRUCTURADA_JUGADORES_H
#define PIA_PROGRAMACION_ESTRUCTURADA_JUGADORES_H

bool cargarJugadorActual(Jugador *jugador, Jugador lista[], int *n, int pos);
void crearNuevoJugador();
void mostrarDatosJugador(int pos);
void editarJugador(Jugador *jugador, Jugador lista[], int *n, int pos);
void eliminarJugador(Jugador lista[], int *n, int pos);
void calcularPromedios(Jugador lista[], int n, float *promPuntaje, float *promWinrate, float *promVictorias);
void mostrarEstadisticasJugador(Jugador *jugador, Jugador lista[], int n);
void mostrarRendimientoGeneral(Jugador lista[], int n);


#endif
