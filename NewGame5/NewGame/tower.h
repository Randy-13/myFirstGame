#ifndef TOWER_H
#define TOWER_H

#include "QPushButton"
#include <QDebug>
class Tower : public QPushButton
{
public:
    Tower();
    Tower(int x,int y,int mapX,int mapY,QString picturePath);
    int getMapX();
    int getMapY();
    int getX();
    int getY();
    int getAggressivity();
    bool checkAttackRange(int enemyMapX,int enemyMapY);
    QString getPicturePath();
    QVector<int> attackEventPos;      //塔攻击锚点
private:
    int x;
    int y;
    int mapX;
    int mapY;
    int attackR;
    int aggressivity;
    bool live;
    QString picturePath;
};

#endif // TOWER_H
