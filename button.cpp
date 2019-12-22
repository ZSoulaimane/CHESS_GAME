#include "button.h"
#include <QGraphicsTextItem>
#include <QBrush>
#include <QPainter>
#include <QIcon>
#include "chesspiece.h"
#include "queen.h"


//the basic lightgray button
Button::Button(QString name,int x,int y, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //draw the rect
    QFontDatabase::addApplicationFont(":/fonts/Quantify.ttf");
    setRect(0,0,x,y);
    QBrush brush;
    brush.setStyle(Qt::NoBrush);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    setBrush(brush);

    //draw Text
    text = new QGraphicsTextItem(name,this);
    QFont titleFont("Segoe UI Semibold" ,12);
    text->setFont( titleFont);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
    text->setDefaultTextColor(lack);
    //Allow responding to hover
    setAcceptHoverEvents(true);

}

//button with no text
//this one is for promotion choices

Button::Button(int x,int y,QColor color, QGraphicsItem *parent)
    :QGraphicsRectItem(parent)
{
    //draw the rect
    setRect(0,0,x,y);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush);
    setAcceptHoverEvents(false);}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event)
    emit clicked();

}

void Button::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::darkGray);
    text->setDefaultTextColor(Qt::white);
    setBrush(brush);
    }
}
void Button::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    //change color
    if(event){
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::gray);
    text->setDefaultTextColor(lack);
    setBrush(brush);
    }
}
