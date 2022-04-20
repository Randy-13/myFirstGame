#ifndef ENEMY_H
#define ENEMY_H

#include <QChar>

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
    bool getLiveState();
    QChar getMoveDirection();
    void updateX(int x);
    void updateY(int y);
    void updateMoveDirection(QChar dir);
    void updateLiveState(bool check);
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
    QChar moveDirection;
};

#endif // ENEMY_H
