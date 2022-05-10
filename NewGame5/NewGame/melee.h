#ifndef MELEE_H
#define MELEE_H

#include <QChar>
#include <QString>
#include <QVector>

class Melee
{
public:
    Melee();
    Melee(int x,int y,int mapX,int mapY);
    int getX();
    int getY();
    int getPreX();
    int getPreY();
    int getMapPosX();
    int getMapPosY();
    int getHealvalue();
    int getNowHealthValue();
    int getAggressivity();
    bool getPathCondition(int ti,int tj);
    bool getLiveState();
    QChar getMoveDirection();
    void updateX(int x);
    void updateY(int y);
    void updateMoveDirection(QChar dir);
    void updateLiveState(bool check);
    void updatePathCondition(int ti,int tj,bool chang);
    bool updateNowHealthValue(int num);
    void initMovePathArr(int ti,int tj);
    void MapPosLeftMove();
    void MapPosRightMove();
    void MapPosUpMove();
    void MapPosDownMove();
    virtual QString getType() = 0;
    virtual void setAggressivity();
    virtual void setHealthValue();
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
protected:
    int aggressivity;
    int healthValue;
    int nowHealthValue;
    QString type;
};

#endif // MELEE_H
