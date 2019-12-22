#include "king.h"
#include "game.h"
#include "QtDebug"
#include "pawn.h"
extern Game *game;
King::King(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    weight=900;
    if(team=="WHITE"){number=1;}
    else number=2;

}

void King::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/king1.png"));
    else
        setPixmap(QPixmap(":/images/king.png"));
}


void King::moves()
{

    location.clear();
    int row = this->getCurrentBox()->rowLocation;
    int col = this->getCurrentBox()->colLocation;
    QString team = this->getSide();

        if(col > 0 && row > 0 && !(game->collection[row-1][col-1]->getChessPieceColor() == team)) {//up left
            location.append(game->collection[row-1][col-1]);
            game->collection[row-1][col-1]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }
        if(col < 7 && row > 0 && !(game->collection[row-1][col+1]->getChessPieceColor() == team)) { // up right
            location.append(game->collection[row-1][col+1]);
            game->collection[row-1][col+1]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }

        if(row> 0 && !(game->collection[row-1][col]->getChessPieceColor() == team)) {//up
            location.append(game->collection[row-1][col]);
            game->collection[row-1][col]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);

            }}

        if(row< 7 && !(game->collection[row+1][col]->getChessPieceColor() == team)) {//down
            location.append(game->collection[row+1][col]);
            game->collection[row+1][col]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }
        if(col>0 && !(game->collection[row][col-1]->getChessPieceColor() == team)) {// left
            location.append(game->collection[row][col-1]);
            game->collection[row][col-1]->setColor(darker);
            qDebug()<< "it seems th condition is working";
             //setup for THE CASTLING , initial thoughts are using signals, or modifying mousepressevent on the box class
            if ((row==7 || row==0) && game->collection[row][col-1]->getHasChessPiece()==0 && game->collection[row][col-2]->getHasChessPiece()==0 && game->collection[row][col-3]->getHasChessPiece()==0 && firstMove && this->isafe==1 && game->collection[row][col-4]->getHasChessPiece()==1 && game->collection[row][col-4]->currentPiece->firstMove==1){
                location.append(game->collection[row][col-2]);
                game->collection[row][col-2]->setColor(Qt::yellow);
                if(team=="WHITE") game->castleftwhite=1;
                else {
                    game->castleftblack=1;
                }
            }
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }
        if(col<7 && !(game->collection[row][col+1]->getChessPieceColor() == team)) {//right
            location.append(game->collection[row][col+1]);
            game->collection[row][col+1]->setColor(darker);
             //setup for THE CASTLING , initial thoughts are using signals, or modifying mousepressevent on the box class
            if ((row==7 || row==0) && game->collection[row][col+2]->getHasChessPiece()==0 && game->collection[row][col+1]->getHasChessPiece()==0 && firstMove && this->isafe==1 && game->collection[row][col+3]->getHasChessPiece()==1 && game->collection[row][col+3]->currentPiece->firstMove==1){
                location.append(game->collection[row][col+2]);
                game->collection[row][col+2]->setColor(Qt::yellow);
                if(team=="WHITE") game->castrightwhite=1;
                else{
                    game->castrightblack=1;}
            }
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }
        if(col >0 && row <7  && !(game->collection[row+1][col-1]->getChessPieceColor() == team)) {//down left
            location.append(game->collection[row+1][col-1]);
            game->collection[row+1][col-1]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }
        if(col < 7 && row < 7 && !(game->collection[row+1][col+1]->getChessPieceColor() == team)) {//down right
            location.append(game->collection[row+1][col+1]);
            game->collection[row+1][col+1]->setColor(darker);
            if(location.last()->getHasChessPiece()){
                location.last()->setColor(redish);
            }
        }


            findUnSafeLocation();


}

void King::findUnSafeLocation() {
    QList <ChessPiece *> pList = game->alivePiece;
    for(int i = 0,n = pList.size(); i < n; i++) {

        if(pList[i]->getSide() != this->getSide())
        {
            QList <ChessBox *> bList = pList[i]->moveLocation();

            for(int j = 0, n = bList.size(); j < n; j++) {
               /* Pawn *c = dynamic_cast<Pawn *> (pList[i]) ;
                if(c) continue;*/

                if(pList[i]->getCurrentBox()->currentPiece->weight==10)continue;
                for(int k = 0, n = location.size(); k < n; k++) {
                   if(bList[j] == location [k]) {
                       location[k]->setColor(blueish);
                       location[k]->safeaiking=0;
                   }
                }
            }
        }
    }
}
