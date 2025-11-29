#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "Chess.h"
#include "ChessBoard.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void resetGame();
    void updateStatus();

private:
    Chess *chessGame;
    ChessBoard *boardWidget;
    QLabel *statusLabel;
    QLabel *turnIndicatorLabel;
    
    void setupUI();
    void connectSignals();
};

#endif // MAINWINDOW_H
