#include "chesspiece.h"
#include "game.h"
#include <QDebug>
#include "king.h"

extern Game *game;
ChessPiece::ChessPiece(QString team,QGraphicsItem *parent):QGraphicsPixmapItem(parent)
{

    side = team;
    isPlaced = true;
    firstMove = true;

}

void ChessPiece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == game->MovePiece){
        game->MovePiece->getCurrentBox()->resetOriginalColor();
        game->MovePiece->decolor();
        game->MovePiece = NULL;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced())|| ((game->getTurn() != this->getSide())&& (!game->MovePiece)) )
        return;
    //selecting
    if(!game->MovePiece){

        game->MovePiece = this;
        game->MovePiece->getCurrentBox()->setColor(redish);
        game->MovePiece->moves();
    }
    //Consuming counterPart of the CHessBox
    else if(this->getSide() != game->MovePiece->getSide()){
        this->getCurrentBox()->mousePressEvent(event);
    }


}

void ChessPiece::setCurrentBox(ChessBox *box)
{

    currentBox = box;
}

ChessBox *ChessPiece::getCurrentBox()
{
    return currentBox;
}

QString ChessPiece::getSide()
{
    return side;
}

void ChessPiece::setSide( QString value)
{
    side = value;
}

bool ChessPiece::getIsPlaced()
{
    return isPlaced;
}

void ChessPiece::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<ChessBox *> ChessPiece::moveLocation()
{
    return location;
}
void ChessPiece::decolor()
{
    for(int i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}
//movestart

void ChessPiece::move(ChessBox *box){
    if (this->firstMove)firstMove=0;
    int ligne=box->rowLocation;
    int colon=box->colLocation;
    int row=this->getCurrentBox()->rowLocation;
    int col=this->getCurrentBox()->colLocation;
    game->removeFromScene(this);
    this->getCurrentBox()->currentPiece = NULL;
    game->collection[row][col]->setHasChessPiece(false);
    ChessBox *b =game->collection[ligne][colon];
    b->placePiece(this);
    game->addToScene(this);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            game->collection[i][j]->safeaiking=1;
        }
    }




}

//moveend

bool ChessPiece::boxSetting(ChessBox *box)
{
    if(box->getHasChessPiece()) {
       //King *q = dynamic_cast<King*>(location.last()->currentPiece);
        //q number equal 0 if the piece is not a king otherwise it's 1
        int q;
      q=box->getpiecenumber();


        if(q){
            box->setColor(blueish);
        }
        else
            box->setColor(redish);
        return true;
    }
    else
        location.last()->setColor(Qt::darkRed);
    return false;
}
