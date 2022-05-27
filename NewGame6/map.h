#ifndef MAP_H
#define MAP_H

#include <QLabel>
#include <QVector>
class SubMap
{
public:
    int getX();
    int getY();
    bool updateXY(int tx,int ty);
    SubMap();
private:
    int mapType;
    int x;
    int y;
};

#endif // MAP_H
