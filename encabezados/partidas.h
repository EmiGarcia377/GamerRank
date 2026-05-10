#ifndef PIA_PROGRAMACION_ESTRUCTURADA_PARTIDAS_H
#define PIA_PROGRAMACION_ESTRUCTURADA_PARTIDAS_H

void registrarPartida(Jugador *jugador, Jugador lista[], int *n, int pos);
void actualizarEstadisticas(Jugador *jugador, Partida *nueva);
void actualizarRango(Estadisticas *stats);
void verHistorial(Jugador *jugador);
void editarPartida(Jugador *jugador, Jugador lista[], int *n, int pos);
void mostrarRankingGlobal(Jugador lista[], int n, int tipo);
void mostrarRankingPorPais(Jugador lista[], int n, int tipo);
void mostrarRankingPorJuego(Jugador lista[], int n, int tipo);
void mostrarTop10(Jugador lista[], int n, int tipo);
void ordenarRanking(Jugador lista[], int n, int tipo);

#endif
