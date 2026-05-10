#include "encabezados/main.h"
#include "encabezados/validadores.h"
#include  "encabezados/archivos.h"

bool cargarJugadorActual(Jugador *jugador, Jugador lista[], int *n, int pos) {
    if (jugador == NULL || n == NULL || pos < 0 || pos >= *n) {
        printf("No se pudo encontrar al jugador.\n");
        return false;
    }

    *jugador = lista[pos];

    printf("\n¡Iniciaste sesion como '%s'!\n\n", jugador->username);

    return true;
}

void crearNuevoJugador() {

    do {

        printf("Ingrese su nombre de usuario: ");
        scanf("%29s", lista[contador_id].username);

    } while (!validarUsername(lista[contador_id].username) || !validarJugador(lista[contador_id].username));

    do {

        printf("Ingrese su correo electronico: ");
        scanf("%49s", lista[contador_id].email);

    } while (!validarEmail(lista[contador_id].email));

    do {

        printf("Ingrese su pais: ");
        scanf("%29s", lista[contador_id].pais);

    } while (!validarPais(lista[contador_id].pais));

    lista[contador_id].id_jugador = contador_id;

    guardarJugador(&lista[contador_id], &contador_id);

    menuPrincipal();
}

void mostrarDatosJugador(int pos) {

    if (pos == -1) {
        printf("\nEl jugador no fue encontrado.\n");
        return;
    }

    printf("\n----------- %s -----------\n\n", lista[pos].username);
    printf("Id del usuario: %d\n", lista[pos].id_jugador);
    printf("Email: %s\n", jugadorActivo.email);
    printf("Pais: %s\n\n", jugadorActivo.pais);

}

void editarJugador(Jugador *jugador, Jugador lista[], int *n, int pos) {
    if (pos < 0 || pos >= *n) {
        printf("No se pudo encontrar al jugador.\n");
        return;
    }

    int op;
    char nuevoValor[50];

    do {
        printf("\n----- MODIFICAR JUGADOR: %s -----\n", jugador->username);
        printf("\t1) Cambiar pais     [actual: %s]\n", jugador->pais);
        printf("\t2) Cambiar email    [actual: %s]\n", jugador->email);
        printf("\t3) Guardar cambios\n");
        printf("\t4) Cancelar\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
                do {
                    printf("Nuevo pais: ");
                    scanf("%29s", nuevoValor);
                } while (!validarPais(nuevoValor));
                strcpy(jugador->pais, nuevoValor);
                strcpy(lista[pos].pais, nuevoValor);
                printf("Pais actualizado.\n");
                break;

            case 2:
                do {
                    printf("Nuevo email: ");
                    scanf("%49s", nuevoValor);
                } while (!validarEmail(nuevoValor));
                strcpy(jugador->email, nuevoValor);
                strcpy(lista[pos].email, nuevoValor);
                printf("Email actualizado.\n");
                break;

            case 3: {
                FILE *archivo = fopen("jugadores.dat", "r+b");
                if (archivo == NULL) {
                    printf("Error: No se pudo abrir el archivo.\n");
                    break;
                }
                fseek(archivo, pos * sizeof(Jugador), SEEK_SET);
                fwrite(jugador, sizeof(Jugador), 1, archivo);
                fclose(archivo);
                printf("Cambios guardados correctamente.\n");
                break;
            }

            case 4:
                printf("Modificacion cancelada.\n");
                break;

            default:
                printf("Opcion invalida.\n");
        }

    } while (op != 3 && op != 4);
}

void eliminarJugador(Jugador lista[], int *n, int pos) {
    if (pos < 0 || pos >= *n) {
        printf("No se pudo encontrar al jugador.\n");
        return;
    }

    char confirmacion[4];

    printf("\nEsta seguro que desea eliminar a '%s'? (s/n): ", lista[pos].username);
    scanf("%3s", confirmacion);

    if (strcmp(confirmacion, "s") != 0 && strcmp(confirmacion, "S") != 0) {
        printf("Eliminacion cancelada.\n");
        return;
    }

    FILE *archivo = fopen("jugadores.dat", "wb");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }

    for (int i = 0; i < *n; i++) {
        if (i != pos) {
            fwrite(&lista[i], sizeof(Jugador), 1, archivo);
        }
    }
    fclose(archivo);

    for (int i = pos; i < *n - 1; i++) {
        lista[i] = lista[i + 1];
    }
    (*n)--;

    printf("Jugador eliminado correctamente.\n");
}
