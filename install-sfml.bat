@echo off
echo Instalando SFML para el proyecto TicTacToe...

REM Verificar si vcpkg está instalado
where vcpkg >nul 2>&1
if %errorlevel% neq 0 (
    echo vcpkg no encontrado. Instalando vcpkg...
    echo Clonando vcpkg desde GitHub...
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    .\bootstrap-vcpkg.bat
    echo Agregando vcpkg al PATH...
    set PATH=%PATH%;%cd%
    cd ..
) else (
    echo vcpkg ya está instalado.
)

REM Instalar SFML usando vcpkg
echo Instalando SFML...
vcpkg install sfml:x64-windows

echo.
echo Instalación completada.
echo Ahora puedes compilar el proyecto ejecutando build.bat
pause
