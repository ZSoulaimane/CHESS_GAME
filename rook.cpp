#include "rook.h"
#include "game.h"

extern Game *game;
Rook::Rook(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    weight=50;
}


void Rook::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/rook1.png"));
    else
        setPixmap(QPixmap(":/images/rook.png"));
}

void Rook::moves()
{
    location.clear();
    int row = this->getCurrentBox()->rowLocation;
    int col = this->getCurrentBox()->colLocation;

    //START CASTLING
        //RESPONDING TO WHITE CASTLING LEFTSIDE
    if(row==7 && col==0 && game->castleftwhite==1 && game->collection[row][col+2]->getHasChessPiece()==1 && firstMove) {
        game->removeFromScene(this);
        game->collection[row][col]->setHasChessPiece(false);
        ChessBox *box =game->collection[row][col+3];
        box->placePiece(this);
        //game->alivePiece.append(this);
        game->addToScene(this);
    }
       //RESPONDING TO WHITE CASTLING RIGHTSIDE
    if(row==7 && col==7 && game->castrightwhite==1 && game->collection[row][col-1]->getHasChessPiece()==1 && firstMove) {
        game->removeFromScene(this);
        game->collection[row][col]->setHasChessPiece(false);
        ChessBox *box =game->collection[row][col-2];
        box->placePiece(this);
        //game->alivePiece.append(this);
        game->addToScene(this);
    }
    if(row==0 && col==0 && game->castleftblack==1 && game->collection[row][col+2]->getHasChessPiece()==1 && firstMove) {
        game->removeFromScene(this);
        game->collection[row][col]->setHasChessPiece(false);
        ChessBox *box =game->collection[row][col+3];
        box->placePiece(this);
        //game->alivePiece.append(this);
        game->addToScene(this);
    }
       //RESPONDING TO WHITE CASTLING RIGHTSIDE
    if(row==0 && col==7 && game->castrightblack==1 && game->collection[row][col-1]->getHasChessPiece()==1 && firstMove) {
        game->removeFromScene(this);
        game->collection[row][col]->setHasChessPiece(false);
        ChessBox *box =game->collection[row][col-2];
        box->placePiece(this);
        //game->alivePiece.append(this);
        game->addToScene(this);
    }

    //END CASTLING


    QString team = this->getSide();
    //For up

     for(int i = row-1,j = col; i >= 0 ; i--) {

       if(game->collection[i][j]->getChessPieceColor() == team ) {
           break;
       }
       else
       {
           location.append(game->collection[i][j]);
           if(boxSetting(location.last()))
               break;
        }
    }

     //For Down

      for(int i = row+1,j = col; i <= 7 ; i++) {
        if(game->collection[i][j]->getChessPieceColor() == team ) {
            break;
        }
        else
        {
            location.append(game->collection[i][j]);
            if(boxSetting(location.last())){
                break;
            }
        }
     }

      //For left

       for(int i = row,j = col-1; j >= 0 ; j--) {
         if(game->collection[i][j]->getChessPieceColor() == team ) {
             break;
         }
         else
         {
             location.append(game->collection[i][j]);
             if(boxSetting(location.last()))
                break;
         }
        }
       //For Right

        for(int i = row,j = col+1; j <= 7 ; j++)
        {
              if(game->collection[i][j]->getChessPieceColor() == team ) {
                  break;
              }
              else
              {
                  location.append(game->collection[i][j]);
                  if(boxSetting(location.last()))
                      break;
               }

       }


}


