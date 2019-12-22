#ifndef PAWN_H
#define PAWN_H
#include "chesspiece.h"

class Pawn:public ChessPiece
{
public:
    Pawn(QString team,QGraphicsItem *parent = 0);
    void setImage();
    void moves();
 private:
    bool promoted=0; //differentiates between normal pawns and promoted ones promoted are set to 1, and none promoted to 0
    int promoqueen=0;//differentiates between choosing queen and knight
    bool promotion=0;//differentiates between promoted pawns and the ones currently in the process of promotion

};

#endif // PAWN_H
