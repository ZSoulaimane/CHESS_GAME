#include "game.h"
#include "button.h"
#include <QPixmap>
#include "king.h"
#include <QDebug>
#include <QFontDatabase>
#include <QGraphicsItem>
#include "pawn.h"

Game::Game(QWidget *parent ):QGraphicsView(parent)
  {
    QFontDatabase::addApplicationFont(":/fonts/BebasNeue-Regular.ttf");
    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,860,660);

    //Making the view
    setFixedSize(860,660);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    MovePiece = NULL;

    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(230,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("Bebas Neue",18));
    turnDisplay->setPlainText("Turn : WHITE");

    //display Check
    check = new QGraphicsTextItem();
    check->setPos(230,620);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::black);
    check->setFont(QFont("Bebas Neue",18));
    check->setPlainText("CHECK !");
    check->setVisible(false);
    setTurn("WHITE");
}

void Game::youwin(QString turn){
    pausebox(0,0,pausecol);
        addToScene(pause);
        listP.append(pause);
    QFontDatabase::addApplicationFont(":/fonts/BebasNeue-Regular.ttf");
    QGraphicsTextItem *win = new QGraphicsTextItem(turn + " WON");
    QFont titleFont("Bebas Neue" , 70);
    win->setFont( titleFont);
    int xPos = 560/2 - win->boundingRect().width()/2;
    int yPos = 150;
    win->setDefaultTextColor(Qt::white);
    win->setPos(xPos,yPos);
    win->setZValue(10);
    addToScene(win);
    listP.append(win);

    //restart button

    Button * restartbutton = new Button("Restart",200,50);
    int axPos = 560/2 - restartbutton->boundingRect().width()/2;
    int ayPos = 300;
    restartbutton->setPos(axPos,ayPos);
    restartbutton->setZValue(6);
    connect(restartbutton, SIGNAL(clicked()),this,SLOT(gameOver()));
    addToScene(restartbutton);
    listP.append(restartbutton);

    //Main menu
    Button * Mainmenu = new Button("Main menu",200,50);
    int jxPos = 560/2 - restartbutton->boundingRect().width()/2;
    int jyPos = 375;
    Mainmenu->setPos(jxPos,jyPos);
    Mainmenu->setZValue(6);
    connect(Mainmenu, SIGNAL(clicked()),this,SLOT(gameOver()));
    addToScene(Mainmenu);
    listP.append(Mainmenu);

    //Create Quit Button
    Button * quitButton = new Button("Quit",200,50);
    int qxPos = 560/2 - quitButton->boundingRect().width()/2;
    int qyPos = 450;
    quitButton->setPos(qxPos,qyPos);
    quitButton->setZValue(6);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    listP.append(quitButton);
    //wining sound
    QMediaPlayer *winmusic= new QMediaPlayer();
    winmusic->setMedia(QUrl("qrc:/sounds/win_music.mp3"));
    winmusic->play();

}

void Game::drawChessBoard(QColor a,QColor b)
{
    chess = new ChessBoard();
    drawDeadHolder(560,330,Qt::lightGray);
    drawDeadHolder(560,0,Qt::lightGray);
    deadpieceboxes(580,20,Qt::gray );
    deadpieceboxes(580,350,Qt::gray);
    chess->drawingBoxes(0,50,a,b);

}

void Game::displayDeadWhite()
{
    int SHIFT = 40;
    int j = 0;
    int k = 0;
    for(int i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 6){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(580+SHIFT*j++,380+SHIFT*1.5*k);
    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 40;
    int j = 0;
    int k = 0;
    for(int i = 0,n = blackDead.size(); i<n; i++) {
        if(j ==6){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(580+SHIFT*j++,50+SHIFT*1.5*k);
    }
}
void Game::promochoice(){

    QFontDatabase::addApplicationFont(":/fonts/BebasNeue-Regular.ttf");
    QGraphicsTextItem *ChoiceText = new QGraphicsTextItem("CHOOSE ONE");
    QFont titleFont("Bebas Neue" , 70);
    ChoiceText->setFont( titleFont);
    int xPos = 560/2 - ChoiceText->boundingRect().width()/2;
    int yPos = 150;
    ChoiceText->setDefaultTextColor(Qt::white);
    ChoiceText->setPos(xPos,yPos);
    ChoiceText->setZValue(10);
    addToScene(ChoiceText);
    listP.append(ChoiceText);
    pausebox(0,0,pausecol);
        addToScene(pause);
        listP.append(pause);

    //Queen BUTTON
    Button * QueenB = new Button(100,100,Qt::lightGray);
    int zxPos = 150;
    int zyPos = 270 ;
    QueenB->setPos(zxPos,zyPos);
    connect(QueenB,SIGNAL(clicked()) , this , SLOT(choseQueen()));
    QueenB->setZValue(10);
        addToScene(QueenB);
        listP.append(QueenB);
    QGraphicsPixmapItem *imag = new QGraphicsPixmapItem();
    imag->setPixmap(QPixmap(":/images/queen1.png"));
    int oxPos = 150 +50  - imag->boundingRect().width()/2;
    int oyPos = 270 +50 - imag->boundingRect().height()/2;
    imag->setZValue(3000);
    imag->setPos(oxPos,oyPos);
    addToScene(imag);
    listP.append(imag);

    //Knight Button
    Button * KnightB = new Button(100,100,Qt::lightGray);
    int mxPos = 310;
    int myPos = 270 ;
    KnightB->setPos(mxPos,myPos);
    connect(KnightB,SIGNAL(clicked()) , this , SLOT(choseKnight()));
    KnightB->setZValue(10);
    addToScene(KnightB);
    listP.append(KnightB);

    //horse Button
    QGraphicsPixmapItem *imag2 = new QGraphicsPixmapItem();
    imag2->setPixmap(QPixmap(":/images/horse1.png"));
    int wxPos = 310 +50 - imag2->boundingRect().width()/2;
    int wyPos = 270 +50 - imag2->boundingRect().height()/2;
    imag2->setZValue(3000);
    imag2->setPos(wxPos,wyPos);
    addToScene(imag2);
    listP.append(imag2);


}
void Game::placeInDeadPlace(ChessPiece *piece)
{
    int g;
    g=piece->number;
    if(piece->getSide() == "WHITE") {
        whiteDead.append(piece);
        //King *g = dynamic_cast <King *>(piece);

        if(g==1){
            if(this->isAi)youwin("Ai");
            else{
                youwin(getTurn());}
        }
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
        //King *g = dynamic_cast <King *>(piece);
        if(g==2){

            youwin(getTurn());
        }
        displayDeadBlack();
    }
    //remove this piece from alivepiece
    alivePiece.removeAll(piece);

    if(piece->getSide()=="BLACK"){
        aliveblackPiece.removeAll(piece);
    }
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}

QString Game::getTurn()
{
    return turn;
}

void Game::setTurn(QString value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(isAi==0){
    if(getTurn() == "WHITE")
        setTurn("BLACK");
    else
        setTurn("WHITE");
    turnDisplay->setPlainText("Turn : " + getTurn());}
    else {
        setTurn("WHITE");
    }
}

void Game::start()
{
    for(size_t i =0, n = listG.size(); i < n; i++)
        removeFromScene(listG[i]);
    //pausebutton
    addToScene(turnDisplay);
    Button * Pause = new Button("||",40,40);
    int dxPos = 815-Pause->boundingRect().width()/2;
    int dyPos = 25 ;
    Pause->setPos(dxPos,dyPos);
    if (this->pausecon==0){
    connect(Pause,SIGNAL(clicked()) , this , SLOT(displayPauseMenu()));}
    addToScene(Pause);

    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(710-45,350);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("Bebas Neue",18));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);
    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();

    blackPiece->setPos(710-45,20);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("Bebas Neue",18));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    chess->addChessPiece();

}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,330);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);

}
void Game::deadpieceboxes(int x, int y,QColor color)
{
    box = new QGraphicsRectItem(x,y,260,290);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    box->setBrush(brush);
    addToScene(box);
}
void Game::pausebox(int x, int y,QColor color)
{
    pause = new QGraphicsRectItem(x,y,2000,2000);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    pause->setBrush(brush);
    pause->setZValue(5);
}



void Game::displayMainMenu()
{
    //added in order to access the main menu from the game, quiting the actual gamemode whithout quiting the game.
    resume();
    if(this->pausecon) clearboard();

    //Create the title
    QFontDatabase::addApplicationFont(":/fonts/BebasNeue-Regular.ttf");
    QGraphicsTextItem *titleText = new QGraphicsTextItem("Chess");
        QFont titleFont("Bebas Neue" , 70);
        titleText->setFont( titleFont);
    int xPos = 560/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);

    //create Button 1VS 1 BUTTON
    Button * playButton = new Button("Player vs Player",200,50);
    int pxPos = 560/2 - playButton->boundingRect().width()/2;
    int pyPos = 300;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(start()));
    addToScene(playButton);
    listG.append(playButton);


    // pvscpu -------NOT READY--------
    Button * computer = new Button("Player vs CPU",200,50);
    int gxPos = 560/2 - computer->boundingRect().width()/2;
    int gyPos = 375;
    computer->setPos(gxPos,gyPos);
    connect(computer, SIGNAL(clicked()),this,SLOT(startAi()));
    addToScene(computer);
    listG.append(computer);


    //Create Quit Button
    Button * quitButton = new Button("Quit",200,50);
    int qxPos = 560/2 - quitButton->boundingRect().width()/2;
    int qyPos = 450;
    quitButton->setPos(qxPos,qyPos);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    listG.append(quitButton);

    //switch button
    Button * colorswitch = new Button(50,50,Qt::white);
    int dxPos = 390 ;
    int dyPos = 450 ;
    colorswitch->setPos(dxPos,dyPos);
    connect(colorswitch,SIGNAL(clicked()) , this , SLOT(switchcolor()));
    addToScene(colorswitch);
    listG.append(colorswitch);

    //reload icon
    QGraphicsPixmapItem *reloadicon = new QGraphicsPixmapItem();
    reloadicon->setPixmap(QPixmap(":/images/reload.png"));
    int uxPos = 390   +28 - reloadicon->boundingRect().width()/2;
    int uyPos = 450  +25 - reloadicon->boundingRect().height()/2;
    reloadicon->setZValue(3000);
    reloadicon->setPos(uxPos,uyPos);
    addToScene(reloadicon);
    listG.append(reloadicon);
    drawChessBoard(beige,maroon);

}

void Game::choseQueen(){
     this->promopiece=0;
     QList <ChessPiece *> zList = this->alivePiece;
     for(int i = 0,n=zList.size(); i < n; i++ ) {
         zList[i]->moves();
         zList[i]->decolor();
     }
    for(int i =0, n = listP.size(); i < n; i++)
        removeFromScene(listP[i]);
}
void Game::choseKnight(){
     this->promopiece=1;
    QList <ChessPiece *> zList = this->alivePiece;
    for(int i = 0,n=zList.size(); i < n; i++ ) {
        zList[i]->moves();
        zList[i]->decolor();
    }
    for(int i =0, n = listP.size(); i < n; i++)
       removeFromScene(listP[i]);
}
void Game::resume(){
this->MovePiece=NULL;
    for(int i =0, n = listP.size(); i < n; i++)
        removeFromScene(listP[i]);
}
void Game::displayPauseMenu(){
    this->pausecon=1;
    ChessPiece *l=new Pawn("WHITE");
    this->MovePiece=l;
    pausebox(0,0,pausecol);
        addToScene(pause);
        listP.append(pause);
    QFontDatabase::addApplicationFont(":/fonts/BebasNeue-Regular.ttf");
    QGraphicsTextItem * PauseText = new QGraphicsTextItem("PAUSED");
    QFont titleFont("Bebas Neue" , 70);
    PauseText->setFont( titleFont);
    int xPos =560/2 - PauseText->boundingRect().width()/2;
    int yPos =130;
    PauseText->setDefaultTextColor(Qt::white);
    PauseText->setPos(xPos,yPos);
    PauseText->setZValue(6);
    addToScene(PauseText);
    listP.append(PauseText);


    //RESUME button
    Button * ResumeButton = new Button("Resume",200,50);

    int pxPos = 560/2 - ResumeButton->boundingRect().width()/2;
    int pyPos = 260;
    ResumeButton->setPos(pxPos,pyPos);
    ResumeButton->setZValue(6);
    connect(ResumeButton,SIGNAL(clicked()) , this , SLOT(resume()));
    addToScene(ResumeButton);
    listP.append(ResumeButton);

    //restart button

    Button * restartbutton = new Button("Restart",200,50);
    int axPos = 560/2 - restartbutton->boundingRect().width()/2;
    int ayPos = 335;
    restartbutton->setPos(axPos,ayPos);
    restartbutton->setZValue(6);
    connect(restartbutton, SIGNAL(clicked()),this,SLOT(gameOver()));
    addToScene(restartbutton);
    listP.append(restartbutton);

    //Main menu
    Button * Mainmenu = new Button("Main menu",200,50);
    int jxPos = 560/2 - restartbutton->boundingRect().width()/2;
    int jyPos = 410;
    Mainmenu->setPos(jxPos,jyPos);
    Mainmenu->setZValue(6);
    connect(Mainmenu, SIGNAL(clicked()),this,SLOT(displayMainMenu()));
    addToScene(Mainmenu);
    listP.append(Mainmenu);



    //Quit Button
    Button * quitButton = new Button("Quit",200,50);
    int qxPos = 560/2 - quitButton->boundingRect().width()/2;
    int qyPos = 485;
    quitButton->setPos(qxPos,qyPos);
    quitButton->setZValue(6);
    connect(quitButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(quitButton);
    listP.append(quitButton);


}
//slot for switching colors
void Game::switchcolor(){
    if(color==0){
        for(int i =0, n = cololist.size(); i < n; i++)
            removeFromScene(cololist[i]);
        color=1;
        drawChessBoard(beige,Qt::darkCyan);
    }
    else if(color==1){
        for(int i =0, n = cololist.size(); i < n; i++)
            removeFromScene(cololist[i]);
        color=2;
        drawChessBoard(ligreen,greeen);
    }
    else if(color==2){
        for(int i =0, n = cololist.size(); i < n; i++)
            removeFromScene(cololist[i]);
        color=3;
        drawChessBoard(beige,ligreen);
    }
    else if(color==3){
        color=0;
        drawChessBoard(beige,maroon);
    }

}

void Game::startAi(){
  isAi=1;
  start();

}

//STARTAiend
// not functioning well
void Game::clearboard(){
    QList <ChessPiece *> jList = this->alivePiece;
    for(int i=0;i<jList.size();i++){
        jList[i]->decolor();
        jList[i]->getCurrentBox()->resetOriginalColor();
        this->removeFromScene(jList[i]);
}
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {
            this->collection[i][j]->setHasChessPiece(false);
        }
    }
    whiteDead.clear();
    blackDead.clear();
    removeFromScene(turnDisplay);
    alivePiece.clear();
    this->castleftblack=0;
    this->castleftwhite=0;
    this->castrightblack=0;
    this->castrightwhite=0;
    check->setVisible(false);

}
void Game::gameOver()
{   resume();
    QList <ChessPiece *> jList = this->alivePiece;
    for(int i=0;i<jList.size();i++){
        jList[i]->decolor();
        jList[i]->getCurrentBox()->resetOriginalColor();
}
    whiteDead.clear();
    blackDead.clear();
    alivePiece.clear();
    setTurn("WHITE");
    this->castleftblack=0;
    this->castleftwhite=0;
    this->castrightblack=0;
    this->castrightwhite=0;
    check->setVisible(false);
    chess->reset();
}

/*void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}*/

