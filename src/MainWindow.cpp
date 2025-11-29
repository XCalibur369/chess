#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStatusBar>
#include <QWidget>
#include <QDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), promotionRow(-1), promotionCol(-1)
{
    setWindowTitle("Chess Game - 2 Player");
    setGeometry(100, 100, 900, 800);

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
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Top bar with buttons - uniform style and size
    QHBoxLayout *topLayout = new QHBoxLayout();
    topLayout->setSpacing(15);

    QPushButton *resetButton = new QPushButton("New Game", this);
    resetButton->setMinimumSize(120, 45);
    resetButton->setStyleSheet(
        "QPushButton { "
        "font-size: 14px; "
        "font-weight: bold; "
        "color: white; "
        "background-color: #333333; "
        "border: none; "
        "border-radius: 4px; "
        "padding: 8px 16px; "
        "} "
        "QPushButton:hover { background-color: #005a9e; } "
        "QPushButton:pressed { background-color: #003d6b; }"
    );
    connect(resetButton, &QPushButton::clicked, this, &MainWindow::resetGame);

    turnIndicatorLabel = new QLabel("⚪ White's Turn", this);
    turnIndicatorLabel->setMinimumSize(200, 45);
    turnIndicatorLabel->setAlignment(Qt::AlignCenter);
    turnIndicatorLabel->setStyleSheet(
        "QLabel { "
        "font-size: 16px; "
        "font-weight: bold; "
        "color: white; "
        "background-color: #333333; "
        "border-radius: 4px; "
        "}"
    );

    topLayout->addWidget(resetButton);
    topLayout->addStretch();
    topLayout->addWidget(turnIndicatorLabel);

    mainLayout->addLayout(topLayout);

    // Centered board with checkmate overlay
    QWidget *boardContainer = new QWidget(this);
    QVBoxLayout *containerLayout = new QVBoxLayout(boardContainer);
    containerLayout->setContentsMargins(0, 0, 0, 0);

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "QLabel { "
        "font-size: 24px; "
        "font-weight: bold; "
        "color: #333333; "
        "background-color: rgba(255, 0, 0, 180); "
        "border-radius: 8px; "
        "padding: 8px 20px; "
        "}"
    );
    statusLabel->setMinimumHeight(100);
    statusLabel->setVisible(false);

    containerLayout->addWidget(statusLabel, 0, Qt::AlignCenter | Qt::AlignTop);
    containerLayout->addStretch();
    containerLayout->addWidget(boardWidget, 0, Qt::AlignCenter);
    containerLayout->addStretch();

    mainLayout->addWidget(boardContainer, 1);

    // Connect board signals
    connect(boardWidget, &ChessBoard::moveCompleted, this, &MainWindow::updateStatus);
    connect(boardWidget, &ChessBoard::promotionNeeded, this, &MainWindow::handlePromotion);

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
        
        // Show large checkmate message on top
        statusLabel->setText("🏁 CHECKMATE!\n" + winner + " WINS! 🏁");
        statusLabel->setVisible(true);
        
        // Update turn indicator with checkmate style
        turnIndicatorLabel->setText("GAME OVER");
        turnIndicatorLabel->setStyleSheet(
            "QLabel { "
            "font-size: 16px; "
            "font-weight: bold; "
            "color: white; "
            "background-color: #ff0000; "
            "border-radius: 4px; "
            "}"
        );
    }
    else if (chessGame->isStalemate())
    {
        // Show large stalemate message on top
        statusLabel->setText("🏁 STALEMATE!\nDRAW! 🏁");
        statusLabel->setVisible(true);
        
        // Update turn indicator with stalemate style
        turnIndicatorLabel->setText("GAME OVER");
        turnIndicatorLabel->setStyleSheet(
            "QLabel { "
            "font-size: 16px; "
            "font-weight: bold; "
            "color: white; "
            "background-color: #ffa500; "
            "border-radius: 4px; "
            "}"
        );
    }
    else
    {
        statusLabel->setVisible(false);
        
        // Update turn indicator
        if (chessGame->getCurrentPlayer() == PieceColor::WHITE)
        {
            turnIndicatorLabel->setText("⚪ White's Turn");
            turnIndicatorLabel->setStyleSheet(
                "QLabel { "
                "font-size: 16px; "
                "font-weight: bold; "
                "color: white; "
                "background-color: #333333; "
                "border-radius: 4px; "
                "}"
            );
        }
        else
        {
            turnIndicatorLabel->setText("● Black's Turn");
            turnIndicatorLabel->setStyleSheet(
                "QLabel { "
                "font-size: 16px; "
                "font-weight: bold; "
                "color: white; "
                "background-color: #000000; "
                "border-radius: 4px; "
                "}"
            );
        }

        // Update check status
        if (chessGame->isCheck())
        {
            turnIndicatorLabel->setText(
                (chessGame->getCurrentPlayer() == PieceColor::WHITE)
                    ? "⚪ White's Turn\n⚠️ CHECK!"
                    : "● Black's Turn\n⚠️ CHECK!"
            );
        }
    }
}

void MainWindow::handlePromotion(int row, int col)
{
    QDialog promotionDialog(this);
    promotionDialog.setWindowTitle("Pawn Promotion");
    promotionDialog.setWindowFlags(promotionDialog.windowFlags() | Qt::WindowStaysOnTopHint);
    promotionDialog.setMinimumWidth(350);

    QVBoxLayout *layout = new QVBoxLayout(&promotionDialog);
    
    QLabel *label = new QLabel("Choose a piece to promote your pawn to:", &promotionDialog);
    label->setStyleSheet("font-size: 13px; font-weight: bold;");
    layout->addWidget(label);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    // Knight button
    QPushButton *knightBtn = new QPushButton("♘ Knight", &promotionDialog);
    knightBtn->setMinimumSize(70, 50);
    knightBtn->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #4CAF50; color: white; border: none; border-radius: 4px; }"
        "QPushButton:hover { background-color: #45a049; }"
    );
    connect(knightBtn, &QPushButton::clicked, [this, row, col, &promotionDialog]() {
        chessGame->promotePawn(row, col, PieceType::KNIGHT);
        boardWidget->update();
        updateStatus();
        promotionDialog.accept();
    });
    buttonsLayout->addWidget(knightBtn);

    // Bishop button
    QPushButton *bishopBtn = new QPushButton("♗ Bishop", &promotionDialog);
    bishopBtn->setMinimumSize(70, 50);
    bishopBtn->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #2196F3; color: white; border: none; border-radius: 4px; }"
        "QPushButton:hover { background-color: #0b7dda; }"
    );
    connect(bishopBtn, &QPushButton::clicked, [this, row, col, &promotionDialog]() {
        chessGame->promotePawn(row, col, PieceType::BISHOP);
        boardWidget->update();
        updateStatus();
        promotionDialog.accept();
    });
    buttonsLayout->addWidget(bishopBtn);

    // Rook button
    QPushButton *rookBtn = new QPushButton("♖ Rook", &promotionDialog);
    rookBtn->setMinimumSize(70, 50);
    rookBtn->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #FF9800; color: white; border: none; border-radius: 4px; }"
        "QPushButton:hover { background-color: #e68900; }"
    );
    connect(rookBtn, &QPushButton::clicked, [this, row, col, &promotionDialog]() {
        chessGame->promotePawn(row, col, PieceType::ROOK);
        boardWidget->update();
        updateStatus();
        promotionDialog.accept();
    });
    buttonsLayout->addWidget(rookBtn);

    // Queen button (default - most powerful)
    QPushButton *queenBtn = new QPushButton("♕ Queen", &promotionDialog);
    queenBtn->setMinimumSize(70, 50);
    queenBtn->setStyleSheet(
        "QPushButton { font-size: 16px; background-color: #f44336; color: white; border: none; border-radius: 4px; font-weight: bold; }"
        "QPushButton:hover { background-color: #da190b; }"
    );
    connect(queenBtn, &QPushButton::clicked, [this, row, col, &promotionDialog]() {
        chessGame->promotePawn(row, col, PieceType::QUEEN);
        boardWidget->update();
        updateStatus();
        promotionDialog.accept();
    });
    buttonsLayout->addWidget(queenBtn);

    layout->addLayout(buttonsLayout);
    
    // Set Queen as default (selected on Enter)
    queenBtn->setDefault(true);
    queenBtn->setFocus();

    promotionDialog.setLayout(layout);
    promotionDialog.exec();
}

