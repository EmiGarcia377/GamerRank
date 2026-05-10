#include <stdlib.h>

#include "encabezados/main.h"
#include "encabezados/validadores.h"

void actualizarRango(Estadisticas *stats) {
    int puntos = stats->puntaje_total;

    if (puntos < 500) {
        strcpy(stats->rango_actual.nombre, "Bronce");
        stats->rango_actual.nivel = 1;
        stats->rango_actual.puntos_min = 0;
        stats->rango_actual.puntos_max = 499;
    } else if (puntos < 1500) {
        strcpy(stats->rango_actual.nombre, "Plata");
        stats->rango_actual.nivel = 2;
        stats->rango_actual.puntos_min = 500;
        stats->rango_actual.puntos_max = 1499;
    } else if (puntos < 3000) {
        strcpy(stats->rango_actual.nombre, "Oro");
        stats->rango_actual.nivel = 3;
        stats->rango_actual.puntos_min = 1500;
        stats->rango_actual.puntos_max = 2999;
    } else if (puntos < 5000) {
        strcpy(stats->rango_actual.nombre, "Platino");
        stats->rango_actual.nivel = 4;
        stats->rango_actual.puntos_min = 3000;
        stats->rango_actual.puntos_max = 4999;
    } else {
        strcpy(stats->rango_actual.nombre, "Diamante");
        stats->rango_actual.nivel = 5;
        stats->rango_actual.puntos_min = 5000;
        stats->rango_actual.puntos_max = 99999;
    }
}

void actualizarEstadisticas(Jugador *jugador, Partida *nueva) {
    jugador->stats.partidas_jugadas++;
    jugador->stats.puntaje_total += nueva->puntos;

    if (nueva->victoria)
        jugador->stats.victorias++;

    jugador->stats.winrate = (float)jugador->stats.victorias /
                              jugador->stats.partidas_jugadas * 100.0;

    actualizarRango(&jugador->stats);
}

void registrarPartida(Jugador *jugador, Jugador lista[], int *n, int pos) {
    if (jugador->hist.total_partidas >= 50) {
        printf("Error: Historial lleno, maximo 50 partidas.\n");
        return;
    }

    Partida nueva;
    char victoria[4];

    nueva.id_partida = jugador->hist.total_partidas + 1;

    do {
        printf("Nombre del juego: ");
        scanf(" %39[^\n]", nueva.juego);
    } while (!validarCadena(nueva.juego));

    char puntosStr[10];
    do {
        printf("Puntos obtenidos: ");
        scanf("%9s", puntosStr);
    } while (!validarPuntos(puntosStr));
    nueva.puntos = atoi(puntosStr);

    do {
        printf("Victoria? (s/n): ");
        scanf("%3s", victoria);
        if (strcmp(victoria, "s") != 0 && strcmp(victoria, "S") != 0 &&
            strcmp(victoria, "n") != 0 && strcmp(victoria, "N") != 0)
            printf("Error: Ingresa 's' para victoria o 'n' para derrota.\n");
    } while (strcmp(victoria, "s") != 0 && strcmp(victoria, "S") != 0 &&
             strcmp(victoria, "n") != 0 && strcmp(victoria, "N") != 0);

    nueva.victoria = (strcmp(victoria, "s") == 0 || strcmp(victoria, "S") == 0);

    jugador->hist.partidas[jugador->hist.total_partidas] = nueva;
    jugador->hist.total_partidas++;

    actualizarEstadisticas(jugador, &nueva);

    lista[pos] = *jugador;
    FILE *archivo = fopen("jugadores.dat", "r+b");
    if (archivo != NULL) {
        fseek(archivo, pos * sizeof(Jugador), SEEK_SET);
        fwrite(jugador, sizeof(Jugador), 1, archivo);
        fclose(archivo);
    }

    printf("Partida registrada correctamente.\n");
}

void verHistorial(Jugador *jugador) {
    if (jugador->hist.total_partidas == 0) {
        printf("No tienes partidas registradas.\n");
        return;
    }

    printf("\n=== HISTORIAL DE PARTIDAS: %s ===\n", jugador->username);
    printf("%-5s %-20s %-10s %-10s\n", "ID", "Juego", "Puntos", "Resultado");
    printf("%-5s %-20s %-10s %-10s\n", "---", "--------------------", "----------", "----------");

    for (int i = 0; i < jugador->hist.total_partidas; i++) {
        Partida p = jugador->hist.partidas[i];
        printf("%-5d %-20s %-10d %-10s\n",
            p.id_partida,
            p.juego,
            p.puntos,
            p.victoria ? "Victoria" : "Derrota");
    }

    printf("\nTotal partidas : %d\n", jugador->stats.partidas_jugadas);
    printf("Victorias      : %d\n", jugador->stats.victorias);
    printf("Winrate        : %.1f%%\n", jugador->stats.winrate);
    printf("Puntaje total  : %d\n", jugador->stats.puntaje_total);
    printf("Rango actual   : %s\n", jugador->stats.rango_actual.nombre);
}

void recalcularEstadisticas(Jugador *jugador) {
    jugador->stats.partidas_jugadas = 0;
    jugador->stats.victorias = 0;
    jugador->stats.puntaje_total = 0;
    jugador->stats.winrate = 0.0;

    for (int i = 0; i < jugador->hist.total_partidas; i++) {
        jugador->stats.partidas_jugadas++;
        jugador->stats.puntaje_total += jugador->hist.partidas[i].puntos;
        if (jugador->hist.partidas[i].victoria)
            jugador->stats.victorias++;
    }

    if (jugador->stats.partidas_jugadas > 0)
        jugador->stats.winrate = (float)jugador->stats.victorias /
                                  jugador->stats.partidas_jugadas * 100.0;

    actualizarRango(&jugador->stats);
}

void editarPartida(Jugador *jugador, Jugador lista[], int *n, int pos) {
    if (jugador->hist.total_partidas == 0) {
        printf("No tienes partidas registradas.\n");
        return;
    }

    verHistorial(jugador);

    int idPartida;
    do {
        printf("\nIngresa el ID de la partida a editar (1-%d): ",
                jugador->hist.total_partidas);
        scanf("%d", &idPartida);
        if (idPartida < 1 || idPartida > jugador->hist.total_partidas)
            printf("Error: ID invalido, ingresa un numero entre 1 y %d.\n",
                    jugador->hist.total_partidas);
    } while (idPartida < 1 || idPartida > jugador->hist.total_partidas);

    int idx = idPartida - 1;
    Partida *p = &jugador->hist.partidas[idx];
    int opcion;

    do {
        printf("\n=== EDITAR PARTIDA #%d ===\n", p->id_partida);
        printf("1. Cambiar juego     [actual: %s]\n", p->juego);
        printf("2. Cambiar puntos    [actual: %d]\n", p->puntos);
        printf("3. Cambiar resultado [actual: %s]\n",
                p->victoria ? "Victoria" : "Derrota");
        printf("4. Guardar cambios\n");
        printf("5. Cancelar\n");
        printf("Opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {
                char nuevoJuego[40];
                do {
                    printf("Nuevo nombre del juego: ");
                    scanf(" %39[^\n]", nuevoJuego);
                } while (!validarCadena(nuevoJuego));
                strcpy(p->juego, nuevoJuego);
                printf("Juego actualizado.\n");
                break;
            }
            case 2: {
                int nuevosPuntos;
                do {
                    printf("Nuevos puntos: ");
                    scanf("%d", &nuevosPuntos);
                    if (nuevosPuntos < 0)
                        printf("Error: Los puntos no pueden ser negativos.\n");
                } while (nuevosPuntos < 0);
                p->puntos = nuevosPuntos;
                printf("Puntos actualizados.\n");
                break;
            }
            case 3: {
                char victoria[4];
                do {
                    printf("Victoria? (s/n): ");
                    scanf("%3s", victoria);
                    if (strcmp(victoria, "s") != 0 && strcmp(victoria, "S") != 0 &&
                        strcmp(victoria, "n") != 0 && strcmp(victoria, "N") != 0)
                        printf("Error: Ingresa 's' para victoria o 'n' para derrota.\n");
                } while (strcmp(victoria, "s") != 0 && strcmp(victoria, "S") != 0 &&
                         strcmp(victoria, "n") != 0 && strcmp(victoria, "N") != 0);
                p->victoria = (strcmp(victoria, "s") == 0 ||
                               strcmp(victoria, "S") == 0);
                printf("Resultado actualizado.\n");
                break;
            }
            case 4: {
                recalcularEstadisticas(jugador);

                lista[pos] = *jugador;
                FILE *archivo = fopen("jugadores.dat", "r+b");
                if (archivo != NULL) {
                    fseek(archivo, pos * sizeof(Jugador), SEEK_SET);
                    fwrite(jugador, sizeof(Jugador), 1, archivo);
                    fclose(archivo);
                }
                printf("Cambios guardados correctamente.\n");
                break;
            }
            case 5:
                printf("Edicion cancelada.\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 4 && opcion != 5);
}

void ordenarRanking(Jugador lista[], int n, int tipo) {
    Jugador temp;
    int i, j;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            int intercambiar = 0;

            switch (tipo) {
                case 1:
                    if (lista[j].stats.puntaje_total < lista[j+1].stats.puntaje_total)
                        intercambiar = 1;
                    break;
                case 2:
                    if (lista[j].stats.winrate < lista[j+1].stats.winrate)
                        intercambiar = 1;
                    break;
                case 3:
                    if (lista[j].stats.victorias < lista[j+1].stats.victorias)
                        intercambiar = 1;
                    break;
            }

            if (intercambiar) {
                temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void mostrarRankingGlobal(Jugador lista[], int n, int tipo) {
    if (n == 0) {
        printf("No hay jugadores registrados.\n");
        return;
    }

    Jugador copia[100];
    for (int i = 0; i < n; i++)
        copia[i] = lista[i];

    ordenarRanking(copia, n, tipo);

    char *tipoNombre;
    switch (tipo) {
        case 1: tipoNombre = "Puntaje Total";    break;
        case 2: tipoNombre = "Winrate";          break;
        case 3: tipoNombre = "Victorias";        break;
        default: tipoNombre = "Puntaje Total";   break;
    }

    printf("\n=== RANKING GLOBAL POR %s ===\n", tipoNombre);
    printf("%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "Pos", "Username", "Puntaje", "Winrate", "Victorias", "Rango");
    printf("%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "---", "--------------------", "-------",
           "-------", "---------", "-----");

    for (int i = 0; i < n; i++) {
        printf("%-5d %-20s %-10d %-9.1f%% %-10d %-10s\n",
               i + 1,
               copia[i].username,
               copia[i].stats.puntaje_total,
               copia[i].stats.winrate,
               copia[i].stats.victorias,
               copia[i].stats.rango_actual.nombre);
    }
}

void mostrarRankingPorPais(Jugador lista[], int n, int tipo) {
    char pais[30];

    do {
        printf("Ingresa el pais a consultar: ");
        scanf(" %29[^\n]", pais);
    } while (!validarPais(pais));

    Jugador filtrados[100];
    int total = 0;

    for (int i = 0; i < n; i++) {
        if (strcmp(lista[i].pais, pais) == 0) {
            filtrados[total] = lista[i];
            total++;
        }
    }

    if (total == 0) {
        printf("No hay jugadores registrados de '%s'.\n", pais);
        return;
    }

    ordenarRanking(filtrados, total, tipo);

    printf("\n=== RANKING POR PAIS: %s ===\n", pais);
    printf("%-5s %-20s %-10s %-10s %-10s\n",
           "Pos", "Username", "Puntaje", "Winrate", "Victorias");
    printf("%-5s %-20s %-10s %-10s %-10s\n",
           "---", "--------------------", "-------", "-------", "---------");

    for (int i = 0; i < total; i++) {
        printf("%-5d %-20s %-10d %-9.1f%% %-10d\n",
               i + 1,
               filtrados[i].username,
               filtrados[i].stats.puntaje_total,
               filtrados[i].stats.winrate,
               filtrados[i].stats.victorias);
    }
}

void mostrarRankingPorJuego(Jugador lista[], int n, int tipo) {
    char juego[40];

    do {
        printf("Ingresa el nombre del juego: ");
        scanf(" %39[^\n]", juego);
    } while (!validarCadena(juego));

    Jugador filtrados[100];
    int puntajesPorJuego[100];
    int victoriasPorJuego[100];
    int partidasPorJuego[100];
    int total = 0;

    for (int i = 0; i < n; i++) {
        int puntaje = 0, victorias = 0, partidas = 0;

        for (int j = 0; j < lista[i].hist.total_partidas; j++) {
            if (strcmp(lista[i].hist.partidas[j].juego, juego) == 0) {
                puntaje += lista[i].hist.partidas[j].puntos;
                if (lista[i].hist.partidas[j].victoria) victorias++;
                partidas++;
            }
        }

        if (partidas > 0) {
            filtrados[total] = lista[i];
            puntajesPorJuego[total] = puntaje;
            victoriasPorJuego[total] = victorias;
            partidasPorJuego[total] = partidas;
            total++;
        }
    }

    if (total == 0) {
        printf("No hay jugadores con partidas en '%s'.\n", juego);
        return;
    }

    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (puntajesPorJuego[j] < puntajesPorJuego[j+1]) {
                Jugador tempJ = filtrados[j];
                filtrados[j] = filtrados[j+1];
                filtrados[j+1] = tempJ;

                int tempP = puntajesPorJuego[j];
                puntajesPorJuego[j] = puntajesPorJuego[j+1];
                puntajesPorJuego[j+1] = tempP;

                int tempV = victoriasPorJuego[j];
                victoriasPorJuego[j] = victoriasPorJuego[j+1];
                victoriasPorJuego[j+1] = tempV;

                int tempPart = partidasPorJuego[j];
                partidasPorJuego[j] = partidasPorJuego[j+1];
                partidasPorJuego[j+1] = tempPart;
            }
        }
    }

    printf("\n=== RANKING POR JUEGO: %s ===\n", juego);
    printf("%-5s %-20s %-10s %-10s %-10s\n",
           "Pos", "Username", "Puntaje", "Victorias", "Partidas");
    printf("%-5s %-20s %-10s %-10s %-10s\n",
           "---", "--------------------", "-------", "---------", "--------");

    for (int i = 0; i < total; i++) {
        printf("%-5d %-20s %-10d %-10d %-10d\n",
               i + 1,
               filtrados[i].username,
               puntajesPorJuego[i],
               victoriasPorJuego[i],
               partidasPorJuego[i]);
    }
}

void mostrarTop10(Jugador lista[], int n, int criterio) {
    if (n == 0) {
        printf("No hay jugadores registrados.\n");
        return;
    }

    Jugador copia[100];
    for (int i = 0; i < n; i++)
        copia[i] = lista[i];

    ordenarRanking(copia, n, criterio);

    int limite = n < 10 ? n : 10;

    printf("\n=== TOP %d JUGADORES ===\n", limite);
    printf("%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "Pos", "Username", "Puntaje", "Winrate", "Victorias", "Rango");
    printf("%-5s %-20s %-10s %-10s %-10s %-10s\n",
           "---", "--------------------", "-------",
           "-------", "---------", "-----");

    for (int i = 0; i < limite; i++) {
        printf("%-5d %-20s %-10d %-9.1f%% %-10d %-10s\n",
               i + 1,
               copia[i].username,
               copia[i].stats.puntaje_total,
               copia[i].stats.winrate,
               copia[i].stats.victorias,
               copia[i].stats.rango_actual.nombre);
    }
}