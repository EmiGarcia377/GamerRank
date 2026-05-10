#ifndef PIA_PROGRAMACION_ESTRUCTURADA_ARCHIVOS_H
#define PIA_PROGRAMACION_ESTRUCTURADA_ARCHIVOS_H

void cargarJugadores(Jugador lista[], int *n);
void guardarJugador(Jugador *jugador, int *n);
int buscarJugador(Jugador *encontrado);
void generarReporteTxt(Jugador lista[], int n);
void generarReporteJugador(Jugador *jugador);
void mostrarReporteTxt(char *nombreArchivo);

#endif
