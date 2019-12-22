#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include "chessbox.h"
#include <QGraphicsSceneMouseEvent>

class ChessBox;
//class Pawn;
class ChessPiece:public QGraphicsPixmapItem
{

public:
    QColor redish=QColor(217,100,90);
    QColor darker=QColor(140,70,70);
    QColor blueish=QColor(135,16,63);

    ChessPiece(QString team = "",QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(ChessBox *box);
    ChessBox *getCurrentBox() ;
    QString getSide() ;
    void setSide( QString value);
    virtual void setImage() = 0;
    bool getIsPlaced() ;
    void setIsPlaced(bool value);
    QList <ChessBox *> moveLocation();
    virtual void moves() = 0;
    void decolor();
//move
   void move(ChessBox *box);
//moveend
    bool boxSetting(ChessBox *box);
    bool firstMove;
    int number=0;
    int weight;
    ChessBox *currentBox;
protected:

    QString side;
    bool isPlaced;
    QList <ChessBox *> location;

};

#endif // CHESSPIECE_H
