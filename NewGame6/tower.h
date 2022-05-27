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
    void updateCost(int cost);
    void updateIfShowRange(bool update);
    int getCost();
    int getAggressivity();
    bool checkAttackRange(int enemyMapX,int enemyMapY);
    bool checkIfShowRange();
    int getAttackR();
    QString getPicturePath();
    QVector<int> attackEventPos;        //塔攻击锚点
protected:
    int x;
    int y;
    int cost;
    int mapX;
    int mapY;
    int attackR;
    int aggressivity;
    bool live;
    bool showRange;
    QString picturePath;
};

#endif // TOWER_H
