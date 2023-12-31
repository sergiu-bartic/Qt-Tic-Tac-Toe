#include "Game.h"
#include "MainMenu.h"
#include <QApplication>
#include <QPushButton>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QBrush>
#include <QMediaPlayer>
#include <QImage>

Game::Game(QWidget*parent)
{
    // set up the screen
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1024,768);

    // set up the scene
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1024,768);
    setScene(scene);

    setBackgroundBrush(QBrush(QImage(":/Images/BG.png")));

    // play background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/Sounds/BG.mp3"));
    music->play();
}

void Game::displayMainMenu()
{
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(QString("Tic Tac Toe"));
    QFont titleFont("comic sans",50);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::yellow);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 150;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    MainMenu* playButton = new MainMenu(QString("Play"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 300;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    MainMenu* quitButton = new MainMenu(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 400;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);
}

void Game::start()
{
    // clear the screen
    scene->clear();

    drawGUI();
}

void Game::drawGUI()
{
    // place player X text
    QGraphicsTextItem* p1 = new QGraphicsTextItem("Player X");
    QFont p1Font("comic sans",20,QFont::Bold);
    p1->setFont(p1Font);
    p1->setDefaultTextColor(Qt::darkGreen);
    p1->setPos(200,200);
    scene->addItem(p1);

    // place player 0 text
    QGraphicsTextItem* p2 = new QGraphicsTextItem("Player 0");
    QFont p2Font("comic sans",20,QFont::Bold);
    p2->setFont(p1Font);
    p2->setDefaultTextColor(Qt::red);
    p2->setPos(725,200);
    scene->addItem(p2);

    // place vsText
    QGraphicsTextItem* vsText = new QGraphicsTextItem("vs");
    QFont vsTextFont("comic sans",18);
    int vsxPos = this->width()/2 - vsText->boundingRect().width()/2;
    vsText->setFont(vsTextFont);
    vsText->setDefaultTextColor(Qt::yellow);
    vsText->setPos(vsxPos,200);
    scene->addItem(vsText);

    // place playerTurnText
    playerTurnText = new QGraphicsTextItem();
    setPlayerTurn(QString("X"));
    QFont playerTurnTextFont("comic sans",20);
    playerTurnText->setFont(playerTurnTextFont);
    playerTurnText->setDefaultTextColor(Qt::yellow);
    int pTTxPos = this->width()/2 - playerTurnText->boundingRect().width()/2;
    playerTurnText->setPos(pTTxPos,100);
    scene->addItem(playerTurnText);

    int startx = width()/2 - 100 - 5 - 50;
    int starty = 325;
    int valueWidth = (width() - startx - 200 - 2 * 5) / 3;
    int valueHeight = (height() - starty  -170 - 2 * 5) / 3;

    for (int i = 0; i < 9; ++i)
    {
        buttons[i] = new QPushButton("");
        buttons[i]->setGeometry(startx+i%3*(5+100), starty+i/3*(5+100), 100, 100);
        buttons[i]->setFont(QFont("Comic",25,QFont::Bold));
        buttons[i]->setStyleSheet("background-color: lightGray; color: blue;");
        scene->addWidget(buttons[i]);
        connect(buttons[i], SIGNAL(clicked()), this, SLOT(buttonClicked()));
    }

    restartButton = new QPushButton("Restart");
    scene->addWidget(restartButton);
    restartButton->setGeometry(10,10,100,30);
    restartButton->setFont(QFont("Comic",12,QFont::Bold));
    restartButton->setStyleSheet("background-color: lightGray; color: blue;");
    QObject::connect(restartButton,SIGNAL(clicked()),this,SLOT(restartGame()));

    QPushButton* about = new QPushButton("About Qt");
    scene->addWidget(about);
    about->setGeometry(115,10,100,30);
    about->setFont(QFont("Comic",12,QFont::Bold));
    about->setStyleSheet("background-color: lightGray; color: blue;");
    QObject::connect(about,SIGNAL(clicked()),qApp,SLOT(aboutQt()));

    QPushButton* quit = new QPushButton("Quit");
    scene->addWidget(quit);
    quit->setGeometry(220,10,100,30);
    quit->setFont(QFont("Comic",12,QFont::Bold));
    quit->setStyleSheet("background-color: lightGray; color: blue;");
    QObject::connect(quit,SIGNAL(clicked()),qApp,SLOT(quit()));
}

void Game::buttonClicked()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (turnText == "X" && button->text() == ""){
        button->setText("0");
        button->setStyleSheet("color: red;");
        turnText = "0";
        nr++;
    }
    else if (turnText == "0" && button->text() == ""){
        button->setText("X");
        button->setStyleSheet("color: green;");
        turnText = "X";
        nr++;
    }

    // make it the next players turn
    nextPlayerTurn();
    checkWinner();
}

void Game::restartGame()
{
    turnText = "0";

    for (int i = 0; i < 9; ++i)
    {
        buttons[i]->setText("");
        buttons[i]->setStyleSheet("background-color: lightGray;");
    }
    nr = 0;
}

void Game::checkWinner()
{
    if (buttons[0]->text() == buttons[1]->text() && buttons[1]->text() == buttons[2]->text() && buttons[0]->text() != "")
    {
        buttons[0]->setStyleSheet("background-color: green;");
        buttons[1]->setStyleSheet("background-color: green;");
        buttons[2]->setStyleSheet("background-color: green;");
        gameOver();
    }
    else if (buttons[3]->text() == buttons[4]->text() && buttons[4]->text() == buttons[5]->text() && buttons[3]->text() != "")
    {
        buttons[3]->setStyleSheet("background-color: green;");
        buttons[4]->setStyleSheet("background-color: green;");
        buttons[5]->setStyleSheet("background-color: green;");
        gameOver();
    }
    else if (buttons[6]->text() == buttons[7]->text() && buttons[7]->text() == buttons[8]->text() && buttons[6]->text() != "")
    {
        buttons[6]->setStyleSheet("background-color: green;");
        buttons[7]->setStyleSheet("background-color: green;");
        buttons[8]->setStyleSheet("background-color: green;");
        gameOver();
    }
    else if (buttons[0]->text() == buttons[3]->text() && buttons[3]->text() == buttons[6]->text() && buttons[0]->text() != "")
    {
        buttons[0]->setStyleSheet("background-color: red;");
        buttons[3]->setStyleSheet("background-color: red;");
        buttons[6]->setStyleSheet("background-color: red;");
        gameOver();
    }
    else if (buttons[1]->text() == buttons[4]->text() && buttons[4]->text() == buttons[7]->text() && buttons[1]->text() != "")
    {
        buttons[1]->setStyleSheet("background-color: red;");
        buttons[4]->setStyleSheet("background-color: red;");
        buttons[7]->setStyleSheet("background-color: red;");
        gameOver();
    }
    else if (buttons[2]->text() == buttons[5]->text() && buttons[5]->text() == buttons[8]->text() && buttons[2]->text() != "")
    {
        buttons[2]->setStyleSheet("background-color: red;");
        buttons[5]->setStyleSheet("background-color: red;");
        buttons[8]->setStyleSheet("background-color: red;");
        gameOver();
    }
    else if (buttons[0]->text() == buttons[4]->text() && buttons[4]->text() == buttons[8]->text() && buttons[0]->text() != "")
    {
        buttons[0]->setStyleSheet("background-color: blue;");
        buttons[4]->setStyleSheet("background-color: blue;");
        buttons[8]->setStyleSheet("background-color: blue;");
        gameOver();
    }
    else if (buttons[2]->text() == buttons[4]->text() && buttons[4]->text() == buttons[6]->text() && buttons[2]->text() != "")
    {
        buttons[2]->setStyleSheet("background-color: yellow;");
        buttons[4]->setStyleSheet("background-color: yellow;");
        buttons[6]->setStyleSheet("background-color: yellow;");
        gameOver();
    }
    else if(nr==9)
        gameOver();
}

void Game::gameOver(){

    QString messege;

    if(nr==9)
        messege = QString("Draw Game!!!");
    else
        messege = QString("Player ") + turnText + QString(" Win!!!");

    displayGameOver(messege);

    }

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity){
    // draws a panel at the specified location with the specified properties
    QGraphicsRectItem* panel = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    panel->setBrush(brush);
    panel->setOpacity(opacity);
    scene->addItem(panel);
}

void Game::displayGameOver(QString textToDisplay)
{
    // disable all scene items
    for (size_t i = 0, n = scene->items().size(); i < n; i++){
        scene->items()[i]->setEnabled(false);
    }

    // pop up semi transparent panel
    drawPanel(0,0,1024,768,Qt::black,0.75);

    // draw panel
    drawPanel(312,184,400,400,Qt::lightGray,0.85);
    // create the title text
    QGraphicsTextItem* titleText = new QGraphicsTextItem(textToDisplay);
    QFont titleFont("comic sans",30,QFont::Bold);
    titleText->setFont(titleFont);
    titleText->setDefaultTextColor(Qt::yellow);
    int txPos = this->width()/2 - titleText->boundingRect().width()/2;
    int tyPos = 225;
    titleText->setPos(txPos,tyPos);
    scene->addItem(titleText);

    // create the play button
    MainMenu* playButton = new MainMenu(QString("Play again"));
    int bxPos = this->width()/2 - playButton->boundingRect().width()/2;
    int byPos = 300;
    playButton->setPos(bxPos,byPos);
    connect(playButton,SIGNAL(clicked()),this,SLOT(start()));
    scene->addItem(playButton);

    // create the quit button
    MainMenu* quitButton = new MainMenu(QString("Quit"));
    int qxPos = this->width()/2 - quitButton->boundingRect().width()/2;
    int qyPos = 400;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton,SIGNAL(clicked()),this,SLOT(close()));
    scene->addItem(quitButton);

    turnText = "0";
    nr = 0;

    // set Game Over sound
    gameOverSound = new QMediaPlayer();
    gameOverSound->setMedia(QUrl("qrc:/Sounds/Shoot.mp3"));
    gameOverSound->play();
}

QString Game::getPlayerTurn(){
    return playerTurn;
}

void Game::setPlayerTurn(QString turnText){
    // change the QString
    playerTurn = turnText;

    // change the QGraphicsTextItem
    playerTurnText->setPlainText(QString("Turn: Player ") + turnText);
}

void Game::nextPlayerTurn(){
    if (getPlayerTurn() == QString("X")){
        setPlayerTurn(QString("0"));
    }
    else {
        setPlayerTurn(QString("X"));
    }
}
