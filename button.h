#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include "queen.h"
#include "chesspiece.h"
#include <QFontDatabase>


class Button:public QObject, public QGraphicsRectItem
{
     Q_OBJECT
public:
    //colors
    QColor hovcol=QColor(1,  1, 1,80);
    QColor beige=QColor(245,  226, 204);
    QColor maroon=QColor(187,  127, 73);
    QColor lack=QColor(10,10,10);


    Button(QString name,int,int,QGraphicsItem * parent = NULL);
    Button(int,int,QColor,QGraphicsItem * parent = NULL);

    //events
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:
    void clicked();

private:
    QGraphicsTextItem *text;
    QGraphicsItem *imag;
};
#endif // BUTTON_H
