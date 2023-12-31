#include "MainMenu.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QFont>

MainMenu::MainMenu(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent)
{
    // draw the rect
    setRect(0,0,200,50);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkYellow);
    setBrush(brush);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    QFont textFont("comic sans",20);
    text->setFont(textFont);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);

    // allow responding to hover events
    setAcceptHoverEvents(true);
}

void MainMenu::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit clicked();
}

void MainMenu::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    // change color to yellow
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::yellow);
    setBrush(brush);
}

void MainMenu::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    // change color to dark yellow
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkYellow);
    setBrush(brush);
}
