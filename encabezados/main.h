#ifndef PIA_PROGRAMACION_ESTRUCTURADA_MAIN_H
#define PIA_PROGRAMACION_ESTRUCTURADA_MAIN_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    char nombre[20];
    int puntos_min;
    int puntos_max;
    int nivel;
} Rango;

typedef struct{
    int id_partida;
    char juego[40];
    int puntos;
    bool victoria;
} Partida;

typedef struct {
    Partida partidas[50];
    int total_partidas;
    char juego[40];
    char fecha[12];
    int puntos_ganados;
    bool victoria;
} Historial;

typedef struct {
    int partidas_jugadas;
    int victorias;
    float kd_ratio;
    int puntaje_total;
    float winrate;
    Rango rango_actual;
} Estadisticas;

typedef struct {
    int id_jugador;
    char username[30];
    char email[50];
    char pais[30];
    Estadisticas stats;
    Historial hist;
} Jugador;

extern Jugador lista[100];
extern int contador_id;
extern int posicionActual;
extern int ranking[100][2];
extern Jugador jugadorActivo;

void inicioSesion();
void menuPrincipal();
void menuJugadores();
void menuPartidas();
void menuRankings();
void menuEstadisticas();
void ingresarJugador();
void crearNuevoJugador();
bool validarUsername(char *username);
void mostrarDatosJugador(int pos);

#endif
