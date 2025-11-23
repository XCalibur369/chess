# Chess Game

A simple 2-player chess game built with C++ and Qt framework, featuring a graphical user interface.

## Features

- Full chess board with proper piece placement
- 2-player gameplay (White and Black)
- Click-based piece selection and movement
- Valid move highlighting and visualization
- Turn indicator showing current player
- Check detection
- Reset/New Game functionality

## Prerequisites

- C++ compiler (GCC, Clang, MSVC)
- CMake 3.16 or higher
- Qt 5 (Core, GUI, Widgets)

### Installing Qt on Windows

1. **Using vcpkg** (Recommended):
   ```powershell
   git clone https://github.com/Microsoft/vcpkg.git
   cd vcpkg
   .\vcpkg integrate install
   .\vcpkg install qt5:x64-windows
   ```

2. **Using Qt Online Installer**:
   - Download from https://www.qt.io/download
   - Install Qt 5.15.x or later

## Building the Project

### Step 1: Configure with CMake

```powershell
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake
```

Or if using Qt installed via online installer:
```powershell
mkdir build
cd build
cmake .. -DCMAKE_PREFIX_PATH="C:\Qt\5.15.x\msvc2019_64"
```

### Step 2: Build

```powershell
cmake --build . --config Release
```

### Step 3: Run

```powershell
.\Release\ChessGame.exe
```

## How to Play

1. **Select a Piece**: Click on any of your pieces (white pieces move first)
2. **View Valid Moves**: Selected pieces show valid moves as green circles
3. **Move a Piece**: Click on a highlighted square to move your piece
4. **Capture**: Move to a square with an opponent's piece to capture it
5. **New Game**: Click the "New Game" button to reset the board

## Game Rules Implemented

- **Pawns**: Move forward 1 square, or 2 squares on first move. Capture diagonally.
- **Rooks**: Move any number of squares horizontally or vertically.
- **Knights**: Move in an L-shape (2+1 squares).
- **Bishops**: Move any number of squares diagonally.
- **Queens**: Move any number of squares horizontally, vertically, or diagonally.
- **Kings**: Move one square in any direction.
- **Check Detection**: Game alerts when a king is in check.

## Project Structure

```
.
├── CMakeLists.txt           # Build configuration
├── include/
│   ├── Chess.h             # Game logic and piece definitions
│   ├── ChessBoard.h        # Board widget and rendering
│   └── MainWindow.h        # Main application window
└── src/
    ├── Chess.cpp           # Chess engine implementation
    ├── ChessBoard.cpp      # Board widget implementation
    ├── MainWindow.cpp      # Main window implementation
    └── main.cpp            # Application entry point
```

## Future Enhancements

- En passant and castling moves
- Pawn promotion
- Checkmate detection
- Move history/undo
- AI opponent
- Save/Load game functionality
- Move validation with check evasion
- Stalemate detection

## License

This project is provided as-is for educational purposes.
