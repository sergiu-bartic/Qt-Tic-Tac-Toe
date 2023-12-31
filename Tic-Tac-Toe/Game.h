#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QPushButton>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget*parent=0);

    // public methods
    void displayMainMenu();
    void gameOver();
    void displayGameOver(QString textToDisplay);
    QString getPlayerTurn();
    void setPlayerTurn(QString player);
    void nextPlayerTurn();

    // public attributes
    QGraphicsScene* scene;
    int nr = 0;

public slots:
    void start();
    void buttonClicked();
    void restartGame();

private:
    // private methods
    void drawGUI();
    void checkWinner();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity);

    // private attributes
    QPushButton *buttons[9];
    QPushButton *restartButton;
    QString turnText = "0";
    QGraphicsTextItem* playerTurnText;
    QString playerTurn;
    QMediaPlayer * gameOverSound;
};


#endif // GAME_H
