# Tic Tac Toe - Evolución del Proyecto

## Descripción del Proyecto

Este repositorio contiene la evolución del clásico juego Tic Tac Toe (Tres en Raya) desde una implementación básica en consola hasta una versión avanzada con interfaz gráfica y chat integrado.

## Versiones

### v1.0 - Versión Terminal (Original)
Una implementación clásica del juego Tic Tac Toe en consola con una CPU inteligente que implementa una estrategia de 6 niveles para tomar decisiones. Incluye sistema de dados para determinar quién empieza.

**Características:**
- Juego en consola con interfaz de texto
- CPU con inteligencia artificial avanzada (6 niveles)
- Sistema de dados para determinar el jugador inicial
- Coordenadas cartesianas para movimientos (1,1 es la esquina inferior izquierda)

**Cómo ejecutar:**
```bash
# Navegar a la carpeta de la versión terminal
cd terminal-version

# Compilar (puede variar según el compilador)
g++ Cpp-Tictactoe.cpp -o tictactoe

# Ejecutar
./tictactoe
```

### v2.0 - Versión con Interfaz Gráfica y Chat
Una implementación moderna del juego con interfaz gráfica estilo Frutiger Aero (Windows XP/2000) y sistema de chat integrado.

**Características:**
- Interfaz gráfica con estilo Frutiger Aero
- Juego contra CPU con inteligencia artificial de 4 niveles
- Sistema de chat integrado para comunicación en tiempo real
- Diseño MVC (Modelo-Vista-Controlador)
- Tablero interactivo con clics del mouse

**Requisitos del Sistema:**
- Windows 10/11
- Visual Studio 2022 o superior
- CMake 3.10 o superior
- SFML 2.5 o superior

**Cómo ejecutar:**
```bash
# Navegar a la carpeta de la versión GUI
cd gui-version

# Compilación manual
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release

# Ejecutar
build\Release\TicTacToe.exe
```

## Estructura del Repositorio

```
TicTacToe-en-CPP/
├── terminal-version/  # Versión original en consola
│   └── Cpp-Tictactoe.cpp
├── gui-version/       # Versión con GUI y chat
│   ├── include/       # Archivos de cabecera
│   ├── src/           # Código fuente
│   ├── CMakeLists.txt # Configuración de CMake
│   └── .gitignore
├── .vscode/           # Configuración del IDE
└── README.md          # Este archivo
```

## Historial de Versiones

- **v1.0**: Versión terminal básica con CPU inteligente
- **v2.0**: Versión con interfaz gráfica y chat

## Autor

Carlos Javier Cuervo Baracaldo (Carlonox)
