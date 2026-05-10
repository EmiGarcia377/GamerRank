#include "encabezados/main.h"
#include "encabezados/jugadores.h"
#include "encabezados/archivos.h"
#include "encabezados/partidas.h"
#include "encabezados/graficas.h"

void inicioSesion() {
    int op = 0;

    printf("========== SISTEMA DE RANKINGS ==========\n");
    printf("========== INICIO DE SESION / REGISTRO ==========\n\n");

    do {

        printf("Ingrese algun metodo de registro: \n");
        printf("\t1) Iniciar sesion.\n");
        printf("\t2) Registrarte.\n");
        printf("\t3) Salir.\n");
        printf("Ingrese una opcion: ");
        scanf("%i", &op);

        switch (op) {
            case 1:
                if (cargarJugadorActual(&jugadorActivo, lista, &contador_id, buscarJugador(&jugadorActivo))) {
                    menuPrincipal();
                }
                break;
            case 2:
                crearNuevoJugador();
                break;
        }

    } while (op != 3);


}

void menuPrincipal() {
    char op;

    printf("========== SISTEMA DE RANKINGS ==========\n");
    printf("========== MENU PRINCIPAL ==========\n\n");

    do {

        printf("Ingrese alguna de las opciones para ingresar al submenu:\n");
        printf("\t(J) Jugadores\n");
        printf("\t(P) Partidas\n");
        printf("\t(R) Rankings\n");
        printf("\t(E) Estadisticas\n");
        printf("\t(S) Cerrar sesion.\n");
        printf("Ingrese alguna opcion: ");
        scanf(" %c", &op);

        switch (op) {
            case 'j':
            case 'J':
                menuJugadores();
                break;
            case 'p':
            case 'P':
                menuPartidas();
                break;
            case 'r':
            case 'R':
                menuRankings();
                break;
            case 'e':
            case 'E':
                menuEstadisticas();
                break;
            case 's':
            case 'S':
                return;
            default:
                printf("Ingrese una opcion valida para poder continuar.\n");
                break;
        }
    } while (op != 's' != op != 'S');
}

void menuJugadores() {
    int op;

    printf("========== SISTEMA DE RANKINGS ==========\n");
    printf("========== MENU DE JUGADORES ==========\n");

    do {

        printf("Ingrese alguna de las opciones para empezar: \n");
        printf("\t1) Ingresar nuevo usuario.\n");
        printf("\t2) Editar usuario.\n");
        printf("\t3) Eliminar usuario.\n");
        printf("\t4) Buscar jugador.\n");
        printf("\t5) Salir.\n");
        printf("Ingrese alguna opcion: ");
        scanf("%i", &op);

        switch (op) {
            case 1:
                crearNuevoJugador();
                break;
            case 2:
                editarJugador(&jugadorActivo, lista, &contador_id, buscarJugador(&jugadorActivo));
                break;
            case 3:
                eliminarJugador(lista, &contador_id, buscarJugador(&jugadorActivo));
                break;
            case 4:
                mostrarDatosJugador(buscarJugador(&jugadorActivo));
                break;
            case 5:
                return;
            default:
                printf("Ingrese una opcion valida.");
                break;

        }

    } while (op != 5);
}

void menuPartidas() {
    int op = 0;

    printf("========== SISTEMA DE RANKINGS ==========\n");
    printf("========== MENU DE PARTIDAS ==========\n\n");

    do {

        printf("Ingrese alguna de las opciones para empezar: \n");
        printf("\t1) Registrar nueva partida.\n");
        printf("\t2) Ver historial de partidas.\n");
        printf("\t3) Actualizar partida.\n");
        printf("\t4) Salir.\n");
        printf("Ingrese alguna opcion: ");
        scanf("%i", &op);

        switch (op) {
            case 1:
                registrarPartida(&jugadorActivo, lista, &contador_id, posicionActual);
                break;
            case 2:
                verHistorial(&jugadorActivo);
                break;
            case 3:
                editarPartida(&jugadorActivo, lista, &contador_id, posicionActual);
                break;
            case 4:
                return;
            default:
                printf("Ingrese una opcion valida.\n");
                break;
        }
    } while (op != 4);
}

void menuRankings() {
    int op = 0, tipo = 0;

    printf("========== SISTEMA DE RANKINGS ==========\n");
    printf("========== MENU DE RANKINGS ==========\n\n");

    do {
        printf("Ingrese alguna de las opciones para empezar: \n");
        printf("\t1) Ver ranking global.\n");
        printf("\t2) Ver ranking por juego.\n");
        printf("\t3) Ver ranking por pais.\n");
        printf("\t4) Ver top 10.\n");
        printf("\t5) Salir.\n");
        printf("Ingrese alguna opcion: ");
        scanf("%i", &op);

        if (op >= 1 && op <= 4) {
            printf("\nOrdenar por:\n");
            printf("1) Puntaje total\n");
            printf("2) Winrate\n");
            printf("3) Victorias\n");
            printf("Criterio: ");

            do {
                scanf("%d", &tipo);
                if (tipo < 1 || tipo > 3)
                    printf("Error: Elige un criterio entre 1 y 3: ");
            } while (tipo < 1 || tipo > 3);
        }

        switch (op) {
            case 1:
                mostrarRankingGlobal(lista, contador_id, tipo);
                break;
            case 2:
                mostrarRankingPorJuego(lista, contador_id, tipo);
                break;
            case 3:
                mostrarRankingPorPais(lista, contador_id, tipo);
                break;
            case 4:
                mostrarTop10(lista, contador_id, tipo);
                break;
            case 5:
                return;
            default:
                printf("Ingrese una opcion valida.\n");
                break;
        }
    } while (op != 5);
}

void menuGraficas(Jugador *jugador, Jugador lista[], int n) {
    int op;

    do {
        printf("\n=== GRAFICAS ===\n");
        printf("1) Barras de puntaje\n");
        printf("2) Progreso en el tiempo\n");
        printf("3) Winrate por juego\n");
        printf("4) Comparativa winrate\n");
        printf("5) Volver\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1: {
                char usernames[100][30];
                int puntajes[100];
                for (int i = 0; i < n; i++) {
                    strcpy(usernames[i], lista[i].username);
                    puntajes[i] = lista[i].stats.puntaje_total;
                }
                graficaBarrasPuntaje(usernames, puntajes, n);
                break;
            }
            case 2: {
                int puntajesPorPartida[50];
                for (int i = 0; i < jugador->hist.total_partidas; i++)
                    puntajesPorPartida[i] = jugador->hist.partidas[i].puntos;
                graficaProgresoJugador(puntajesPorPartida,
                                       jugador->hist.total_partidas,
                                       jugador->username);
                break;
            }
            case 3: {
                char juegos[50][40];
                float winrates[50];
                int totalJuegos = 0;

                for (int i = 0; i < jugador->hist.total_partidas; i++) {
                    char *juego = jugador->hist.partidas[i].juego;
                    int encontrado = 0;

                    for (int j = 0; j < totalJuegos; j++) {
                        if (strcmp(juegos[j], juego) == 0) {
                            encontrado = 1;
                            break;
                        }
                    }

                    if (!encontrado) {
                        strcpy(juegos[totalJuegos], juego);
                        int victorias = 0, partidas = 0;
                        for (int k = 0; k < jugador->hist.total_partidas; k++) {
                            if (strcmp(jugador->hist.partidas[k].juego, juego) == 0) {
                                partidas++;
                                if (jugador->hist.partidas[k].victoria)
                                    victorias++;
                            }
                        }
                        winrates[totalJuegos] = (float)victorias / partidas * 100;
                        totalJuegos++;
                    }
                }
                graficaWinratePorJuego(juegos, winrates, totalJuegos);
                break;
            }
            case 4: {
                char usernames[100][30];
                float winrates[100];
                for (int i = 0; i < n; i++) {
                    strcpy(usernames[i], lista[i].username);
                    winrates[i] = lista[i].stats.winrate;
                }
                graficaComparativaKD(usernames, winrates, n);
                break;
            }
            case 5:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (op != 5);
}

void menuEstadisticas() {
    int op;

    do {
        printf("\n=== ESTADISTICAS ===\n");
        printf("1) Ver mis estadisticas\n");
        printf("2) Graficas\n");
        printf("3) Rendimiento general\n");
        printf("4) Generar reporte ranking global\n");
        printf("5) Generar reporte de estadisticas personales.\n");
        printf("6) Ver reporte ranking global\n");
        printf("7) Ver reporte de estadisticas personales.\n");
        printf("8) Volver al menu principal\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                mostrarEstadisticasJugador(&jugadorActivo, lista, contador_id);
                break;
            case 2:
                menuGraficas(&jugadorActivo, lista, contador_id);
                break;
            case 3:
                mostrarRendimientoGeneral(lista, contador_id);
                break;
            case 4:
                generarReporteTxt(lista, contador_id);
                break;
            case 5:
                generarReporteJugador(&jugadorActivo);
                break;
            case 6:
                mostrarReporteTxt("ranking.txt");
                break;
            case 7: {
                char nombreArchivo[50];
                sprintf(nombreArchivo, "reporte_%s.txt", jugadorActivo.username);
                mostrarReporteTxt(nombreArchivo);
                break;
            }
            case 8:
                printf("Volviendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (op != 8);
}