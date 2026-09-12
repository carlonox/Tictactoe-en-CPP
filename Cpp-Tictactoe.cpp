// ===========================================================================
// TIC-TAC-TOE (TRIQUI) GAME WITH A STRATEGIC CPU
// ===========================================================================
// Author: Carlos Javier Cuervo Baracaldo (Carlonox)
// Description: Implementation of the classic Tic-Tac-Toe game with a CPU that 
//              follows a 6-tier strategy to make its decisions.
//              Includes a dice system to determine who starts.
//
// Coordinate system: Cartesian coordinates where (1,1) is the bottom-left 
//                    corner and (3,3) is the top-right corner.
// ===========================================================================

// Standard C++ libraries
#include <iostream>     // Standard input/output
#include <stdlib.h>     // Standard functions such as srand() and rand()
#include <process.h>    // Process functions (getpid())
#include <vector>       // Vector containers
#include <ctime>        // Time functions for random numbers
#include <cstdio>       // C input/output functions (scanf, printf)

// Game constants
const int FILAS = 3;                    // Number of board rows
const int COLUMNAS = 3;                 // Number of board columns
const int TAMANO_MATRIZ = FILAS * COLUMNAS;  // Total board size
const char JUGADOR_X = 'X';             // Human player symbol
const char JUGADOR_O = 'O';             // CPU symbol
const char JUGADOR_CPU_X = JUGADOR_X;   // Alias for the CPU's X player
const char JUGADOR_CPU_O = JUGADOR_O;   // Alias for the CPU's O player
const char ESPACIO_VACIO = ' ';         // Character for empty spaces
const int CONTEO_PARA_GANAR = 3;        // Number of pieces in a line needed to win

// Main menu options
const int JUGADOR_CPU = 1;              // Option to play against the CPU
const int SALIR = 2;                    // Option to quit the game

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

// FIXED: Prints the board with Y growing from bottom to top
void imprimirTablero(char tablero[FILAS][COLUMNAS])
{
    printf("\n");
    int fila;
    int col;
    
    // Print from top to bottom, but showing Y numbers from highest to lowest
    // array row 0 = Y=3 (top)
    // array row 1 = Y=2 (middle)
    // array row 2 = Y=1 (bottom)
    for (fila = 0; fila < FILAS; fila++)
    {
        printf("%d ", FILAS - fila); // Shows 3, 2, 1
        for (col = 0; col < COLUMNAS; col++)
        {
            printf("|%c", tablero[fila][col]);
        }
        cout<<"|\n";
    }
    
    // Print the column header (X) at the bottom
    printf("  ");
    for (col = 0; col < COLUMNAS; col++)
    {
        printf(" %d", col + 1); // Shows 1, 2, 3
    }
    printf("\n");
}

int coordenadasVacias(int fila, int col, char tablero[FILAS][COLUMNAS])
{
    return tablero[fila][col] == ESPACIO_VACIO;
}

// Returns 1 if the piece was placed successfully, 0 if not
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

// FIXED: Counting functions with parameters in the correct order (row, col)
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
                copiaTablero[fila][col] = jugador; // Place directly without a helper function
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
            // Place directly without a helper function
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
    
    // 1. Win if possible
    coordenadasParaGanar(jugador, tablero, &fila, &col);
    if (fila != -1 && col != -1)
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
    
    // 2. Block the opponent
    coordenadasParaGanar(oponente, tablero, &fila, &col);
    if (fila != -1 && col != -1)
    {
        *filaDestino = fila;
        *colDestino = col;
        return;
    }
    
    // 3 and 4. Take the best move
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

        cout << "Rolling dice... " << endl;
        cout << "CPU die: [" << dado1 << "] Human die: [" << dado2 << "]"<< endl;
        
        if (dado1 == dado2) {
            cout << "Rolling dice again... "<<endl;
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
        cout<<"Game mode not allowed";
        return;
    }
    
    char tablero[FILAS][COLUMNAS];
    limpiarTablero(tablero);
    char jugadorActual = jugadorAleatorio();
    printf("The starting player is: %c\n", jugadorActual);
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
printf("Player %c. Enter coordinates (x,y) where x=column, y=row.\n", jugadorActual);
                printf("Example: 1,1=bottom-left corner, 3,3=top-right corner: ");
                
                if (scanf("%d,%d", &x, &y) != 2)
                {
                    printf("Invalid format. Use: x,y (example: 2,3)\n");
                    int c;
                    while ((c = getchar()) != '\n' && c != EOF); // Clear buffer
                    continue;
                }
                
                // Clear the input buffer
                while (getchar() != '\n');
                
                // Validate range
                if (x < 1 || x > COLUMNAS || y < 1 || y > FILAS)
                {
                    printf("Coordinates out of range. Use x and y between 1 and %d\n", FILAS);
                    continue;
                }
                
                // Convert Cartesian coordinates to array indices
                col = x - 1;           // x=1 -> col=0, x=2 -> col=1, x=3 -> col=2
                fila = FILAS - y;      // y=1 -> fila=2, y=2 -> fila=1, y=3 -> fila=0
                
                // Check whether the cell is empty
                if (!coordenadasVacias(fila, col, tablero))
                {
                    printf("Position (%d,%d) is already taken. Try another one.\n", x, y);
                    continue;
                }
                
                // If we get here, the move is valid
                movimientoValido = 1;
            }
        }
        else if (modo == JUGADOR_CPU && jugadorActual == JUGADOR_O)
        {
            elegirCoordenadasCpu(jugadorActual, tablero, &fila, &col);
        }
        
        // Place the piece (already validated)
        tablero[fila][col] = jugadorActual;
        
        if (comprobarSiGana(jugadorActual, tablero))
        {
            imprimirTablero(tablero);
            printf("Player %c wins\n", jugadorActual);
            return;
        }
        else if (empate(tablero))
        {
            imprimirTablero(tablero);
            cout<<"It's a draw";
            return;
        }
        
        jugadorActual = oponenteDe(jugadorActual);
    }
}

int main()
{
    srand(time(0));
    cout << ("================================================\n");
    cout << ("|          Basic Programming Project           |\n");
    cout << ("|               Tic-Tac-Toe Game               |\n");
    cout << ("================================================\n");
    
    int modo;
    cout << "1.Play (the CPU plays as: O)" << "\n2.Quit\nChoose: " ;
    cin >> modo;
    if (modo == SALIR)
    {
        return 0;
    }
    iniciarJuego(modo);
}
