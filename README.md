# 🎲 Triqui Inteligente con CPU Estratégica

> Implementación del clásico juego **Triqui (Tres en Raya)** en **C++**, con una **CPU que toma decisiones estratégicas** para ganar, bloquear o maximizar su puntaje. Incluye sistema de dados para decidir quién empieza. ¡Perfecto para aprender lógica de juego y algoritmos de toma de decisiones!

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Console](https://img.shields.io/badge/Consola-Texto%20%F0%9F%96%A5-333333?style=for-the-badge)
![MIT License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

![Captura del juego en consola](https://via.placeholder.com/600x300/2c3e50/ffffff?text=Triqui+C%2B%2B+en+Consola)  
*(Reemplaza con una captura real de tu juego en ejecución)*

---

## 📌 Descripción

Este proyecto es una versión mejorada del juego Triqui, donde:
- El jugador humano juega con **`X`**.
- La CPU juega con **`O`**.
- **¡Sistema de dados!** 🎲 Antes de iniciar, se lanzan dados virtuales para decidir aleatoriamente quién empieza.
- La CPU sigue una **estrategia en 6 niveles**:
  1. ✅ Gana si puede.
  2. 🚫 Bloquea al jugador si está a punto de ganar.
  3. 🎯 Toma la mejor jugada del oponente (mayor puntaje).
  4. 🧠 Toma su propia mejor jugada.
  5. 🎯 Elige la esquina superior izquierda (0,0) si está libre.
  6. 🎲 Si todo falla, elige aleatoriamente.

Ideal para aprender lógica de programación, matrices, recursión y toma de decisiones en C++.

---

## 🛠️ Tecnologías Utilizadas

- **Lenguaje**: C++ (estándar)
- **Compilador**: GCC, Clang, MSVC (cualquiera compatible)
- **Librerías estándar**: `<iostream>`, `<vector>`, `<ctime>`, `<cstdlib>`, `<cstdio>`
- **Plataforma**: Consola (multiplataforma: Windows, Linux, macOS)

---

## 🚀 Cómo Compilar y Ejecutar

### Requisitos
- Compilador de C++ (g++, clang++, etc.)
- Sistema operativo: Windows, Linux o macOS

### Pasos

1. Clona el repositorio (o copia el archivo `.cpp`):
   ```bash
    git clone https://github.com/carlonox/Tictactoe-en-CPP.git
    cd Tictactoe-en-CPP
