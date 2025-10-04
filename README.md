# Tic Tac Toe con Interfaz Gráfica y Chat

Este proyecto es una implementación del juego clásico Tic Tac Toe (Tres en Raya) con una interfaz gráfica moderna y un sistema de chat integrado. El juego mantiene la inteligencia artificial del oponente CPU del juego original, pero ahora con una experiencia visual mejorada y la capacidad de comunicarse con otros jugadores.

## Características

- Interfaz gráfica con estilo Frutiger Aero (estilo Windows XP/2000)
- Juego contra CPU con inteligencia artificial de 4 niveles
- Sistema de chat integrado para comunicación en tiempo real
- Diseño MVC (Modelo-Vista-Controlador) para una arquitectura limpia y mantenible
- Tablero interactivo con clics del mouse

## Requisitos del Sistema

- Windows 10/11
- Visual Studio 2022 o superior
- CMake 3.10 o superior
- SFML 2.5 o superior

## Instalación de Dependencias

### Instalar SFML

1. Descarga SFML desde [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
2. Selecciona la versión compatible con tu compilador (Visual Studio)
3. Extrae los archivos en una ubicación conocida (por ejemplo, `C:\SFML`)

### Configurar Variables de Entorno

1. Agrega la ruta de los binarios de SFML a tu PATH:
   - `C:\SFML\bin` (o la ruta donde extrajiste SFML)

## Compilación

### Método 1: Usando el script de compilación

```bash
build.bat
```

### Método 2: Compilación manual

```bash
mkdir build
cd build
cmake .. -G "Visual Studio 17 2022"
cmake --build . --config Release
```

## Ejecución

Después de compilar, ejecuta el juego:

```bash
build\Release\TicTacToe.exe
```

## Cómo Jugar

1. El juego comienza automáticamente después de lanzar los dados para determinar quién empieza
2. Haz clic en una celda vacía para colocar tu ficha (X)
3. La CPU (O) hará su movimiento automáticamente
4. El primer jugador en conseguir tres en línea gana
5. Usa el chat para comunicarte con otros jugadores (funcionalidad en desarrollo)

## Controles

- **Mouse**: Hacer clic en las celdas del tablero para hacer movimientos
- **Teclado**: Escribir en el cuadro de chat y presionar Enter para enviar mensajes

## Estructura del Proyecto

```
TicTacToe-en-CPP/
├── include/           # Archivos de cabecera
├── src/               # Código fuente
├── resources/         # Recursos (imágenes, fuentes, etc.)
├── build/             # Archivos de compilación (generados)
├── CMakeLists.txt     # Configuración de CMake
├── build.bat          # Script de compilación para Windows
└── README.md          # Este archivo
```

## Arquitectura MVC

### Modelo
- `GameModel`: Lógica del juego, reglas, verificación de victoria
- `ChatModel`: Gestión de mensajes de chat y comunicación de red

### Vista
- `GameView`: Renderizado gráfico del tablero y elementos del juego
- `ChatView`: Interfaz de usuario para el sistema de chat

### Controlador
- `Controller`: Coordinación entre modelo y vista, manejo de eventos

## Personalización

### Cambiar el Estilo Frutiger Aero

Puedes modificar los colores en los archivos `GameView.cpp` y `ChatView.cpp`:
- `backgroundColor`: Color de fondo principal
- `cellColor`: Color de las celdas del tablero
- `textColor`: Color del texto
- `borderColor`: Color de los bordes

## Problemas Conocidos

1. La funcionalidad de red para el chat aún está en desarrollo
2. Algunas configuraciones pueden requerir ajustes manuales de rutas

## Contribuciones

Las contribuciones son bienvenidas. Por favor, haz un fork del repositorio y envía un pull request con tus mejoras.

## Licencia

Este proyecto está licenciado bajo la Licencia MIT - ver el archivo LICENSE para más detalles.

## Autor

Basado en el trabajo original de Carlos Javier Cuervo Baracaldo (Carlonox)
