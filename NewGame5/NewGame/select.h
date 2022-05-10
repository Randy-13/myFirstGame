#ifndef SELECT_H
#define SELECT_H

#include <QVector>
#include <QString>

class Select
{
public:
    ~Select();
    Select(int x,int y,int mapX,int mapY);
    int getMapX();
    int getMapY();
    int getX();
    int getY();
    QString picturePath[3];
private:
    int x;
    int y;
    int mapX;
    int mapY;
};

#endif // SELECT_H
