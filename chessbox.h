#ifndef CHESSBOX_H
#define CHESSBOX_H

#include <QGraphicsRectItem>
#include <QBrush>
#include "chesspiece.h"
#include <QGraphicsSceneMouseEvent>
#include <stdlib.h>
#include "time.h"
#include<QMediaPlayer>



class ChessPiece;
class ChessBox:public QGraphicsRectItem
{
public:
    QColor redish=QColor(217,100,90);
    QColor darker=QColor(140,70,70);
    QColor blueish=QColor(135,16,63);

    //Constructor
    ChessBox(QGraphicsItem *parent=0);
    ~ChessBox();


    //public member function
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(ChessPiece *piece);

    //getter piece number
    int getpiecenumber();

    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = 0);
    void aimove();
    void checkForCheck();

    QString getChessPieceColor() ;
    void setChessPieceColor(QString value);

    int rowLocation;
    int colLocation;

    ChessPiece * currentPiece;
    QList <ChessBox *> bxlist;
    bool safeaiking=1;

private:
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    QString chessPieceColor;
    QMediaPlayer *piecesound ;


};

#endif // CHESSBOX_H
