@echo off
echo Subiendo la versión mejorada a GitHub...

REM Verificar si estamos en un repositorio git
if not exist .git (
    echo Este directorio no es un repositorio git.
    echo Por favor, ejecuta este script desde el directorio del repositorio.
    pause
    exit /b 1
)

REM Verificar el estado actual
echo Verificando el estado del repositorio...
git status

REM Crear una nueva rama para la versión mejorada
echo Creando nueva rama 'enhanced-version'...
git checkout -b enhanced-version

REM Agregar todos los nuevos archivos
echo Agregando archivos al staging area...
git add include/
git add src/
git add CMakeLists.txt
git add build.bat
git add install-sfml.bat
git add README.md

REM Agregar el archivo modificado
git add Cpp-Tictactoe.cpp

REM Hacer commit de los cambios
echo Haciendo commit de los cambios...
git commit -m "Agregada versión mejorada con interfaz gráfica y chat

- Implementada arquitectura MVC
- Añadida interfaz gráfica con SFML y estilo Frutiger Aero
- Integrado sistema de chat
- Mantenido el código original en esta rama como referencia
- Actualizado README con instrucciones de compilación"

REM Hacer push de la nueva rama
echo Subiendo la nueva rama a GitHub...
git push origin enhanced-version

echo.
echo ¡Proceso completado!
echo La versión mejorada se ha subido a la rama 'enhanced-version'
echo en el repositorio https://github.com/carlonox/Tictactoe-en-CPP.git
echo.
echo Para ver ambas versiones:
echo - Rama principal: Código original en consola
echo - Rama enhanced-version: Nueva versión con interfaz gráfica y chat
pause
