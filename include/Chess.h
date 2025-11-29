#ifndef CHESS_H
#define CHESS_H

#include <array>
#include <vector>
#include <utility>

enum class PieceType {
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

enum class PieceColor {
    WHITE,
    BLACK,
    NONE
};

struct Piece {
    PieceType type;
    PieceColor color;
    
    Piece(PieceType t = PieceType::EMPTY, PieceColor c = PieceColor::NONE)
        : type(t), color(c) {}
    
    bool isEmpty() const { return type == PieceType::EMPTY; }
};

class Chess {
public:
    Chess();
    
    // Board management
    void resetBoard();
    const Piece& getPiece(int row, int col) const;
    void setPiece(int row, int col, const Piece& piece);
    
    // Move validation
    bool isValidMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool movePiece(int fromRow, int fromCol, int toRow, int toCol);
    void promotePawn(int row, int col, PieceType newType);
    
    // Game state
    PieceColor getCurrentPlayer() const;
    bool isGameOver() const;
    bool isCheckmate() const;
    bool isStalemate() const;
    bool isCheck() const;
    bool hasAnyLegalMove(PieceColor color) const;
    
    // Helper methods
    std::vector<std::pair<int, int>> getValidMoves(int row, int col) const;
    
private:
    mutable std::array<std::array<Piece, 8>, 8> board;
    PieceColor currentPlayer;
    
    // Move validation helpers
    bool isPathClear(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canPieceMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canPawnMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canKnightMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canBishopMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canRookMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canQueenMove(int fromRow, int fromCol, int toRow, int toCol) const;
    bool canKingMove(int fromRow, int fromCol, int toRow, int toCol) const;
    
    bool isKingInCheck(PieceColor color) const;
    int findKingPosition(PieceColor color) const;
    bool isSquareAttacked(int row, int col, PieceColor byColor) const;
};

#endif // CHESS_H
