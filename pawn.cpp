#include "pawn.h"
#include "game.h"
#include <QDebug>
#include <typeinfo>
#include "king.h"
#include "queen.h"
#include "chesspiece.h"
extern Game * game;
Pawn::Pawn(QString team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    firstMove = true;
    weight=10;
}

void Pawn::setImage()
{
    if(side == "WHITE")
        setPixmap(QPixmap(":/images/pawn1.png"));
    if(side =="BLACK")
        setPixmap(QPixmap(":/images/pawn.png"));
}

void Pawn::moves()
{

    location.clear();
    int row = this->getCurrentBox()->rowLocation;
    int col = this->getCurrentBox()->colLocation;

    /*if(this->getSide() == "BLACK"){

        ChessBox *b =game->collection[row+3][col];
        this->move(b);
    }*/
    if(this->getSide() == "WHITE") {
        if (this->promoted==0 || this->firstMove){
        if(col > 0 && row > 0 && game->collection[row-1][col-1]->getChessPieceColor() == "BLACK") {
            location.append(game->collection[row-1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && game->collection[row-1][col+1]->getChessPieceColor() == "BLACK") {
            location.append(game->collection[row-1][col+1]);
            boxSetting(location.last());
        }
        this->promoted=0;
        if(row>0 && (!game->collection[row-1][col]->getHasChessPiece())) {
            location.append(game->collection[row-1][col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[row-2][col]->getHasChessPiece()){
                location.append(game->collection[row-2][col]);
                boxSetting(location.last());
            }
        }}
        if (row==0 || this->promoted==1){
            //function that shows choice
            if (this->promoted==0) {
                this->promoted=1;
                game->promochoice(); 
            }
            if (this->promoted==1 && game->promopiece==0 && this->promotion==0){
                this->promoqueen=0;
                this->promotion=1;
                this->setPixmap(QPixmap(":/images/queen1.png"));


            }
            if(this->promoted==1 && game->promopiece==1 && this->promotion==0){
                this->promoqueen=1;
                this->promotion=1;
                this->setPixmap(QPixmap(":/images/horse1.png"));}



            if (this->promoqueen==0){
                this->setPixmap(QPixmap(":/images/queen1.png"));
            for(int i = row-1,j = col; i >= 0 ; i--) {
              if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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
               if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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
                if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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
                     if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
                         break;
                     }
                     else
                     {
                         location.append(game->collection[i][j]);
                         if(boxSetting(location.last()))
                             break;
                      }

              }

               //For upper Left

                for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
                  if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
                      break;

                  }
                  else
                  {
                      location.append(game->collection[i][j]);
                      if(boxSetting(location.last()) ){
                          break;
                      }
                  }
               }

                //For upper right

                 for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
                   if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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

                 //For downward right

                  for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
                    if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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

                  //For downward left

                   for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
                     if(game->collection[i][j]->getChessPieceColor() == "WHITE" ) {
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
                    }
            if (this->promoqueen==1){
                this->setPixmap(QPixmap(":/images/horse1.png"));
                int i ,j;
                QString team  = this->getSide();
                //There are total 8 places where a knight can move
                //1st up up left
                i = row - 2;
                j = col - 1;
                if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //2nd up up right
                i = row - 2;
                j = col + 1;
                if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //3rd down down left
                i = row + 2;
                j = col - 1;
                if(i <= 7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //4th  down down right
                i = row + 2;
                j = col + 1;
                if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //5th left left up
                i = row - 1;
                j = col - 2;
                if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //6th left left down
                i = row + 1;
                j = col - 2;
                if(i <=7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //7th right right up
                i = row - 1;
                j = col + 2;
                if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //8th right right down
                i = row + 1;
                j = col +  2;
                if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

        }}}
          //black moves
    else{
        promoted=0;
        if (this->promoted==0|| this->firstMove){
        if(col > 0 && row < 7 && game->collection[row+1][col-1]->getChessPieceColor() == "WHITE") {//left
            location.append(game->collection[row+1][col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row <  7 && game->collection[row+1][col+1]->getChessPieceColor() == "WHITE") {//right
            location.append(game->collection[row+1][col+1]);
            boxSetting(location.last());
        }

        if(row<7 && (!game->collection[row+1][col]->getHasChessPiece())) {
            location.append(game->collection[row+1][col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[row+2][col]->getHasChessPiece()){
                location.append(game->collection[row+2][col]);
                boxSetting(location.last());
            }

        }

        }
        if (row==7 || this->promoted==1){
            //function that shows choice
          if(!game->isAi){
            if (this->promoted==0) {
                this->promoted=1;
                game->promochoice();
            }
            if (this->promoted==1 && game->promopiece==0 && this->promotion==0){
                this->promoqueen=0;
                this->promotion=1;
                this->setPixmap(QPixmap(":/images/queen.png"));


            }
            if(this->promoted==1 && game->promopiece==1 && this->promotion==0){
                this->promoqueen=1;
                this->promotion=1;
                this->setPixmap(QPixmap(":/images/horse.png"));}
          }



            if (this->promoqueen==0){
                this->setPixmap(QPixmap(":/images/queen.png"));
            for(int i = row-1,j = col; i >= 0 ; i--) {
              if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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
               if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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
                if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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
                     if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
                         break;
                     }
                     else
                     {
                         location.append(game->collection[i][j]);
                         if(boxSetting(location.last()))
                             break;
                      }

              }

               //For upper Left

                for(int i = row-1,j = col-1; i >= 0 && j >=0; i--,j--) {
                  if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
                      break;

                  }
                  else
                  {
                      location.append(game->collection[i][j]);
                      if(boxSetting(location.last()) ){
                          break;
                      }
                  }
               }

                //For upper right

                 for(int i = row-1,j = col+1; i >= 0 && j <= 7; i--,j++) {
                   if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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

                 //For downward right

                  for(int i = row+1,j = col+1; i <= 7 && j <= 7; i++,j++) {
                    if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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

                  //For downward left

                   for(int i = row+1,j = col-1; i <= 7 && j >= 0; i++,j--) {
                     if(game->collection[i][j]->getChessPieceColor() == "BLACK" ) {
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
                    }
            if (this->promoqueen==1){
                this->setPixmap(QPixmap(":/images/horse.png"));
                int i ,j;
                QString team  = this->getSide();
                //There are total 8 places where a knight can move

                //1st up up left
                i = row - 2;
                j = col - 1;
                if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //2nd up up right
                i = row - 2;
                j = col + 1;
                if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //3rd down down left
                i = row + 2;
                j = col - 1;
                if(i <= 7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //4th  down down right
                i = row + 2;
                j = col + 1;
                if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //5th left left up
                i = row - 1;
                j = col - 2;
                if(i >=0 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //6th left left down
                i = row + 1;
                j = col - 2;
                if(i <=7 && j>=0 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //7th right right up
                i = row - 1;
                j = col + 2;
                if(i >=0 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

                //8th right right down
                i = row + 1;
                j = col +  2;
                if(i <=7 && j<=7 && (game->collection[i][j]->getChessPieceColor() != team) ) {
                    location.append(game->collection[i][j]);
                    if(location.last()->getHasChessPiece())
                        location.last()->setColor(redish);
                    else
                        location.last()->setColor(darker);
                }

        }}



    }

}




