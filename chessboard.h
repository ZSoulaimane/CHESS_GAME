#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.h"

class ChessBoard
{
public:
    ChessBoard();
   ~ChessBoard();

    //public functions
    void drawingBoxes(int x, int y,QColor,QColor);
    void setlistWhite();
    void setlistBlack();
    void addChessPiece();
    void reset();
private:
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;

};

#endif // CHESSBOARD_H
