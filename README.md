# GamerRank

Sistema de rankings y estadísticas de jugadores de videojuegos desarrollado en C/C++ como Producto Integrador de Aprendizaje (PIA) para la materia de Programación Estructurada en la UANL.

---

## Descripción

GamerRank permite a los jugadores registrarse, llevar un historial de sus partidas y consultar su posición en rankings dinámicos frente a otros jugadores. El sistema calcula automáticamente estadísticas de rendimiento y las compara contra el promedio global, generando un diagnóstico personalizado para cada jugador.

---

## Características principales

- **Registro y gestión de jugadores** con validación de datos mediante expresiones regulares
- **Historial de partidas** con hasta 50 partidas por jugador
- **Sistema de rangos automático**: Bronce → Plata → Oro → Platino → Diamante
- **Rankings dinámicos** ordenables por puntaje, winrate o victorias
- **Filtros de ranking** por país y por juego específico
- **Comparación contra el promedio global** con diagnóstico de rendimiento
- **Gráficas interactivas** con Matplot++
- **Reportes exportables** en archivos .txt con formato tabular

---

## Estructura del proyecto

```
GamerRank/
├── main.c              # Lógica principal del sistema en C
├── graficas.cpp        # Funciones de visualización con Matplot++
├── graficas.h          # Archivo de cabecera (extern "C")
├── CMakeLists.txt      # Configuración de compilación
├── jugadores.dat       # Archivo binario de acceso directo (generado al ejecutar)
├── ranking.txt         # Reporte de ranking global (generado al ejecutar)
└── reporte_[user].txt  # Reporte individual por jugador (generado al ejecutar)
```

---

## Requisitos

- GCC / G++ con soporte C11 y C++17
- CMake 3.20 o superior
- [Matplot++](https://github.com/alandefreitas/matplotplusplus) — instalable con Homebrew en Mac:

```bash
brew install matplotplusplus
brew install gnuplot
```

### Instalacion en Windows

Requisitos:
- Visual Studio 2022 con C++ (MSVC)
- CMake 3.20 o superior
- Git
- vcpkg

Pasos recomendados (PowerShell):
```powershell
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
./vcpkg install matplotplusplus:x64-windows gnuplot:x64-windows
```

Al configurar CMake, agrega la ruta de vcpkg para que encuentre Matplot++:
```bash
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE="C:/ruta/a/vcpkg/scripts/buildsystems/vcpkg.cmake"
```


##  Uso del sistema

Al iniciar, el sistema solicita un **username**. Si ya existe, carga los datos del jugador. Si no existe, lo registra solicitando país y email.

### Menú principal

| Tecla | Opción |
|-------|--------|
| `J` | Gestión de jugadores (editar, eliminar) |
| `P` | Partidas (registrar, ver historial, editar) |
| `R` | Rankings (global, por juego, por país, Top 10) |
| `E` | Estadísticas y gráficas |
| `S` | Salir del sistema |

### Rangos del sistema

| Rango | Puntaje requerido |
|-------|-------------------|
| Bronce | 0 — 499 pts |
| Plata | 500 — 1,499 pts |
| Oro | 1,500 — 2,999 pts |
| Platino | 3,000 — 4,999 pts |
| Diamante | 5,000+ pts |

---

## Equipo

| Nombre | Matrícula | Grupo |
|--------|-----------|-------|
| Hector Emiliano Garcia Luevano | 2148010 | 035 |
| Dariana Michel Guevara Corpus | 2082041 | 033 |
| Luis Angel Hernandez Hernandez | 2118162 | 033 |

**Maestra:** Reyna Guadalupe Castro Medellin  
**Universidad:** Universidad Autónoma de Nuevo León  
**Materia:** Programación Estructurada  
**Fecha de entrega:** 9 de mayo de 2026
