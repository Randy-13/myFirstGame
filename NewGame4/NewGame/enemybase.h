#ifndef ENEMYBASE_H
#define ENEMYBASE_H


class enemyBase
{
public:
    enemyBase();
    enemyBase(int x,int y);
    int getX();
    int getY();
private:
    int x;
    int y;
};

#endif // ENEMYBASE_H
