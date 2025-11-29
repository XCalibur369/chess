#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPoint>
#include "Chess.h"

class ChessBoard : public QWidget {
    Q_OBJECT

public:
    ChessBoard(QWidget *parent = nullptr);
    
    void setChessGame(Chess *game);
    void resetBoard();
    
signals:
    void moveCompleted();
    void promotionNeeded(int row, int col);
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    
private:
    Chess *chessGame;
    int squareSize;
    int selectedRow;
    int selectedCol;
    
    QPoint boardOffset;
    
    void drawBoard(QPainter &painter);
    void drawPieces(QPainter &painter);
    void drawHighlights(QPainter &painter);
    
    void getSquareFromPoint(const QPoint &point, int &row, int &col) const;
    QRect getSquareRect(int row, int col) const;
    
    QString getPieceSymbol(const Piece &piece) const;
};

#endif // CHESSBOARD_H
