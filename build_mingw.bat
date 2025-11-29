@echo off
REM Chess Game Build Script for Windows with MinGW and Qt6

setlocal enabledelayedexpansion

echo.
echo ====================================
echo Chess Game - Build & Run Script
echo ====================================
echo.

REM Check if build directory exists
if not exist build (
    echo Creating build directory...
    mkdir build
)

cd build

REM Clean previous build
echo Cleaning previous build...
if exist CMakeFiles (
    rmdir /s /q CMakeFiles
)
del /q CMakeCache.txt 2>nul

REM Configure with CMake
echo.
echo Configuring with CMake...
echo Using MinGW compiler and Qt6...
echo.

cmake .. ^
  -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER="C:\Qt\Tools\mingw1310_64\bin\gcc.exe" ^
  -DCMAKE_CXX_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe" ^
  -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64"

if errorlevel 1 (
    echo.
    echo ERROR: CMake configuration failed!
    echo.
    echo Troubleshooting:
    echo 1. Verify CMake is installed
    echo 2. Check Qt6 path: C:\Qt\6.10.1\mingw_64
    echo 3. Verify MinGW path: C:\Qt\Tools\mingw1310_64
    echo.
    pause
    exit /b 1
)

REM Build the project
echo.
echo Building project...
echo.

mingw32-make -j4

if errorlevel 1 (
    echo.
    echo ERROR: Build failed!
    echo.
    pause
    exit /b 1
)

REM Deploy Qt libraries
echo.
echo Deploying Qt libraries...
"C:\Qt\6.10.1\mingw_64\bin\windeployqt.exe" "ChessGame.exe"

if errorlevel 1 (
    echo.
    echo WARNING: Qt deployment may have failed
    echo But the executable might still work
    echo.
)

echo.
echo ====================================
echo Build successful!
echo ====================================
echo.
echo To run the game, execute:
echo   .\ChessGame.exe
echo.
pause
cd ..
