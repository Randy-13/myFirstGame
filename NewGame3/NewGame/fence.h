#ifndef FENCE_H
#define FENCE_H

#include <QPainter>
#include <QString>
class Fence
{
public:
    Fence();
    int getX();
    int getY();
    int getSx();
    int getSy();
    QString getType();
    void updateX(int x);
    void updateY(int y);
    void updateSx(int sx);
    void updateSy(int sy);
    void updateType(QString type);
    bool creatTypeU(QPainter &p);  //横上
    bool creatTypeD(QPainter &p);  //横下
    bool creatTypeUD(QPainter &p);  //上下
    bool creatTypeL(QPainter &p);  //竖左
    bool creatTypeR(QPainter &p);  //竖右
    bool creatTypeLR(QPainter &p);  //左右
    bool creatTypeUDL(QPainter &p);  //上下左
    bool creatTypeUDR(QPainter &p);  //上下右
    bool creatTypeLRU(QPainter &p);  //左右上
    bool creatTypeLRD(QPainter &p);  //左右下
    bool creatTypeUDLR(QPainter &p);  //上下左右
    bool creatTypeUL(QPainter &p);  //上左
    bool creatTypeUR(QPainter &p);  //上右
    bool creatTypeDL(QPainter &p);  //下左
    bool creatTypeDR(QPainter &p);  //下右
private:
    int sx;
    int sy;
    int x;
    int y;
    QString type;
};

#endif // FENCE_H
