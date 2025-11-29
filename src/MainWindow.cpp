#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chess Game - 2 Player");
    setGeometry(100, 100, 750, 650);

    chessGame = new Chess();
    boardWidget = new ChessBoard(this);
    boardWidget->setChessGame(chessGame);

    setupUI();
    updateStatus();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout *topLayout = new QHBoxLayout();

    QPushButton *resetButton = new QPushButton("New Game", this);
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    turnIndicatorLabel = new QLabel("⚪ White's Turn", this);
    turnIndicatorLabel->setStyleSheet(
        "QLabel { "
        "font-size: 18px; "
        "font-weight: bold; "
        "color: white; "
        "background-color: #333333; "
        "padding: 8px 16px; "
        "border-radius: 4px; "
        "}"
    );
    turnIndicatorLabel->setMinimumWidth(200);

    statusLabel = new QLabel("", this);
    statusLabel->setStyleSheet("QLabel { font-size: 12px; font-weight: bold; }");

    topLayout->addWidget(resetButton);
    topLayout->addStretch();
    topLayout->addWidget(turnIndicatorLabel);
    topLayout->addWidget(statusLabel);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(boardWidget, 1);

    // Connect board signals
    connect(boardWidget, &ChessBoard::moveCompleted, this, &MainWindow::updateStatus);

    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::resetGame()
{
    boardWidget->resetBoard();
    updateStatus();
}

void MainWindow::updateStatus()
{
    if (chessGame->isCheckmate())
    {
        QString winner = (chessGame->getCurrentPlayer() == PieceColor::WHITE) 
            ? "BLACK" : "WHITE";
        turnIndicatorLabel->setText("🏁 CHECKMATE!");
        turnIndicatorLabel->setStyleSheet(
            "QLabel { "
            "font-size: 18px; "
            "font-weight: bold; "
            "color: white; "
            "background-color: #ff0000; "
            "padding: 8px 16px; "
            "border-radius: 4px; "
            "}"
        );
        statusLabel->setText(winner + " WINS!");
        statusLabel->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; color: #ff0000; }");
    }
    else
    {
        // Update turn indicator
        if (chessGame->getCurrentPlayer() == PieceColor::WHITE)
        {
            turnIndicatorLabel->setText("⚪ White's Turn");
            turnIndicatorLabel->setStyleSheet(
                "QLabel { "
                "font-size: 18px; "
                "font-weight: bold; "
                "color: white; "
                "background-color: #333333; "
                "padding: 8px 16px; "
                "border-radius: 4px; "
                "}"
            );
        }
        else
        {
            turnIndicatorLabel->setText("● Black's Turn");
            turnIndicatorLabel->setStyleSheet(
                "QLabel { "
                "font-size: 18px; "
                "font-weight: bold; "
                "color: white; "
                "background-color: #000000; "
                "padding: 8px 16px; "
                "border-radius: 4px; "
                "}"
            );
        }

        // Update status for check
        QString statusText = "";
        if (chessGame->isCheck())
        {
            statusText = "⚠️ CHECK!";
            statusLabel->setStyleSheet("QLabel { font-size: 12px; font-weight: bold; color: #ff6600; }");
        }
        else
        {
            statusLabel->setStyleSheet("QLabel { font-size: 12px; font-weight: bold; }");
        }
        statusLabel->setText(statusText);
    }
}
