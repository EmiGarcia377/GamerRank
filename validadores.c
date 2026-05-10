#include "encabezados/main.h"
#include <regex.h>


bool validarUsername(char *username) {
    regex_t regex;
    int resultado;
    int len = strlen(username);

    if (len < 3 || len > 31) {
        printf("Error: El username debe tener entre 3 y 20 caracteres.\n");
        return false;
    }

    char *patron = "^[a-zA-Z0-9_]+$";

    regcomp(&regex, patron, REG_EXTENDED | REG_NOSUB);
    resultado = regexec(&regex, username, 0, NULL, 0);
    regfree(&regex);

    if (resultado == 0) {
        return true;
    }
    printf("Error: Solo se permiten letras, numeros y '_'\n");
    return false;
}

bool validarEmail(char *email) {
    regex_t regex;
    int resultado;
    int len = strlen(email);

    if (len < 3 || len > 51) {
        printf("Error: El Email debe ser valido para ser ingresado.\n");
        return false;
    }

    char *patron = "^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$";

    regcomp(&regex, patron, REG_EXTENDED | REG_NOSUB);
    resultado = regexec(&regex, email, 0, NULL, 0);
    regfree(&regex);

    if (resultado == 0) {
        return true;
    }
    printf("Error: Solo se permiten letras, numeros y '_'\n");
    return false;
}

bool validarPais(char *pais) {
    regex_t regex;
    int resultado;
    int len = strlen(pais);

    if (len < 3 || len > 31) {
        printf("Error: La longitud del nombre del pais debe ser mayor a 3 y menor a 31.");
        return false;
    }

    char *patron = "^[a-zA-Z]+";

    regcomp(&regex, patron, REG_EXTENDED | REG_NOSUB);
    resultado = regexec(&regex, pais, 0, NULL, 0);
    regfree(&regex);

    if (resultado == 0) {
        return true;
    }
    printf("Error: solo se permiten letras.");
    return false;
}

bool validarJugador (char *username){
    FILE *archivo = fopen("jugadores.dat", "rb");

    if (archivo != NULL) {
        for (int i = 0; i < contador_id; i++) {
            if (strcmp(lista[i].username, username) == 0) {
                printf("Este nombre de usuario ya existe, ingresa otro diferente.\n");
                fclose(archivo);
                return false;
            }
        }
    };

    fclose(archivo);

    return true;
}

bool validarCadena(char *cadena) {
    int len = strlen(cadena);

    if (len < 2 || len > 39) {
        printf("Error: El nombre debe tener entre 2 y 39 caracteres.\n");
        return false;
    }

    regex_t regex;
    char *patron = "^[a-zA-Z0-9 :_-]+$";

    regcomp(&regex, patron, REG_EXTENDED | REG_NOSUB);
    int resultado = regexec(&regex, cadena, 0, NULL, 0);
    regfree(&regex);

    if (resultado != 0) {
        printf("Error: El nombre solo puede tener letras, numeros, ");
        printf("espacios, guiones y dos puntos.\n");
        return false;
    }

    return true;
}

bool validarPuntos(char *puntos) {
    regex_t regex;
    char *patron = "^[0-9]\\{1,6\\}$";

    regcomp(&regex, patron, REG_EXTENDED | REG_NOSUB);
    int resultado = regexec(&regex, puntos, 0, NULL, 0);
    regfree(&regex);

    if (resultado != 0) {
        printf("Error: Los puntos deben ser un numero entre 0 y 999999.\n");
        return false;
    }

    return true;
}