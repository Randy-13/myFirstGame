#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QChar>
#include <QString>
#include <QPair>
#include <QDebug>
#include <QTimer>
#include <QPushButton>
#include <QEvent>
#include <QMap>
#include "map.h"
#include "enemy.h"
#include "enemybase.h"


using namespace std;
class GameWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);
    GameWindow(int level);
    ~GameWindow();
    void initMapImagePosArr();
    void updateEnemyArr(int x,int y,int mapX,int mapY);
    void generateEnemy();
    bool EnemyMoveEvent();
    void EnemyMapMove();
    void paintEvent(QPaintEvent *pe);
    void drawEnemy(QPainter &p);
    void drawMap(QPainter &p);
    void timerEvent(QTimerEvent *ev);
    bool event(QEvent *e);
    bool creatMap();
private:
    int level;
    int mapType;
    enemyBase * eB;
    int mx[4] = {0,1,0,-1};                    //左下右上
    int my[4] = {-1,0,1,0};
    QVector<QVector<bool>> visit;              //是否访问数组
    QMap<int,QString> mapArrImagePath;         //记录对应图片地址
    QVector<QVector<SubMap*>> mapImagePos;     //记录坐标值
    QVector<Enemy*> enemy;                     //
    QVector<QVector<int>> myMapArr;            //地图数组
signals:

};

#endif // GAMEWINDOW_H
