#include "encabezados/main.h"
#include "encabezados/partidas.h"
#include "encabezados/jugadores.h"

void cargarJugadores(Jugador lista[], int *n) {
    FILE *archivo = fopen("jugadores.dat", "rb");

    if (archivo == NULL) {
        printf("Archivo 'jugadores.dat' no encontrado.\n\n");
        *n = 0;
        return;
    };

    *n = 0;

    while (fread(&lista[*n], sizeof(Jugador), 1, archivo)) {
        (*n)++;
        if (*n >= 100) break;
    }

    fclose(archivo);

    printf("¡Archivo 'jugadores.dat' cargado correctamente!\n\n");
}

void guardarJugador(Jugador *jugador, int *n) {

    FILE *archivo;

    archivo = fopen("jugadores.dat", "ab");

    if (archivo == NULL) {
        archivo = fopen("jugadores.dat", "wb");
        if (archivo == NULL) {
            printf("No se pudo abrir el archivo 'jugadores.dat'.\n");
            return;
        }
    }

    memset(&jugador->hist, 0, sizeof(jugador->hist));
    memset(&jugador->stats, 0, sizeof(jugador->stats));

    fwrite(jugador, sizeof(*jugador), 1, archivo);
    fclose(archivo);
    (*n)++;

    printf("\nJugador '%s' registrado exitosamente.\n\n", jugador->username);

}

int buscarJugador(Jugador *encontrado) {
    char username[30];

    do {
        printf("Ingrese el nombre del usuario a buscar: ");
        scanf("%29s", username);

    } while (!validarUsername(username));

    for (int i = 0; i < contador_id; i++) {
        if (strcmp(lista[i].username, username) == 0) {
            *encontrado = lista[i];
            posicionActual = i;
            return i;
        }
    }
    return -1;
}

void generarReporteTxt(Jugador lista[], int n) {
    if (n == 0) {
        printf("No hay jugadores registrados.\n");
        return;
    }

    Jugador copia[100];
    for (int i = 0; i < n; i++)
        copia[i] = lista[i];
    ordenarRanking(copia, n, 1);

    FILE *archivo = fopen("ranking.txt", "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo ranking.txt\n");
        return;
    }

    fprintf(archivo, "========================================");
    fprintf(archivo, "========================================\n");
    fprintf(archivo, "%-10s %-20s %-10s %-10s %-10s %-10s\n",
            "Posicion", "Username", "Puntaje", "Winrate",
            "Victorias", "Rango");
    fprintf(archivo, "========================================");
    fprintf(archivo, "========================================\n");

    for (int i = 0; i < n; i++) {
        fprintf(archivo, "%-10d %-20s %-10d %-9.1f%% %-10d %-10s\n",
                i + 1,
                copia[i].username,
                copia[i].stats.puntaje_total,
                copia[i].stats.winrate,
                copia[i].stats.victorias,
                copia[i].stats.rango_actual.nombre);
    }

    float promPuntaje, promWinrate, promVictorias;
    calcularPromedios(lista, n, &promPuntaje, &promWinrate, &promVictorias);

    fprintf(archivo, "========================================");
    fprintf(archivo, "========================================\n");
    fprintf(archivo, "%-10s %-20s %-10.1f %-9.1f%% %-10.1f\n",
            "PROMEDIO", "---", promPuntaje, promWinrate, promVictorias);
    fprintf(archivo, "========================================");
    fprintf(archivo, "========================================\n");

    fclose(archivo);
    printf("Reporte ranking.txt generado correctamente.\n");
}

void generarReporteJugador(Jugador *jugador) {
    char nombreArchivo[50];
    sprintf(nombreArchivo, "reporte_%s.txt", jugador->username);

    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo crear el archivo %s\n", nombreArchivo);
        return;
    }

    fprintf(archivo, "========================================\n");
    fprintf(archivo, "   REPORTE DE JUGADOR: %s\n", jugador->username);
    fprintf(archivo, "========================================\n\n");

    fprintf(archivo, "--- DATOS GENERALES ---\n");
    fprintf(archivo, "Username : %s\n", jugador->username);
    fprintf(archivo, "Pais     : %s\n", jugador->pais);
    fprintf(archivo, "Email    : %s\n\n", jugador->email);

    fprintf(archivo, "--- ESTADISTICAS ---\n");
    fprintf(archivo, "Rango          : %s (Nivel %d)\n",
            jugador->stats.rango_actual.nombre,
            jugador->stats.rango_actual.nivel);
    fprintf(archivo, "Partidas       : %d\n",
            jugador->stats.partidas_jugadas);
    fprintf(archivo, "Victorias      : %d\n",
            jugador->stats.victorias);
    fprintf(archivo, "Winrate        : %.1f%%\n",
            jugador->stats.winrate);
    fprintf(archivo, "Puntaje total  : %d\n\n",
            jugador->stats.puntaje_total);

    fprintf(archivo, "--- HISTORIAL DE PARTIDAS ---\n");
    fprintf(archivo, "%-5s %-20s %-10s %-10s\n",
            "ID", "Juego", "Puntos", "Resultado");
    fprintf(archivo, "%-5s %-20s %-10s %-10s\n",
            "---", "--------------------",
            "----------", "----------");

    for (int i = 0; i < jugador->hist.total_partidas; i++) {
        Partida p = jugador->hist.partidas[i];
        fprintf(archivo, "%-5d %-20s %-10d %-10s\n",
                p.id_partida,
                p.juego,
                p.puntos,
                p.victoria ? "Victoria" : "Derrota");
    }

    fprintf(archivo, "========================================\n");

    fclose(archivo);
    printf("Reporte %s generado correctamente.\n", nombreArchivo);
}

void mostrarReporteTxt(char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");

    if (archivo == NULL) {
        printf("Error: El archivo '%s' no existe.\n", nombreArchivo);
        printf("Genera el reporte primero desde el menu.\n");
        return;
    }

    printf("\n=== CONTENIDO DE %s ===\n", nombreArchivo);

    char linea[200];
    while (fgets(linea, sizeof(linea), archivo)) {
        printf("%s", linea);
    }

    fclose(archivo);
}