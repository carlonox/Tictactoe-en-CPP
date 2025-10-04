// ===========================================================================
// JUEGO TRIQUI (TRES EN RAYA) CON CPU INTELIGENTE
// ===========================================================================
// Autor: Carlos Javier Cuervo Baracaldo (Carlonox)
// Descripción: Implementación del clásico juego Triqui con una CPU que 
//              implementa una estrategia de 6 niveles para tomar decisiones.
//              Incluye sistema de dados para determinar quién empieza.
//
// Sistema de coordenadas: Coordenadas cartesianas donde (1,1) es la esquina 
//                         inferior izquierda y (3,3) es la esquina superior derecha.
// ===========================================================================

// Librerías estándar de C++
#include <iostream>     // Entrada/salida estándar
#include <stdlib.h>     // Funciones estándar como srand() y rand()
#include <process.h>    // Funciones de proceso (getpid())
#include <vector>       // Contenedores vector
#include <ctime>        // Funciones de tiempo para números aleatorios
#include <cstdio>       // Funciones de entrada/salida en C (scanf, printf)

// Constantes del juego
const int FILAS = 3;                    // Número de filas del tablero
const int COLUMNAS = 3;                 // Número de columnas del tablero
const int TAMANO_MATRIZ = FILAS * COLUMNAS;  // Tamaño total del tablero
const char JUGADOR_X = 'X';             // Símbolo del jugador humano
const char JUGADOR_O = 'O';             // Símbolo de la CPU
const char JUGADOR_CPU_X = JUGADOR_X;   // Alias para el jugador X de la CPU
const char JUGADOR_CPU_O = JUGADOR_O;   // Alias para el jugador O de la CPU
const char ESPACIO_VACIO = ' ';         // Carácter para espacios vacíos
const int CONTEO_PARA_GANAR = 3;        // Número de piezas en línea para ganar

// Opciones del menú principal
const int JUGADOR_CPU = 1;              // Opción para jugar contra CPU
const int SALIR = 2;                    // Opción para salir del juego

using namespace std;

void clonarMatriz(char tableroOriginal[FILAS][COLUMNAS], char destino[FILAS][COLUMNAS])
{
    memcpy(destino, tableroOriginal, TAMANO_MATRIZ);
}

void limpiarTablero(char tablero[FILAS][COLUMNAS])
{
    int fila;
    for (fila = 0; fila < FILAS; fila++)
    {
        int col;
        for (col = 0; col < COLUMNAS; col++)
        {
            tablero[fila][col] = ESPACIO_VACIO;
        }
    }
}

// CORREGIDO: Imprime el tablero con Y creciendo de abajo hacia arriba
void imprimirTablero(char tablero[FILAS][COLUMNAS])
{
    printf("\n");
    int fila;
    int col;
    
    // Imprimir de arriba hacia abajo, pero mostrando números Y de mayor a menor
    // fila 0 del arreglo = Y=3 (arriba)
    // fila 1 del arreglo = Y=2 (medio)
    // fila 2 del arreglo = Y=1 (abajo)
    for (fila = 0; fila < FILAS; fila++)
    {
        printf("%d ", FILAS - fila); // Muestra 3, 2, 1
        for (col = 0; col < COLUMNAS; col++)
        {
            printf("|%c", tablero[fila][col]);
        }
        cout<<"|\n";
    }
    
    // Imprimir encabezado de columnas (X) en la parte inferior
    printf("  ");
    for (col = 0; col < COLUMNAS; col++)
    {
        printf(" %d", col + 1); // Muestra 1, 2, 3
    }
    printf("\n");
}

int coordenadasVacias(int fila, int col, char tablero[FILAS][COLUMNAS])
{
    return tablero[fila][col] == ESPACIO_VACIO;
}

// Devuelve 1 si se colocó exitosamente, 0 si no
int colocarPieza(int fila, int col, char pieza, char tablero[FILAS][COLUMNAS])
{
    if (fila < 0 || fila >= FILAS)
    {
        return 0;
    }

    if (col < 0 || col >= COLUMNAS)
    {
        return 0;
    }
    if (pieza != JUGADOR_O && pieza != JUGADOR_X)
    {
        return 0;
    }
    if (!coordenadasVacias(fila, col, tablero))
    {
        return 0;
    }
    tablero[fila][col] = pieza;
    return 1;
}

// CORREGIDO: Funciones de conteo con parámetros en orden correcto (fila, col)
int contarHaciaArriba(int fila, int col, char jugador, char tablero[FILAS][COLUMNAS])
{
    int filaInicio = (fila - CONTEO_PARA_GANAR >= 0) ? fila - CONTEO_PARA_GANAR + 1 : 0;
    int contador = 0;
    for (; filaInicio <= fila; filaInicio++)
    {
        if (tablero[filaInicio][col] == jugador)
        {
            contador++;
        }
        else
        {
            contador = 0;
        }
    }
    return contador;
}

int contarHaciaDerecha(int fila, int col, char jugador, char tablero[FILAS][COLUMNAS])
{
    int colFin = (col + CONTEO_PARA_GANAR < COLUMNAS) ? col + CONTEO_PARA_GANAR - 1 : COLUMNAS - 1;
    int contador = 0;
    for (; col <= colFin; col++)
    {
        if (tablero[fila][col] == jugador)
        {
            contador++;
        }
        else
        {
            contador = 0;
        }
    }
    return contador;
}

int contarHaciaArribaDerecha(int fila, int col, char jugador, char tablero[FILAS][COLUMNAS])
{
    int colFin = (col + CONTEO_PARA_GANAR < COLUMNAS) ? col + CONTEO_PARA_GANAR - 1 : COLUMNAS - 1;
    int filaInicio = (fila - CONTEO_PARA_GANAR >= 0) ? fila - CONTEO_PARA_GANAR + 1 : 0;
    int contador = 0;
    while (col <= colFin && filaInicio <= fila)
    {
        if (tablero[fila][col] == jugador)
        {
            contador++;
        }
        else
        {
            contador = 0;
        }
        col++;
        fila--;
    }
    return contador;
}

int contarHaciaAbajoDerecha(int fila, int col, char jugador, char tablero[FILAS][COLUMNAS])
{
    int colFin = (col + CONTEO_PARA_GANAR < COLUMNAS) ? col + CONTEO_PARA_GANAR - 1 : COLUMNAS - 1;
    int filaFin = (fila + CONTEO_PARA_GANAR < FILAS) ? fila + CONTEO_PARA_GANAR - 1 : FILAS - 1;
    int contador = 0;
    while (col <= colFin && fila <= filaFin)
    {
        if (tablero[fila][col] == jugador)
        {
            contador++;
        }
        else
        {
            contador = 0;
        }
        col++;
        fila++;
    }
    return contador;
}

int comprobarSiGana(char jugador, char tablero[FILAS][COLUMNAS])
{
    int fila;
    for (fila = 0; fila < FILAS; fila++)
    {
        int col;
        for (col = 0; col < COLUMNAS; col++)
        {
            if (
                contarHaciaArriba(fila, col, jugador, tablero) >= CONTEO_PARA_GANAR ||
                contarHaciaDerecha(fila, col, jugador, tablero) >= CONTEO_PARA_GANAR ||
                contarHaciaArribaDerecha(fila, col, jugador, tablero) >= CONTEO_PARA_GANAR ||
                contarHaciaAbajoDerecha(fila, col, jugador, tablero) >= CONTEO_PARA_GANAR)
            {
                return 1;
            }
        }
    }
    return 0;
}

char oponenteDe(char jugador)
{
    if (jugador == JUGADOR_O)
    {
        return JUGADOR_X;
    }
    else
    {
        return JUGADOR_O;
    }
}

int empate(char tableroOriginal[FILAS][COLUMNAS])
{
    int fila;
    for (fila = 0; fila < FILAS; fila++)
    {
        int col;
        for (col = 0; col < COLUMNAS; col++)
        {
            if (tableroOriginal[fila][col] == ESPACIO_VACIO)
            {
                return 0;
            }
        }
    }
    return 1;
}

int aleatorio_en_rango(int minimo, int maximo)
{
    return minimo + (rand() % (maximo - minimo + 1));
}

void obtenerCoordenadasAleatorias(char jugador, char tableroOriginal[FILAS][COLUMNAS], int* filaDestino, int* colDestino)
{
    int col, fila;
    do
    {
        col = aleatorio_en_rango(0, COLUMNAS - 1);
        fila = aleatorio_en_rango(0, FILAS - 1);
    } while (!coordenadasVacias(fila, col, tableroOriginal));
    *filaDestino = fila;
    *colDestino = col;
}

void coordenadasParaGanar(char jugador, char tableroOriginal[FILAS][COLUMNAS], int* filaDestino, int* colDestino)
{
    char copiaTablero[FILAS][COLUMNAS];
    int fila, col;
    for (fila = 0; fila < FILAS; fila++)
    {
        for (col = 0; col < COLUMNAS; col++)
        {
            clonarMatriz(tableroOriginal, copiaTablero);
            if (coordenadasVacias(fila, col, tableroOriginal))
            {
                copiaTablero[fila][col] = jugador; // Colocar directamente sin función
                if (comprobarSiGana(jugador, copiaTablero))
                {
                    *filaDestino = fila;
                    *colDestino = col;
                    return;
                }
            }
        }
    }
    *filaDestino = *colDestino = -1;
}

int contarSinSaberCoordenadas(char jugador, char copiaTablero[FILAS][COLUMNAS])
{
    int conteoMayor = 0;
    int col, fila;
    for (fila = 0; fila < FILAS; fila++)
    {
        for (col = 0; col < COLUMNAS; col++)
        {
            int conteoTemporal;
            conteoTemporal = contarHaciaArriba(fila, col, jugador, copiaTablero);
            if (conteoTemporal > conteoMayor)
            {
                conteoMayor = conteoTemporal;
            }
            conteoTemporal = contarHaciaArribaDerecha(fila, col, jugador, copiaTablero);
            if (conteoTemporal > conteoMayor)
            {
                conteoMayor = conteoTemporal;
            }

            conteoTemporal = contarHaciaDerecha(fila, col, jugador, copiaTablero);
            if (conteoTemporal > conteoMayor)
            {
                conteoMayor = conteoTemporal;
            }

            conteoTemporal = contarHaciaAbajoDerecha(fila, col, jugador, copiaTablero);
            if (conteoTemporal > conteoMayor)
            {
                conteoMayor = conteoTemporal;
            }
        }
    }
    return conteoMayor;
}

void coordenadasParaMayorPuntaje(char jugador, char tableroOriginal[FILAS][COLUMNAS], int* filaDestino, int* colDestino, int* conteo)
{
    char copiaTablero[FILAS][COLUMNAS];
    int fila, col;
    int conteoMayor = 0,
        colConteoMayor = -1,
        filaConteoMayor = -1;
    for (fila = 0; fila < FILAS; fila++)
    {
        for (col = 0; col < COLUMNAS; col++)
        {
            clonarMatriz(tableroOriginal, copiaTablero);
            if (!coordenadasVacias(fila, col, tableroOriginal))
            {
                continue;
            }
            // Colocar directamente sin función
            copiaTablero[fila][col] = jugador;
            int conteoTemporal = contarSinSaberCoordenadas(jugador, copiaTablero);
            if (conteoTemporal > conteoMayor)
            {
                conteoMayor = conteoTemporal;
                filaConteoMayor = fila;
                colConteoMayor = col;
            }
        }
    }
    *conteo = conteoMayor;
    *colDestino = colConteoMayor;
    *filaDestino = filaConteoMayor;
}

void elegirCoordenadasCpu(char jugador, char tablero[FILAS][COLUMNAS], int* filaDestino, int* colDestino)
{   
    int fila, col, conteoJugador, conteoOponente;
    char oponente = oponenteDe(jugador);
    
    // 1. Ganar si se puede
    coordenadasParaGanar(jugador, tablero, &fila, &col);
    if (fila != -1 && col != -1)
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
    
    // 2. Bloquear al oponente
    coordenadasParaGanar(oponente, tablero, &fila, &col);
    if (fila != -1 && col != -1)
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
    
    // 3 y 4. Tomar mejor movimiento
    coordenadasParaMayorPuntaje(jugador, tablero, &fila, &col, &conteoJugador);
    coordenadasParaMayorPuntaje(oponente, tablero, &fila, &col, &conteoOponente);
    if (conteoOponente > conteoJugador)
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
    else
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
}

int randomdado() 
{
    return aleatorio_en_rango(1, 6);
}

char jugadorAleatorio()
{
    int dado1, dado2;

    do {
        dado1 = randomdado();
        dado2 = randomdado();

        cout << "Lanzando dados.. " << endl;
        cout << "El dado del CPU es: [" << dado1 << "] El dado del Humano es: [" << dado2 << "]"<< endl;
        
        if (dado1 == dado2) {
            cout << "Lanzando dados de nuevo... "<<endl;
        }
    } while (dado1 == dado2);

    if (dado1 > dado2)
    {
        return JUGADOR_O;
    }
    else
    {
        return JUGADOR_X;
    }
}

void iniciarJuego(int modo)
{
    if (modo  != JUGADOR_CPU )
    {
        cout<<"Modo de juego no permitido";
        return;
    }
    
    char tablero[FILAS][COLUMNAS];
    limpiarTablero(tablero);
    char jugadorActual = jugadorAleatorio();
    printf("El jugador que inicia es: %c\n", jugadorActual);
    int x=0, y=0;
    int fila, col;
    
    while (1)
    {
        imprimirTablero(tablero);
        
        if (modo == JUGADOR_CPU && jugadorActual == JUGADOR_X)
        {
            int movimientoValido = 0;
            while (!movimientoValido)
            {
                printf("Jugador %c. Ingresa coordenadas (x,y) donde x=columna, y=fila.\n", jugadorActual);
                printf("Ejemplo: 1,1=esquina inferior izquierda, 3,3=esquina superior derecha: ");
                
                if (scanf("%d,%d", &x, &y) != 2)
                {
                    printf("Formato incorrecto. Usa: x,y (ejemplo: 2,3)\n");
                    while (getchar() != '\n'); // Limpiar buffer
                    continue;
                }
                
                // Limpiar el buffer de entrada
                while (getchar() != '\n');
                
                // Validar rango
                if (x < 1 || x > COLUMNAS || y < 1 || y > FILAS)
                {
                    printf("Coordenadas fuera de rango. Usa x e y entre 1 y %d\n", FILAS);
                    continue;
                }
                
                // Convertir de coordenadas cartesianas a índices de arreglo
                col = x - 1;           // x=1 -> col=0, x=2 -> col=1, x=3 -> col=2
                fila = FILAS - y;      // y=1 -> fila=2, y=2 -> fila=1, y=3 -> fila=0
                
                // Verificar si está vacío
                if (!coordenadasVacias(fila, col, tablero))
                {
                    printf("La posicion (%d,%d) ya esta ocupada. Intenta otra.\n", x, y);
                    continue;
                }
                
                // Si llegamos aquí, el movimiento es válido
                movimientoValido = 1;
            }
        }
        else if (modo == JUGADOR_CPU && jugadorActual == JUGADOR_O)
        {
            elegirCoordenadasCpu(jugadorActual, tablero, &fila, &col);
        }
        
        // Colocar la pieza (ya validada)
        tablero[fila][col] = jugadorActual;
        
        if (comprobarSiGana(jugadorActual, tablero))
        {
            imprimirTablero(tablero);
            printf("El jugador %c gana\n", jugadorActual);
            return;
        }
        else if (empate(tablero))
        {
            imprimirTablero(tablero);
            cout<<"Empate";
            return;
        }
        
        jugadorActual = oponenteDe(jugadorActual);
    }
}

int main()
{
    srand(time(0));
    cout << ("================================================\n");
    cout << ("|        Proyecto de Programacion basica       |\n");
    cout << ("|                  Juego Triqui                |\n");
    cout << ("|                       :)                     |\n");
    cout << ("================================================\n");
    
    int modo;
    cout << "1.Jugar (La CPU juega como: O)" << "\n2.Salir\nElige: " ;
    cin >> modo;
    if (modo == SALIR)
    {
        return 0;
    }
    iniciarJuego(modo);
}
