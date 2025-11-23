# Chess Game (C++ + Qt 6)

A simple 2-player chess game built using **C++**, **Qt 6**, and **CMake**, featuring a clean graphical user interface and fully working chess movement logic.

---

## Features

- Full chess board with proper piece placement
- 2-player gameplay (White & Black)
- Click-based piece selection
- Green circle indicators for valid moves
- Capture system
- Turn indicator
- Check detection
- Reset / New Game option

---

## Requirements

- **Qt 6.10.1 (MinGW 64-bit)**
- **MinGW 13.1.0** (bundled with Qt)
- **CMake 3.16+**

**MSVC builds are NOT supported.  
This project must be built using MinGW.**

---

## 🛠 Installation & Setup (Windows + MinGW)

### 1️. Install Qt 6

Download the Qt Online Installer:

https://www.qt.io/download-open-source

During installation, select:

- **Qt → 6.10.1 → MinGW 64-bit**
- **Developer Tools → MinGW 13.1.0**

❗ Do NOT install MSVC toolchains.

---

## Building the Project (MinGW Only)

### 2️. Create Build Directory

````sh
cd "path/to/chess"
mkdir build
cd build


### Step 3: Configure with CMake (MinGW Generator)

```powershell
cmake .. -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER="C:/Qt/Tools/mingw1310_64/bin/gcc.exe" ^
  -DCMAKE_CXX_COMPILER="C:/Qt/Tools/mingw1310_64/bin/g++.exe" ^
  -DCMAKE_PREFIX_PATH="C:/Qt/6.10.1/mingw_64"

````

## 4. Build

Run the following commands in powershell to compile and run the program.

mingw32-make
build/ChessGame.exe

If Qt DLLs are missing → run the deployment step below.

📦 Deploying Qt Libraries (Required for .exe)
"C:/Qt/6.10.1/mingw_64/bin/windeployqt.exe" "path/to/chess/build/ChessGame.exe"

This copies required DLLs:

Qt6Core.dll

Qt6Gui.dll

Qt6Widgets.dll

platforms/qwindows.dll

image plugins

After deployment, the .exe can run anywhere.

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

## License

This project is provided as-is for educational purposes.
