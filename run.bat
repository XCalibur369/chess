@echo off
REM Run the Chess Game executable

echo Starting Chess Game...
cd build

if exist ChessGame.exe (
    .\ChessGame.exe
) else (
    echo ERROR: ChessGame.exe not found!
    echo Please run build_mingw.bat first to build the project.
    echo.
    pause
)

cd ..
