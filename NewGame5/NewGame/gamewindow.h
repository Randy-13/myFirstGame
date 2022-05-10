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
#include "select.h"
#include <QMouseEvent>
#include <QMainWindow>

using namespace std;
class GameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(int level);
    ~GameWindow();
    void initMapPixPosArr();
    void updateEnemyArr(int x,int y,int mapX,int mapY);
    void generateEnemy();
    void updateSoldiersArr(int x,int y,int mapX,int mapY);
    void generateSoldiers();
    bool MeleeMoveEvent(QVector<Melee*> melee);
    void MeleeMapMove(QVector<Melee*> melee);
    void judgeFenceType();
    void paintEvent(QPaintEvent *pe);
    void mousePressEvent(QMouseEvent *me);
    void drawBackground(QPainter &p);
    void drawEnemy(QPainter &p);
    void drawSoldiers(QPainter &p);
    void drawTowerBase(QPainter &p);
    void drawTower(QPainter &p);
    void drawSelect(QPainter &p);
    void drawMap(QPainter &p);
    void drawBullet(QPainter &p);
    void timerEvent(QTimerEvent *ev);
    bool event(QEvent *e);
    bool creatMap(int level);
    void meet(QVector<QVector<Melee*>> melee);
    void fight(Melee *enemy,Melee *soldiers);
    void attackEnemy();
private:
    int level;
    int mapType;
    enemyBase * eB;                            //敌方基地信息
    myBase * mb;                               //我方基地信息
    QVector<towerBase*> towerbases;            //塔基座信息
    int mx[4] = {0,1,0,-1};                    //左下右上
    int my[4] = {-1,0,1,0};
    QVector<QVector<bool>> visit;              //是否访问数组
    QMap<int,QString> mapArrImagePath;         //记录对应图片地址
    QVector<QVector<SubMap*>> mapImagePos;     //记录坐标值
    QVector<Melee*> enemy;                     //敌方近战单位数组
    QVector<Melee*> soldiers;                  //我方进战单位
    QVector<Tower*> myTower;                   //我方防御塔单位
    Select* towerSelect;                       //选择框指针
    QVector<QVector<int>> myMapArr;            //地图数组
    QVector<Fence*> fence;                     //栅栏数组
    QVector<QVector<Melee*>> roleArr;          //一条路上子地图的角色
signals:

};

#endif // GAMEWINDOW_H
