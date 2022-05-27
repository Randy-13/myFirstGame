#ifndef BASE_H
#define BASE_H


class Base
{
public:
    Base();
    Base(int x,int y,int mapX,int mapY);
    int getX();
    int getY();
    int getMapX();
    int getMapY();
private:
    int x;
    int y;
    int mapX;
    int mapY;
};

#endif // BASE_H
