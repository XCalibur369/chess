#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Chess Game");
    setGeometry(100, 100, 900, 600);

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

    statusLabel = new QLabel("White's Turn", this);
    statusLabel->setStyleSheet("QLabel { font-size: 14px; font-weight: bold; }");

    topLayout->addWidget(resetButton);
    topLayout->addStretch();
    topLayout->addWidget(statusLabel);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(boardWidget, 1);

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
    QString playerText = (chessGame->getCurrentPlayer() == PieceColor::WHITE)
                             ? "White's Turn"
                             : "Black's Turn";

    if (chessGame->isCheck())
    {
        playerText += " (Check!)";
    }

    statusLabel->setText(playerText);
}
