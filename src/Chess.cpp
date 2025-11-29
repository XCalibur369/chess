#include "Chess.h"
#include <cmath>
#include <algorithm>

Chess::Chess() : currentPlayer(PieceColor::WHITE) {
    resetBoard();
}

void Chess::resetBoard() {
    // Clear board
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = Piece();
        }
    }
    
    // Setup white pieces (bottom)
    board[7][0] = Piece(PieceType::ROOK, PieceColor::WHITE);
    board[7][1] = Piece(PieceType::KNIGHT, PieceColor::WHITE);
    board[7][2] = Piece(PieceType::BISHOP, PieceColor::WHITE);
    board[7][3] = Piece(PieceType::QUEEN, PieceColor::WHITE);
    board[7][4] = Piece(PieceType::KING, PieceColor::WHITE);
    board[7][5] = Piece(PieceType::BISHOP, PieceColor::WHITE);
    board[7][6] = Piece(PieceType::KNIGHT, PieceColor::WHITE);
    board[7][7] = Piece(PieceType::ROOK, PieceColor::WHITE);
    
    for (int j = 0; j < 8; ++j) {
        board[6][j] = Piece(PieceType::PAWN, PieceColor::WHITE);
    }
    
    // Setup black pieces (top)
    board[0][0] = Piece(PieceType::ROOK, PieceColor::BLACK);
    board[0][1] = Piece(PieceType::KNIGHT, PieceColor::BLACK);
    board[0][2] = Piece(PieceType::BISHOP, PieceColor::BLACK);
    board[0][3] = Piece(PieceType::QUEEN, PieceColor::BLACK);
    board[0][4] = Piece(PieceType::KING, PieceColor::BLACK);
    board[0][5] = Piece(PieceType::BISHOP, PieceColor::BLACK);
    board[0][6] = Piece(PieceType::KNIGHT, PieceColor::BLACK);
    board[0][7] = Piece(PieceType::ROOK, PieceColor::BLACK);
    
    for (int j = 0; j < 8; ++j) {
        board[1][j] = Piece(PieceType::PAWN, PieceColor::BLACK);
    }
    
    currentPlayer = PieceColor::WHITE;
}

const Piece& Chess::getPiece(int row, int col) const {
    static Piece emptyPiece;
    if (row < 0 || row >= 8 || col < 0 || col >= 8) {
        return emptyPiece;
    }
    return board[row][col];
}

void Chess::setPiece(int row, int col, const Piece& piece) {
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        board[row][col] = piece;
    }
}

bool Chess::isValidMove(int fromRow, int fromCol, int toRow, int toCol) const {
    // Check bounds
    if (fromRow < 0 || fromRow >= 8 || fromCol < 0 || fromCol >= 8 ||
        toRow < 0 || toRow >= 8 || toCol < 0 || toCol >= 8) {
        return false;
    }
    
    const Piece& piece = board[fromRow][fromCol];
    const Piece& targetPiece = board[toRow][toCol];
    
    // Check if piece exists and belongs to current player
    if (piece.isEmpty() || piece.color != currentPlayer) {
        return false;
    }
    
    // Check if target is not the same color
    if (!targetPiece.isEmpty() && targetPiece.color == piece.color) {
        return false;
    }
    
    // Check if move is valid for the piece type
    if (!canPieceMove(fromRow, fromCol, toRow, toCol)) {
        return false;
    }
    
    // Simulate the move and check if it leaves the king in check
    Piece originalPiece = board[fromRow][fromCol];
    Piece capturedPiece = board[toRow][toCol];
    board[toRow][toCol] = originalPiece;
    board[fromRow][fromCol] = Piece();
    
    // Check if king is in check after this move
    bool kingInCheck = isKingInCheck(currentPlayer);
    
    // Undo the move
    board[fromRow][fromCol] = originalPiece;
    board[toRow][toCol] = capturedPiece;
    
    // Move is valid only if king is not in check after it
    return !kingInCheck;
}

bool Chess::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    if (!isValidMove(fromRow, fromCol, toRow, toCol)) {
        return false;
    }
    
    Piece piece = board[fromRow][fromCol];
    board[toRow][toCol] = piece;
    board[fromRow][fromCol] = Piece();
    
    // Switch player
    currentPlayer = (currentPlayer == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    
    return true;
}

PieceColor Chess::getCurrentPlayer() const {
    return currentPlayer;
}

bool Chess::isGameOver() const {
    return isCheckmate();
}

bool Chess::isCheckmate() const {
    // Current player is in checkmate if:
    // 1. King is in check
    // 2. Player has no legal moves
    return isKingInCheck(currentPlayer) && !hasAnyLegalMove(currentPlayer);
}

bool Chess::isCheck() const {
    return isKingInCheck(currentPlayer);
}

std::vector<std::pair<int, int>> Chess::getValidMoves(int row, int col) const {
    std::vector<std::pair<int, int>> moves;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (isValidMove(row, col, i, j)) {
                moves.push_back({i, j});
            }
        }
    }
    
    return moves;
}

bool Chess::canPieceMove(int fromRow, int fromCol, int toRow, int toCol) const {
    if (fromRow == toRow && fromCol == toCol) {
        return false;
    }
    
    const Piece& piece = board[fromRow][fromCol];
    
    switch (piece.type) {
        case PieceType::PAWN:
            return canPawnMove(fromRow, fromCol, toRow, toCol);
        case PieceType::KNIGHT:
            return canKnightMove(fromRow, fromCol, toRow, toCol);
        case PieceType::BISHOP:
            return canBishopMove(fromRow, fromCol, toRow, toCol);
        case PieceType::ROOK:
            return canRookMove(fromRow, fromCol, toRow, toCol);
        case PieceType::QUEEN:
            return canQueenMove(fromRow, fromCol, toRow, toCol);
        case PieceType::KING:
            return canKingMove(fromRow, fromCol, toRow, toCol);
        default:
            return false;
    }
}

bool Chess::isPathClear(int fromRow, int fromCol, int toRow, int toCol) const {
    int rowDir = 0, colDir = 0;
    
    if (toRow > fromRow) rowDir = 1;
    else if (toRow < fromRow) rowDir = -1;
    
    if (toCol > fromCol) colDir = 1;
    else if (toCol < fromCol) colDir = -1;
    
    int r = fromRow + rowDir;
    int c = fromCol + colDir;
    
    while (r != toRow || c != toCol) {
        if (!board[r][c].isEmpty()) {
            return false;
        }
        r += rowDir;
        c += colDir;
    }
    
    return true;
}

bool Chess::canPawnMove(int fromRow, int fromCol, int toRow, int toCol) const {
    const Piece& piece = board[fromRow][fromCol];
    const Piece& target = board[toRow][toCol];
    
    int direction = (piece.color == PieceColor::WHITE) ? -1 : 1;
    int startRow = (piece.color == PieceColor::WHITE) ? 6 : 1;
    
    // Forward move
    if (fromCol == toCol) {
        if (toRow == fromRow + direction && target.isEmpty()) {
            return true;
        }
        // Two squares from start
        if (fromRow == startRow && toRow == fromRow + 2 * direction && 
            target.isEmpty() && board[fromRow + direction][fromCol].isEmpty()) {
            return true;
        }
    }
    
    // Capture
    if (std::abs(toCol - fromCol) == 1 && toRow == fromRow + direction && !target.isEmpty()) {
        return true;
    }
    
    return false;
}

bool Chess::canKnightMove(int fromRow, int fromCol, int toRow, int toCol) const {
    int rowDiff = std::abs(toRow - fromRow);
    int colDiff = std::abs(toCol - fromCol);
    return (rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2);
}

bool Chess::canBishopMove(int fromRow, int fromCol, int toRow, int toCol) const {
    if (std::abs(toRow - fromRow) != std::abs(toCol - fromCol)) {
        return false;
    }
    return isPathClear(fromRow, fromCol, toRow, toCol);
}

bool Chess::canRookMove(int fromRow, int fromCol, int toRow, int toCol) const {
    if (fromRow != toRow && fromCol != toCol) {
        return false;
    }
    return isPathClear(fromRow, fromCol, toRow, toCol);
}

bool Chess::canQueenMove(int fromRow, int fromCol, int toRow, int toCol) const {
    return canBishopMove(fromRow, fromCol, toRow, toCol) || 
           canRookMove(fromRow, fromCol, toRow, toCol);
}

bool Chess::canKingMove(int fromRow, int fromCol, int toRow, int toCol) const {
    return std::abs(toRow - fromRow) <= 1 && std::abs(toCol - fromCol) <= 1;
}

bool Chess::isKingInCheck(PieceColor color) const {
    int kingPos = findKingPosition(color);
    if (kingPos == -1) return false;
    
    int kingRow = kingPos / 8;
    int kingCol = kingPos % 8;
    
    PieceColor opponent = (color == PieceColor::WHITE) ? PieceColor::BLACK : PieceColor::WHITE;
    return isSquareAttacked(kingRow, kingCol, opponent);
}

int Chess::findKingPosition(PieceColor color) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j].type == PieceType::KING && board[i][j].color == color) {
                return i * 8 + j;
            }
        }
    }
    return -1;
}

bool Chess::isSquareAttacked(int row, int col, PieceColor byColor) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const Piece& piece = board[i][j];
            if (!piece.isEmpty() && piece.color == byColor) {
                if (canPieceMove(i, j, row, col)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Chess::hasAnyLegalMove(PieceColor color) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            const Piece& piece = board[i][j];
            if (!piece.isEmpty() && piece.color == color) {
                // Check all possible moves for this piece
                for (int toRow = 0; toRow < 8; ++toRow) {
                    for (int toCol = 0; toCol < 8; ++toCol) {
                        // Try the move
                        const Piece& targetPiece = board[toRow][toCol];
                        
                        // Check if move is valid
                        if (!targetPiece.isEmpty() && targetPiece.color == color) {
                            continue; // Can't capture own piece
                        }
                        
                        if (!canPieceMove(i, j, toRow, toCol)) {
                            continue;
                        }
                        
                        // Simulate the move
                        Piece originalPiece = board[i][j];
                        Piece capturedPiece = board[toRow][toCol];
                        board[toRow][toCol] = originalPiece;
                        board[i][j] = Piece();
                        
                        // Check if king is still in check after this move
                        bool kingInCheck = isKingInCheck(color);
                        
                        // Undo the move
                        board[i][j] = originalPiece;
                        board[toRow][toCol] = capturedPiece;
                        
                        // If this move leaves king safe, it's a legal move
                        if (!kingInCheck) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

