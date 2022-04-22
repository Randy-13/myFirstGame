#ifndef ENEMY_H
#define ENEMY_H

#include <QChar>
#include <QString>
#include <QVector>

class Enemy
{
public:
    Enemy();
    Enemy(int x,int y,int mapX,int mapY);
    int getX();
    int getY();
    int getPreX();
    int getPreY();
    int getMapPosX();
    int getMapPosY();
    bool getPathCondition(int ti,int tj);
    bool getLiveState();
    QChar getMoveDirection();
    void updateX(int x);
    void updateY(int y);
    void updateMoveDirection(QChar dir);
    void updateLiveState(bool check);
    void updatePathCondition(int ti,int tj,bool chang);
    void initMovePathArr(int ti,int tj);
    void MapPosLeftMove();
    void MapPosRightMove();
    void MapPosUpMove();
    void MapPosDownMove();
private:
    int x;
    int y;
    bool live;
    int prex;
    int prey;
    int mapPosX;
    int mapPosY;
    QVector<QVector<bool>> movePathArr;
    QChar moveDirection;
};

#endif // ENEMY_H
