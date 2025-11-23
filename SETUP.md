# Quick Start Guide – Chess Game (Qt 6 + MinGW + CMake)

## Prerequisites

### ✅ Install Qt 6 (Required)

Download from: https://www.qt.io/download-open-source

During installation, select ONLY:

- **Qt → 6.10.1 → MinGW 64-bit**
- **Developer Tools → MinGW 13.1.0**

⚠️ **Do NOT install MSVC toolchains**  
⚠️ **Qt MSVC builds will NOT work for this project**

---

# Building on Windows (MinGW Only)

## 1. Install CMake

```sh
choco install cmake
```

Or download from: https://cmake.org

---

## 2. Create the Build Directory

```sh
cd "PATH_TO_PROJECT\chess-main"
mkdir build
cd build
```

---

## 3. Configure CMake (Using MinGW Generator)

```sh
cmake .. -G "MinGW Makefiles" ^
  -DCMAKE_C_COMPILER="C:\Qt\Tools\mingw1310_64\bin\gcc.exe" ^
  -DCMAKE_CXX_COMPILER="C:\Qt\Tools\mingw1310_64\bin\g++.exe" ^
  -DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64"
```

This generates Makefiles compatible with MinGW.

---

## 4. Build the Project

```sh
mingw32-make
```

After a successful build, the executable will appear at:

```
PATH_TO_PROJECT\chess-main\build\ChessGame.exe
```

---

## 5. Run the Game (PowerShell)

PowerShell requires `.\` before the filename:

```sh
.\ChessGame.exe
```

If it doesn’t run due to missing Qt DLLs, use deployment below.

---

# Deploying Qt Libraries (Required)

Run Qt's deployment tool:

```sh
"C:\Qt\6.10.1\mingw_64\bin\windeployqt.exe" "PATH_TO_PROJECT\chess-main\build\ChessGame.exe"
```

This copies required files like:

- Qt6Core.dll
- Qt6Gui.dll
- Qt6Widgets.dll
- platforms/qwindows.dll
- image plugins

After this, `ChessGame.exe` will run anywhere.

---

# Rebuilding After Code Changes

If you modify `.cpp` or `.h` files:

```sh
cd build
mingw32-make
.\ChessGame.exe
```

### Run CMake again only if:

- You add/remove source files
- You modify `CMakeLists.txt`
- You change Qt modules

Otherwise, `mingw32-make` alone is enough.

---

# Troubleshooting

### ❌ “Qt6 not found”

Check your prefix path:

```sh
-DCMAKE_PREFIX_PATH="C:\Qt\6.10.1\mingw_64"
```

### ❌ Build fails with MSVC errors

This project must use **MinGW**, not MSVC.

### ❌ GUI does not appear after building

Run:

```sh
windeployqt.exe ChessGame.exe
```

---

# Game Controls

- Click a piece → select it
- Green circles → valid moves
- Click a valid square → move
- **New Game** → resets everything

---

# Features

- ✓ Full chess board
- ✓ Legal move display
- ✓ Capture handling
- ✓ Turn system
- ✓ Check detection
- ✓ Reset button
