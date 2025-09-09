Implementación del clásico juego Triqui (Tres en Raya) en C++, con una CPU inteligente que toma decisiones estratégicas para ganar o bloquear al jugador. Incluye sistema de dados para determinar quién inicia. 


Este proyecto es una versión mejorada del juego Triqui, donde:

El jugador humano juega con X.
La CPU juega con O.
Antes de iniciar, se lanzan dados virtuales para decidir aleatoriamente quién empieza.
La CPU sigue una estrategia en 5 niveles:
✅ Gana si puede.
🚫 Bloquea al jugador si está a punto de ganar.
🎯 Toma la mejor jugada del oponente (mayor puntaje).
🧠 Toma su propia mejor jugada.
🎲 Si todo falla, elige aleatoriamente.
