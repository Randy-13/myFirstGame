#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QChar>
#include <QColor>
#include <QString>
#include <QPair>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QEvent>
#include <QMap>
#include <QtMath>
#include <QTime>
#include <QListWidget>
#include <QMouseEvent>
#include <QMainWindow>
#include "map.h"
#include "fence.h"
#include "enemy.h"
#include "enemybase.h"
#include "soldiers.h"
#include "mybase.h"
#include "base.h"
#include "towerbase.h"
#include "tower.h"
#include "firstkindtower.h"
#include "secondkindtower.h"
#include "thirdkindtower.h"
#include "select.h"
#include "enemyplane.h"
#include "enemysorcerer.h"
#include "myplane.h"
#include "maulers.h"

using namespace std;
class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(int level);
    ~GameWindow();
    void initMapPixPosArr();
    void updateLevel(int level);
    void updateMeleeEnemyArr(int x,int y,int mapX,int mapY);
    void updateFlyEnemyArr(int x,int y,int mapX,int mapY);
    void updateEnemySorcererArr(int x,int y,int mapX,int mapY);
    void generateEnemy(enemyBase * eb,int type);
    void updateSoldiersArr(int x,int y,int mapX,int mapY);
    void generateSoldiers();
    void generateMyPlane();
    void generateMaulers();
    bool MeleeMoveEvent(QVector<Melee*> melee);
    bool flyerMoveEvent(QVector<flyObject *> flyer);
    bool sorcererMoveEvent(QVector<flyObject *> enemysorcerer);
    void MeleeMapMove(QVector<Melee*> melee);
    void flyerMapMove(QVector<flyObject *> flyer);
    //void sorcererMapMove(QVector<enemySorcerer *> enemysorcerer);
    void judgeFenceType();
    void paintEvent(QPaintEvent *pe);
    void mousePressEvent(QMouseEvent *me);
    void creatSelectBoxEvent(QMouseEvent *me);
    void towerSelectEvent(QMouseEvent *me);
    void showTowerAttackRangeEvent(QMouseEvent *me);
    void drawBackground(QPainter &p);
    void drawEnemy(QPainter &p);
    void drawSoldiers(QPainter &p);
    void drawTowerBase(QPainter &p);
    void drawTower(QPainter &p);
    void drawSelect(QPainter &p);
    void drawMap(QPainter &p);
    void drawBullet(QPainter &p);
    void drawRange(QPainter &p);
    void drawHealthValue(QPainter &p);
    void drawGameOver(QPainter &p);
    void drawGameWin(QPainter &p);
    void timerEvent(QTimerEvent *ev);
    bool event(QEvent *e);
    bool creatMap(int level);
    void meet(QVector<QVector<Melee*>> melee);
    void fight(Melee *enemy,Melee *soldiers);
    void fight(flyObject * enemysorcerer,Melee *soldiers);
    void cure();
    void attackEnemy();
    void attackSolider();
private:
    int level;
    int myMoney;
    int mapType;
    int waves;                                 //?????????
    int myHealthValue;                         //???????????????
    int initHealthValve;                       //???????????????
    QVector<enemyBase *> eB;                   //??????????????????
    myBase * mb;                               //??????????????????
    QVector<towerBase*> towerbases;            //???????????????
    int mx[4] = {0,1,0,-1};                    //????????????
    int my[4] = {-1,0,1,0};
    QLabel * myMoneyNum;                       //??????????????????
    QLabel * wavesNum;                         //??????????????????
    QVector<QVector<bool>> visit;              //??????????????????
    QMap<int,QString> mapArrImagePath;         //????????????????????????
    QVector<QVector<SubMap*>> mapImagePos;     //???????????????
    QVector<Melee*> enemy;                     //????????????????????????
    QVector<flyObject *> enemyplane;           //??????????????????
    QVector<flyObject *> enemysorcerer;        //???????????????
    QVector<Melee*> soldiers;                  //??????????????????
    QVector<Melee*> maulers;                   //??????????????????
    QVector<flyObject *> myplane;              //??????????????????
    QVector<Tower*> myTower;                   //?????????????????????
    Select* towerSelect;                       //???????????????
    QVector<QVector<int>> myMapArr;            //????????????
    QVector<Fence*> fence;                     //????????????
    QVector<QVector<Melee*>> roleArr;          //??????????????????????????????
signals:

};

#endif // GAMEWINDOW_H
