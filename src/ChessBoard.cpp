#include "ChessBoard.h"
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QMouseEvent>
#include <QtGui/QScreen>
#include <QtWidgets/QApplication>

ChessBoard::ChessBoard(QWidget *parent)
    : QWidget(parent), chessGame(nullptr), squareSize(60),
      selectedRow(-1), selectedCol(-1)
{
    setMinimumSize(520, 520);
    setMaximumSize(520, 520);
    setStyleSheet("background-color: #f0f0f0;");
    boardOffset = QPoint(10, 10);
}

void ChessBoard::setChessGame(Chess *game)
{
    chessGame = game;
    update();
}

void ChessBoard::resetBoard()
{
    if (chessGame)
    {
        chessGame->resetBoard();
        selectedRow = -1;
        selectedCol = -1;
        update();
    }
}

void ChessBoard::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawBoard(painter);
    drawHighlights(painter);
    drawPieces(painter);
}

void ChessBoard::drawBoard(QPainter &painter)
{
    QColor lightSquare(240, 217, 181);
    QColor darkSquare(181, 136, 99);

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            QRect rect = getSquareRect(row, col);
            QColor squareColor = ((row + col) % 2 == 0) ? lightSquare : darkSquare;
            painter.fillRect(rect, squareColor);
            painter.drawRect(rect);
        }
    }
}

void ChessBoard::drawHighlights(QPainter &painter)
{
    if (!chessGame)
        return;

    // Highlight king in red if in check
    if (chessGame->isCheck())
    {
        // Find the king's position
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                const Piece &piece = chessGame->getPiece(row, col);
                if (piece.type == PieceType::KING && piece.color == chessGame->getCurrentPlayer())
                {
                    QRect kingRect = getSquareRect(row, col);
                    painter.fillRect(kingRect, QColor(255, 0, 0, 150));
                    painter.drawRect(kingRect);
                }
            }
        }
    }

    if (selectedRow >= 0 && selectedCol >= 0)
    {
        QRect selectedRect = getSquareRect(selectedRow, selectedCol);
        painter.fillRect(selectedRect, QColor(255, 255, 0, 100));
        painter.drawRect(selectedRect);

        // Draw valid moves
        if (chessGame)
        {
            auto validMoves = chessGame->getValidMoves(selectedRow, selectedCol);
            painter.setBrush(QColor(0, 255, 0, 100));
            
            for (const auto &move : validMoves)
            {
                QRect moveRect = getSquareRect(move.first, move.second);
                int centerX = moveRect.center().x();
                int centerY = moveRect.center().y();
                
                // Check if this square has an opponent's piece (capturable)
                const Piece &targetPiece = chessGame->getPiece(move.first, move.second);
                if (!targetPiece.isEmpty() && targetPiece.color != chessGame->getCurrentPlayer())
                {
                    // Draw larger green dot for capturable pieces
                    painter.setBrush(QColor(0, 255, 0, 180));
                    painter.setPen(Qt::green);
                    painter.drawEllipse(centerX - 8, centerY - 8, 16, 16);
                }
                else
                {
                    // Draw smaller green dot for empty squares
                    painter.setBrush(QColor(0, 255, 0, 150));
                    painter.setPen(Qt::darkGreen);
                    painter.drawEllipse(centerX - 5, centerY - 5, 10, 10);
                }
            }
        }
    }
    
    // Also highlight capturable opponent pieces even without selection
    if (chessGame && selectedRow < 0 && selectedCol < 0)
    {
        for (int row = 0; row < 8; ++row)
        {
            for (int col = 0; col < 8; ++col)
            {
                const Piece &piece = chessGame->getPiece(row, col);
                // Highlight opponent pieces that can be captured by current player
                if (!piece.isEmpty() && piece.color != chessGame->getCurrentPlayer())
                {
                    // Check if any piece of current player can capture this piece
                    for (int fromRow = 0; fromRow < 8; ++fromRow)
                    {
                        for (int fromCol = 0; fromCol < 8; ++fromCol)
                        {
                            const Piece &myPiece = chessGame->getPiece(fromRow, fromCol);
                            if (!myPiece.isEmpty() && myPiece.color == chessGame->getCurrentPlayer())
                            {
                                if (chessGame->isValidMove(fromRow, fromCol, row, col))
                                {
                                    // This piece can be captured - draw a small green indicator
                                    QRect captureRect = getSquareRect(row, col);
                                    int centerX = captureRect.center().x();
                                    int centerY = captureRect.center().y();
                                    painter.setBrush(QColor(0, 200, 0, 120));
                                    painter.setPen(Qt::darkGreen);
                                    painter.drawEllipse(centerX - 3, centerY - 3, 6, 6);
                                    goto next_piece;  // Move to next piece to avoid overlapping dots
                                }
                            }
                        }
                    }
                    next_piece:;
                }
            }
        }
    }
}

void ChessBoard::drawPieces(QPainter &painter)
{
    if (!chessGame)
        return;

    QFont font("Arial", 36, QFont::Bold);
    painter.setFont(font);

    for (int row = 0; row < 8; ++row)
    {
        for (int col = 0; col < 8; ++col)
        {
            const Piece &piece = chessGame->getPiece(row, col);
            if (!piece.isEmpty())
            {
                QRect rect = getSquareRect(row, col);
                QString symbol = getPieceSymbol(piece);

                if (piece.color == PieceColor::BLACK)
                {
                    // Black pieces: solid black
                    painter.setPen(Qt::black);
                    painter.drawText(rect, Qt::AlignCenter, symbol);
                }
                else
                {
                    // White pieces: draw with black outline for contrast
                    int centerX = rect.center().x();
                    int centerY = rect.center().y();
                    
                    // Draw black outline (shadow effect)
                    painter.setPen(QPen(Qt::black, 2));
                    for (int dx = -2; dx <= 2; ++dx)
                    {
                        for (int dy = -2; dy <= 2; ++dy)
                        {
                            if (dx != 0 || dy != 0)
                            {
                                QRect offsetRect = rect.translated(dx, dy);
                                painter.drawText(offsetRect, Qt::AlignCenter, symbol);
                            }
                        }
                    }
                    
                    // Draw white text on top
                    painter.setPen(Qt::white);
                    painter.drawText(rect, Qt::AlignCenter, symbol);
                }
            }
        }
    }
}

void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    if (!chessGame)
        return;

    int row, col;
    getSquareFromPoint(event->pos(), row, col);

    if (row < 0 || row >= 8 || col < 0 || col >= 8)
    {
        selectedRow = -1;
        selectedCol = -1;
        update();
        return;
    }

    // If clicking an empty square or opponent's piece, deselect
    const Piece &clickedPiece = chessGame->getPiece(row, col);

    if (selectedRow >= 0 && selectedCol >= 0)
    {
        // Try to move
        if (row != selectedRow || col != selectedCol)
        {
            if (chessGame->movePiece(selectedRow, selectedCol, row, col))
            {
                // Check if pawn promotion is needed
                const Piece &movedPiece = chessGame->getPiece(row, col);
                if (movedPiece.type == PieceType::PAWN && 
                    ((movedPiece.color == PieceColor::WHITE && row == 0) ||
                     (movedPiece.color == PieceColor::BLACK && row == 7)))
                {
                    // Emit promotion signal
                    emit promotionNeeded(row, col);
                }
                
                selectedRow = -1;
                selectedCol = -1;
                update();
                emit moveCompleted();
                return;
            }
        }
    }

    // Select piece if it belongs to current player
    if (!clickedPiece.isEmpty() && clickedPiece.color == chessGame->getCurrentPlayer())
    {
        selectedRow = row;
        selectedCol = col;
    }
    else
    {
        selectedRow = -1;
        selectedCol = -1;
    }

    update();
}

void ChessBoard::getSquareFromPoint(const QPoint &point, int &row, int &col) const
{
    col = (point.x() - boardOffset.x()) / squareSize;
    row = (point.y() - boardOffset.y()) / squareSize;
}

QRect ChessBoard::getSquareRect(int row, int col) const
{
    int x = boardOffset.x() + col * squareSize;
    int y = boardOffset.y() + row * squareSize;
    return QRect(x, y, squareSize, squareSize);
}

QString ChessBoard::getPieceSymbol(const Piece &piece) const
{
    switch (piece.type)
    {
    case PieceType::PAWN:
        return "♟";
    case PieceType::ROOK:
        return "♜";
    case PieceType::KNIGHT:
        return "♞";
    case PieceType::BISHOP:
        return "♝";
    case PieceType::QUEEN:
        return "♛";
    case PieceType::KING:
        return "♚";
    default:
        return "";
    }
}
