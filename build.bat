@echo off
REM Build script for Chess Game on Windows

echo Building Chess Game...
echo.

REM Check if build directory exists
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

REM Configure with CMake
REM Adjust the CMAKE_PREFIX_PATH if you have Qt installed elsewhere
echo Configuring with CMake...
cmake .. -DCMAKE_PREFIX_PATH="C:\codebase\Qt\Folder\6.10.1\mingw_64\lib\cmake"

if errorlevel 1 (
    echo CMake configuration failed. Please ensure Qt 5 is installed.
    echo Try installing Qt or update the CMAKE_PREFIX_PATH in this script.
    pause
    exit /b 1
)

REM Build the project
echo.
echo Building project...
cmake --build . --config Release

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Build successful!
echo.
echo To run the game, execute: .\Release\ChessGame.exe
pause
