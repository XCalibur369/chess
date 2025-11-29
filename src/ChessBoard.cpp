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
                painter.drawEllipse(centerX - 5, centerY - 5, 10, 10);
            }
        }
    }
}

void ChessBoard::drawPieces(QPainter &painter)
{
    if (!chessGame)
        return;

    QFont font("Arial", 32, QFont::Bold);
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

                // Draw black pieces in black
                if (piece.color == PieceColor::BLACK)
                {
                    painter.setPen(Qt::black);
                    painter.drawText(rect, Qt::AlignCenter, symbol);
                }
                // Draw white pieces with outline for contrast
                else
                {
                    painter.setPen(Qt::black);
                    // Draw outline
                    QPainterPath path;
                    path.addText(rect.center().x() - 18, rect.center().y() + 12, font, symbol);
                    painter.drawPath(path);
                    // Draw filled white
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
