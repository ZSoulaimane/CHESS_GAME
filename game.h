#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include "chessboard.h"
#include "chesspiece.h"
#include <QGraphicsRectItem>
#include<QMediaPlayer>

class Game:public QGraphicsView
{
    Q_OBJECT
    QColor beige=QColor(245,  226, 204);
    QColor maroon=QColor(187,  127, 73);
    QColor ligreen=QColor(198 , 195, 109);
    QColor lack=QColor(10,10,10);
    QColor greeen=QColor(122,157,115);
    QColor pausecol=QColor(1,  1, 1,100);

public:

    //Constructor
    Game(QWidget *parent = 0);
    //public Methods
    void deadpieceboxes(int x, int y, QColor color);
    void drawDeadHolder(int x, int y, QColor color);
    void pausebox(int x, int y, QColor color);
    void drawChessBoard(QColor a,QColor b);
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);
    void promochoice();
    void changeTurn();
    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);


    //getters/setters
    QString getTurn() ;
    void setTurn( QString value);


    //CASTLING
    bool castleftwhite=0;
    bool castrightwhite=0;
    bool castleftblack=0;
    bool castrightblack=0;
    //enCastling

    bool isAi=0;
    int color=0;

    ChessPiece *MovePiece;

    int promopiece=545;// is 0 if you chose a Queen
                    // set to 1 if you chose a Knight


    ChessBox *collection[8][8];
    QGraphicsTextItem *check;
    QList <ChessPiece *> alivePiece;
    QList <ChessPiece *> aliveblackPiece;
    QList <ChessPiece *> jList ;
    QList <ChessBox *> cololist; //list to store all chessboard and deadholders
    void clearboard();
    void removeAll();
public slots:
    void switchcolor();
    void displayMainMenu();
    void youwin(QString turn);
    void gameOver();
    void displayPauseMenu();
    void start();
    void resume();
    void choseQueen();
    void choseKnight();
    void startAi();

private:
    bool pausecon=0;
    QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    QGraphicsRectItem *box;
    QGraphicsRectItem * pause;

    QString turn;
    ChessBoard *chess;
    //Qlists that have scene items
    QList <QGraphicsItem *> listG;
    QList <QGraphicsItem *> listP;
    QGraphicsTextItem * turnDisplay;



};

#endif // GAME_H
