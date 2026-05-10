#include "encabezados/graficas.h"
#include <matplot/matplot.h>
#include <vector>
#include <string>

using namespace std;
using namespace matplot;

void graficaBarrasPuntaje(const char usernames[][30],
                          int puntajes[], int n) {
    vector<double> y(puntajes, puntajes + n);
    vector<string> etiquetas;
    for (int i = 0; i < n; i++)
        etiquetas.push_back(usernames[i]);

    auto fig = figure();
    auto b = bar(y);
    xticks(iota(1, n));
    xticklabels(etiquetas);
    title("Puntaje Total por Jugador");
    xlabel("Jugador");
    ylabel("Puntaje");
    show();
}

void graficaProgresoJugador(int puntajesPorPartida[],
                             int totalPartidas, const char *username) {
    vector<double> x, y;
    int acumulado = 0;

    for (int i = 0; i < totalPartidas; i++) {
        acumulado += puntajesPorPartida[i];
        x.push_back(i + 1);
        y.push_back(acumulado);
    }

    auto fig = figure();
    plot(x, y, "-o");
    title(string("Progreso de ") + username);
    xlabel("Partida");
    ylabel("Puntaje acumulado");
    grid(true);
    show();
}

void graficaWinratePorJuego(const char juegos[][40],
                              float winrates[], int n) {
    vector<double> y(winrates, winrates + n);
    vector<string> etiquetas;
    for (int i = 0; i < n; i++)
        etiquetas.push_back(juegos[i]);

    auto fig = figure();
    bar(y);
    xticks(iota(1, n));
    xticklabels(etiquetas);
    title("Winrate por Juego");
    xlabel("Juego");
    ylabel("Winrate (%)");
    show();
}

void graficaComparativaKD(const char usernames[][30],
                           float winrates[], int n) {
    vector<double> y(winrates, winrates + n);
    vector<string> etiquetas;
    for (int i = 0; i < n; i++)
        etiquetas.push_back(usernames[i]);

    auto fig = figure();
    bar(y);
    xticks(iota(1, n));
    xticklabels(etiquetas);
    title("Comparativa Winrate entre Jugadores");
    xlabel("Jugador");
    ylabel("Winrate (%)");
    show();
}