# Quick Start Guide - Chess Game

## Prerequisites Installation

### Option 1: Using vcpkg (Recommended for Visual Studio)

```powershell
# Clone vcpkg
git clone https://github.com/Microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat

# Integrate with Visual Studio
.\vcpkg integrate install

# Install Qt5
.\vcpkg install qt5:x64-windows
```

### Option 2: Using Official Qt Installer

1. Download from https://www.qt.io/download-open-source
2. Install Qt 5.15.x or later (select MSVC 2019 or 2022)
3. Note the installation path (e.g., `C:\Qt\5.15.14\msvc2019_64`)

### Option 3: Using Chocolatey

```powershell
choco install qt5-base
```

## Building on Windows

### Using Visual Studio (Recommended)

1. **Install CMake**: 
   ```powershell
   choco install cmake
   ```

2. **Update build.bat with your Qt path**:
   - Edit `build.bat` and change the CMAKE_PREFIX_PATH to match your Qt installation
   - Example: `C:\Qt\5.15.14\msvc2019_64`

3. **Run the build script**:
   ```powershell
   cd c:\codebase\Chess
   .\build.bat
   ```

4. **Run the game**:
   ```powershell
   .\build\Release\ChessGame.exe
   ```

### Using Command Line (CMake)

```powershell
cd c:\codebase\Chess
mkdir build
cd build

# If using vcpkg
cmake .. -DCMAKE_TOOLCHAIN_FILE="C:\path\to\vcpkg\scripts\buildsystems\vcpkg.cmake"

# If using official Qt installer
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\5.15.14\msvc2019_64"

# Build
cmake --build . --config Release

# Run
.\Release\ChessGame.exe
```

## Building on Linux

```bash
# Install dependencies (Ubuntu/Debian)
sudo apt-get install build-essential cmake qt5-qmake qt5-default

# Or with newer systems
sudo apt-get install build-essential cmake qt5-qmake qt5-default

# Build and run
cd ~/codebase/Chess
chmod +x build.sh
./build.sh
./build/ChessGame
```

## Building on macOS

```bash
# Install with Homebrew
brew install cmake qt@5

# Build
cd ~/codebase/Chess
chmod +x build.sh
./build.sh
./build/ChessGame
```

## Troubleshooting

### "Qt5 not found" error
- Ensure Qt5 is installed
- Update the CMAKE_PREFIX_PATH in the build command to match your Qt installation directory

### "CMake not found"
- Install CMake from https://cmake.org or use package manager
- Add CMake to PATH

### Build fails on Windows
- Make sure you have Visual Studio C++ compiler installed
- Try using Developer Command Prompt for Visual Studio
- Ensure Qt version matches your compiler (MSVC 2019 or 2022)

### MSVC compiler errors
- Use "Developer Command Prompt for Visual Studio" instead of regular PowerShell
- Or ensure MSVC is in your PATH

## Game Controls

- **Click a piece** to select it (must be your color)
- **Green circles** show valid moves for selected piece
- **Click a valid move** to move the piece
- **"New Game" button** resets the board

## Features

✓ Full chess board with proper initial piece placement
✓ 2-player gameplay (White moves first)
✓ Valid move highlighting
✓ Piece capture
✓ Turn indicator
✓ Check detection
✓ New Game functionality

## Notes

- Full checkmate and stalemate detection coming soon
- Special moves (castling, en passant, pawn promotion) can be added
- AI opponent can be implemented for single-player mode
