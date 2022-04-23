#ifndef MYBASE_H
#define MYBASE_H


class myBase
{
public:
    myBase();
    myBase(int x,int y);
    int getX();
    int getY();
private:
    int x;
    int y;
};

#endif // MYBASE_H
