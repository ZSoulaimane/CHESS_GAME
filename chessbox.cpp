#include "chessbox.h"
#include "game.h"
#include <QDebug>
#include "king.h"
#include<QMediaPlayer>

extern Game *game;
//class Pawn;
ChessBox::ChessBox(QGraphicsItem *parent):QGraphicsRectItem(parent)
{
    //making the Square CHess Box
   setRect(0,0,70,70);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasChessPiece(false);
    setChessPieceColor("NONE");
    currentPiece = NULL;
    //sound
    piecesound=new QMediaPlayer();
    piecesound->setMedia(QUrl("qrc:/sounds/piece_sound.mp3"));
}

ChessBox::~ChessBox()
{
    delete this;
}

void ChessBox::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      qDebug() << getChessPieceColor();
        //Deselecting counter part of ChessPiece
        if(currentPiece == game->MovePiece && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(game->MovePiece){
            //if same team
            if(this->getChessPieceColor() == game->MovePiece->getSide())
                return;
            //removing the eaten piece
            QList <ChessBox *> movLoc = game->MovePiece->moveLocation();
            //TO make sure the selected box is in move zone
            int check = 0;
            for(size_t i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;
                }
                //sound
                if(piecesound->state()==QMediaPlayer::PlayingState){
                    piecesound->setPosition(0);}
                else if(piecesound->state()==QMediaPlayer::StoppedState){
                    piecesound->play();
                }
            }
            // if not present return
            if(check == 0)
                return;
            //change the color back to normal
             game->MovePiece->decolor();
             //make the first move false applicable for pawn only
             game->MovePiece->firstMove = false;
             //this is to eat or consume the enemy present in the movable region
            if(this->getHasChessPiece()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBox(NULL);
                game->placeInDeadPlace(this->currentPiece);

            }
            //changing the new stat and resetting the previous left region
            game->MovePiece->getCurrentBox()->setHasChessPiece(false);
            game->MovePiece->getCurrentBox()->currentPiece = NULL;
            game->MovePiece->getCurrentBox()->resetOriginalColor();
            placePiece(game->MovePiece);

            game->MovePiece = NULL;
            //changing turn
            game->changeTurn();
            checkForCheck();
            if(game->isAi==1){
                aimove();
            }
}
        //Selecting couterpart of the chessPiece
        else if(this->getHasChessPiece())
        {
            this->currentPiece->mousePressEvent(event);
        }



}

void ChessBox::setColor(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}

void ChessBox::placePiece(ChessPiece *piece)
{
    piece->setPos(x()+35- piece->pixmap().width()/2  ,y()+35-piece->pixmap().width()/2);
    piece->setCurrentBox(this);
    setHasChessPiece(true,piece);
    currentPiece = piece;


}
//start Ai
void ChessBox::aimove(){
    int r=0;
    QList <ChessPiece *> aiList = game->aliveblackPiece;
    ChessPiece *piec;
    ChessBox *boxdest;
    //first checking if the AI king is checked, if so move the king to a safe place
    for (int i=0;i<aiList.size();i++) {
        King * p = dynamic_cast<King *> (aiList[i]);
             if(p){
                 p->moves();
                 p->decolor();
             if(p->isafe==0){
                 for (int j=0;j<p->moveLocation().size();j++) {
                     if(p->moveLocation()[j]->safeaiking==1){
                         r=1;
                         this->resetOriginalColor();
                         if(p->moveLocation()[j]->getChessPieceColor()=="WHITE"){
                             p->moveLocation()[j]->currentPiece->setIsPlaced(false);
                             p->moveLocation()[j]->currentPiece->setCurrentBox(NULL);
                             game->placeInDeadPlace(p->moveLocation()[j]->currentPiece);
                         }
                         p->move(p->moveLocation()[j]);
                         p->isafe=1;

                         for (int z=0;z<aiList.size();z++) {
                         aiList[z]->decolor();}
                         if(game->check->isVisible())
                             game->check->setVisible(false);
                         break;
                     }

                 }
             }
        }

    }
    //trying to find a move that results into a consuming situation before moving a random piece
    if(r==0){
        QList <ChessBox *> boxesList;//has the box destination
        QList <ChessPiece *> piecesList;//the piece that will move
        QList <int > mal; //has the piece weight

    for (int i=0;i<aiList.size();i++) {
        int max=0;
        ChessBox *chosenbox=NULL;
        for (int j=0;j<aiList[i]->moveLocation().size();j++) {
            piec=aiList[i];

            if(piec->moveLocation()[j]->getChessPieceColor()=="WHITE"){
                r=1;
                if(piec->moveLocation()[j]->currentPiece->weight>max){
                    max=piec->moveLocation()[j]->currentPiece->weight;
                    chosenbox=piec->moveLocation()[j];
                }
            }
        }
        if (chosenbox!=NULL){
                boxesList.append(chosenbox);
                mal.append(chosenbox->currentPiece->weight);
                piecesList.append(piec);
        }
    }
    if(mal.size()>0){
    int maxweight=0;
    int indice;
    for (int k=0;k<mal.size();k++) {
        if (mal[k]>maxweight) {
            maxweight=mal[k];
            indice =k;
        }

    }
        boxesList[indice]->currentPiece->setIsPlaced(false);
        boxesList[indice]->currentPiece->setCurrentBox(NULL);
        game->placeInDeadPlace(boxesList[indice]->currentPiece);
        piecesList[indice]->move(boxesList[indice]);
}
    }
    //randomization
    srand(time(0));
    if(r==0){
    do { piec=aiList[rand()%(aiList.size())];
         bxlist = piec->moveLocation();
    }
    while(bxlist.size()==0 || bxlist[rand()%(bxlist.size())]->getChessPieceColor()=="BLACK");
         boxdest=bxlist[rand()%(bxlist.size())];


         //if with the random function of the ai lands on a white pawn
    if(boxdest->getChessPieceColor()=="WHITE"){
        boxdest->currentPiece->setIsPlaced(false);
        boxdest->currentPiece->setCurrentBox(NULL);
        game->placeInDeadPlace(boxdest->currentPiece);
    }
         piec->move(boxdest); }
}
//end AI

void ChessBox::resetOriginalColor()
{
    setColor(originalColor);
}

void ChessBox::setOriginalColor(QColor value)
{
    originalColor = value;
    setColor(originalColor);
}
//getter chiesspiece number
int ChessBox::getpiecenumber(){return currentPiece->number;}
//used in boxsetting in chesspiece

bool ChessBox::getHasChessPiece()
{
    return hasChessPiece;
}

void ChessBox::setHasChessPiece(bool value, ChessPiece *piece)
{
    hasChessPiece = value;
    if(value)
        setChessPieceColor(piece->getSide());
    else
        setChessPieceColor("NONE");
}

void ChessBox::checkForCheck()
{   int c = 0;
    QList <ChessPiece *> pList = game->alivePiece;
    for(int i = 0,n=pList.size(); i < n; i++ ) {

      /*  King * p = dynamic_cast<King *> (pList[i]);
        if(p){
            continue;
        }*/
       /* if(pList[i]->getCurrentBox()->getpiecenumber())
        {continue;}*/


        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0,n = bList.size(); j < n; j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentPiece);

           // if(bList[j]->getHasChessPiece()){
            if(bList[j]->getHasChessPiece() && bList[j]->getpiecenumber()) {
                if(bList[j]->getChessPieceColor() == pList[i]->getSide()){
                    break;}
                bList[j]->setColor(blueish);
                p->isafe=0;
                pList[i]->getCurrentBox()->setColor(darker);
                if(!game->check->isVisible())
                    game->check->setVisible(true);
                else{
                    bList[j]->resetOriginalColor();
                    pList[i]->getCurrentBox()->resetOriginalColor();
                    game->youwin(game->getTurn());
                }
                c++;
            }
        }
    bList.clear();
    }
    if(!c){
        game->check->setVisible(false);
        for(int i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }
    /*int c = 0;
    QList <ChessPiece *> pList = game->alivePiece;
    for(int i = 0,n=pList.size(); i < n; i++ ) {

        King * p = dynamic_cast<King *> (pList[i]);
        if(p){
            continue;
        }
        pList[i]->moves();
        pList[i]->decolor();
        QList <ChessBox *> bList = pList[i]->moveLocation();
        for(int j = 0,n = bList.size(); j < n; j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentPiece);
            if(p) {
                if(p->getSide() == pList[i]->getSide()){
                    p->isafe=1;
                    continue;}
                if(!game->isAi){
                bList[j]->setColor(blueish);
                pList[i]->getCurrentBox()->setColor(darker);}
                p->isafe=0;

                if(!game->check->isVisible())
                    game->check->setVisible(true);
                else{
                    bList[j]->resetOriginalColor();
                    pList[i]->getCurrentBox()->resetOriginalColor();
                    game->youwin(game->getTurn());
                }
                c++;

            }
        }


    }
    if(!c){
        game->check->setVisible(false);
        for(int i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBox()->resetOriginalColor();
    }*/
}

QString ChessBox::getChessPieceColor()
{
    return chessPieceColor;
}

void ChessBox::setChessPieceColor(QString value)
{
    chessPieceColor = value;
}
