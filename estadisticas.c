#include "encabezados/main.h"

void calcularPromedios(Jugador lista[], int n, float *promPuntaje,
                       float *promWinrate, float *promVictorias) {
    if (n == 0) {
        *promPuntaje = 0;
        *promWinrate = 0;
        *promVictorias = 0;
        return;
    }

    float totalPuntaje = 0, totalWinrate = 0, totalVictorias = 0;

    for (int i = 0; i < n; i++) {
        totalPuntaje   += lista[i].stats.puntaje_total;
        totalWinrate   += lista[i].stats.winrate;
        totalVictorias += lista[i].stats.victorias;
    }

    *promPuntaje   = totalPuntaje   / n;
    *promWinrate   = totalWinrate   / n;
    *promVictorias = totalVictorias / n;
}

void mostrarEstadisticasJugador(Jugador *jugador, Jugador lista[], int n) {
    float promPuntaje, promWinrate, promVictorias;
    calcularPromedios(lista, n, &promPuntaje, &promWinrate, &promVictorias);

    printf("\n=== ESTADISTICAS: %s ===\n", jugador->username);
    printf("Rango actual    : %s (Nivel %d)\n",
           jugador->stats.rango_actual.nombre,
           jugador->stats.rango_actual.nivel);
    printf("Partidas jugadas: %d\n",   jugador->stats.partidas_jugadas);
    printf("Victorias       : %d\n",   jugador->stats.victorias);
    printf("Winrate         : %.1f%%\n", jugador->stats.winrate);
    printf("Puntaje total   : %d\n",   jugador->stats.puntaje_total);

    printf("\n--- COMPARACION CON EL PROMEDIO GLOBAL ---\n");
    printf("%-20s %-15s %-15s %-10s\n",
           "Categoria", "Tu valor", "Promedio", "Estado");
    printf("%-20s %-15s %-15s %-10s\n",
           "--------------------", "---------------",
           "---------------", "----------");

    printf("%-20s %-15d %-15.1f %-10s\n",
           "Puntaje total",
           jugador->stats.puntaje_total,
           promPuntaje,
           jugador->stats.puntaje_total >= promPuntaje ?
           "SOBRE" : "BAJO");

    printf("%-20s %-14.1f%% %-14.1f%% %-10s\n",
           "Winrate",
           jugador->stats.winrate,
           promWinrate,
           jugador->stats.winrate >= promWinrate ?
           "SOBRE" : "BAJO");

    printf("%-20s %-15d %-15.1f %-10s\n",
           "Victorias",
           jugador->stats.victorias,
           promVictorias,
           jugador->stats.victorias >= promVictorias ?
           "SOBRE" : "BAJO");

    int sobrePromedio = 0;
    if (jugador->stats.puntaje_total >= promPuntaje) sobrePromedio++;
    if (jugador->stats.winrate       >= promWinrate) sobrePromedio++;
    if (jugador->stats.victorias     >= promVictorias) sobrePromedio++;

    printf("\n");
    if (sobrePromedio == 3) {
        printf("Calificacion: EXCELENTE - Estas por encima del promedio en todo!\n");
    } else if (sobrePromedio == 2) {
        printf("Calificacion: BUENO - Estas por encima del promedio en 2 de 3 categorias.\n");
    } else if (sobrePromedio == 1) {
        printf("Calificacion: REGULAR - Solo superas el promedio en 1 categoria.\n");
    } else {
        printf("Calificacion: POR MEJORAR - Estas por debajo del promedio en todo.\n");
    }
}

void mostrarRendimientoGeneral(Jugador lista[], int n) {
    if (n == 0) {
        printf("No hay jugadores registrados.\n");
        return;
    }

    float promPuntaje, promWinrate, promVictorias;
    calcularPromedios(lista, n, &promPuntaje, &promWinrate, &promVictorias);

    int idxMejorPuntaje = 0, idxMejorWinrate = 0, idxMejorVictorias = 0;

    for (int i = 1; i < n; i++) {
        if (lista[i].stats.puntaje_total > lista[idxMejorPuntaje].stats.puntaje_total)
            idxMejorPuntaje = i;
        if (lista[i].stats.winrate > lista[idxMejorWinrate].stats.winrate)
            idxMejorWinrate = i;
        if (lista[i].stats.victorias > lista[idxMejorVictorias].stats.victorias)
            idxMejorVictorias = i;
    }

    printf("\n=== RENDIMIENTO GENERAL DEL SISTEMA ===\n");
    printf("Total jugadores registrados: %d\n\n", n);

    printf("--- PROMEDIOS GLOBALES ---\n");
    printf("Puntaje promedio : %.1f\n", promPuntaje);
    printf("Winrate promedio : %.1f%%\n", promWinrate);
    printf("Victorias prom.  : %.1f\n\n", promVictorias);

    printf("--- MEJORES JUGADORES ---\n");
    printf("Mayor puntaje  : %-20s (%d pts)\n",
           lista[idxMejorPuntaje].username,
           lista[idxMejorPuntaje].stats.puntaje_total);
    printf("Mayor winrate  : %-20s (%.1f%%)\n",
           lista[idxMejorWinrate].username,
           lista[idxMejorWinrate].stats.winrate);
    printf("Mas victorias  : %-20s (%d victorias)\n",
           lista[idxMejorVictorias].username,
           lista[idxMejorVictorias].stats.victorias);

    int sobreProm = 0, bajoProm = 0;
    for (int i = 0; i < n; i++) {
        if (lista[i].stats.puntaje_total >= promPuntaje)
            sobreProm++;
        else
            bajoProm++;
    }

    printf("\nJugadores sobre promedio: %d (%.1f%%)\n",
           sobreProm, (float)sobreProm / n * 100);
    printf("Jugadores bajo promedio : %d (%.1f%%)\n",
           bajoProm, (float)bajoProm / n * 100);
}