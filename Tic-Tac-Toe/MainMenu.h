#ifndef MAINMENU_H
#define MAINMENU_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class MainMenu:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    // constructors
    MainMenu(QString name, QGraphicsItem* parent=NULL);

    // public methods (events)
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();
private:
    QGraphicsTextItem* text;
};

#endif // MAINMENU_H
