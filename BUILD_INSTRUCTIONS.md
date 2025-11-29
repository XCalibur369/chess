# Chess Game - Build & Run Instructions

## Quick Start (Easiest!)

```powershell
cd C:\codebase\Chess
.\build_mingw.bat
.\run.bat
```

That's it! The game will start.

---

## Prerequisites

### 1. Install Qt 6

Download from: https://www.qt.io/download-open-source

Select:
- Qt 6.10.1 → MinGW 64-bit
- Developer Tools → MinGW 13.1.0

### 2. Install CMake

Download from: https://cmake.org/download/

Or: `choco install cmake`

---

## Game Features

✅ **Full Chess Rules** - All pieces move correctly
✅ **Turn Indicator** - Shows whose turn with colored badge
✅ **Check Detection** - Alerts player when in check
✅ **Checkmate Detection** - Declares winner
✅ **Move Validation** - Cannot move into/leave king in check
✅ **Piece Rendering** - Proper outline for white pieces
✅ **Valid Move Highlighting** - Green circles show possible moves
✅ **Capture Mechanics** - Click opponent piece to capture
✅ **New Game Button** - Reset anytime

---

## Recent Fixes (v2.0)

- ✅ Fixed piece outline rendering with shadow effect
- ✅ Improved turn indicator - now prominent and colored
- ✅ King movement validation - cannot move into check
- ✅ All moves validate king safety - prevents leaving king in check
- ✅ Checkmate detection with winner declaration
- ✅ Better UI layout and status display

---

## Build from Command Line (Manual)

```powershell
cd C:\codebase\Chess
mkdir build
cd build

cmake .. -G "MinGW Makefiles" `
  -DCMAKE_C_COMPILER="C:\Qt\Tools\mingw1310_64\bin\gcc.exe" `
  -DCMAKE_CXX_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe" `
  -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64"

mingw32-make -j4

"C:\Qt\6.10.1\mingw_64\bin\windeployqt.exe" ChessGame.exe

.\ChessGame.exe
```

---

## Troubleshooting

| Issue | Solution |
|-------|----------|
| CMake not found | Install from cmake.org or run: `choco install cmake` |
| Qt6 not found | Verify `C:\Qt\6.10.1\mingw_64` exists |
| Build fails | Check MinGW at `C:\Qt\Tools\mingw1310_64` |
| GUI won't start | Run: `windeployqt.exe ChessGame.exe` |
| Can't rebuild | Delete `build` folder and restart |

---

## How to Play

1. **Select a Piece** - Click any of your pieces (white starts)
2. **See Valid Moves** - Green circles show where you can move
3. **Move** - Click a green circle to move there
4. **Capture** - Move to opponent's piece square to capture
5. **Check!** - Status shows ⚠️ when in check
6. **Checkmate!** - Game shows 🏁 and declares winner

---

## Project Structure

```
C:\codebase\Chess\
├── CMakeLists.txt              # Build config
├── build_mingw.bat             # Quick build script
├── run.bat                      # Quick run script
├── include/
│   ├── Chess.h                 # Game logic
│   ├── ChessBoard.h            # Board widget
│   └── MainWindow.h            # Main window
└── src/
    ├── Chess.cpp               # Engine
    ├── ChessBoard.cpp          # GUI
    ├── MainWindow.cpp          # UI
    └── main.cpp                # Entry point
```

---

## Next Steps

After building, try:
- Play a complete game
- Test check and checkmate detection
- Try moving pieces and verify move validation
- Test reset button for new game

Enjoy! ♟️
