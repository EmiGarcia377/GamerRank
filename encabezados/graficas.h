#ifndef PIA_PROGRAMACION_ESTRUCTURADA_GRAFICAS_H
#define PIA_PROGRAMACION_ESTRUCTURADA_GRAFICAS_H

#ifdef __cplusplus
extern "C" {
#endif

void graficaBarrasPuntaje(const char usernames[][30],
                          int puntajes[], int n);
void graficaProgresoJugador(int puntajesPorPartida[],
                            int totalPartidas, const char *username);
void graficaWinratePorJuego(const char juegos[][40],
                             float winrates[], int n);
void graficaComparativaKD(const char usernames[][30],
                           float winrates[], int n);
#ifdef __cplusplus
}
#endif

#endif
