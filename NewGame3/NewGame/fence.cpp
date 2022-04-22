#include "fence.h"

Fence::Fence()
{
    this->x = 0;
    this->y = 0;
    this->sx = 0;
    this->sy = 0;
    this->type = "F";
}
int Fence::getX()
{
    return this->x;
}

int Fence::getY()
{
    return this->y;
}

int Fence::getSx()
{
    return this->sx;
}

int Fence::getSy()
{
    return this->sy;
}

QString Fence::getType()
{
    return this->type;
}

void Fence::updateX(int x)
{
    this->x = x;
}

void Fence::updateY(int y)
{
    this->y = y;
}

void Fence::updateSx(int sx)
{
    this->sx = sx;
}

void Fence::updateSy(int sy)
{
    this->sy = sy;
}

void Fence::updateType(QString type)
{
    this->type = type;
}

bool Fence::creatTypeU(QPainter &p)  //横上
{
    int x = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    return true;
}

bool Fence::creatTypeD(QPainter &p)  //横下
{
    int x = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    return true;
}

bool Fence::creatTypeUD(QPainter &p)  //上下
{
    int x = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int x2 = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+x2,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x2 += 10;
    }
    return true;
}

bool Fence::creatTypeL(QPainter &p)  //竖左
{
    int y = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

bool Fence::creatTypeR(QPainter &p)  //竖右
{
    int y = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

bool Fence::creatTypeLR(QPainter &p)   //左右
{
    int y = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    int y2 = 0;
    for(int i = 0; i < 6; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y2,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y2 += 10;
    }
    return true;
}

bool Fence::creatTypeUDL(QPainter &p)  //上下左
{
    int x = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int x2 = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x2,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x2 += 10;
    }
    int y = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10 ;
    }
    return true;
}

bool Fence::creatTypeUDR(QPainter &p)  //上下右
{
    int x = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int x2 = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x2,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x2 += 10;
    }
    int y = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10 ;
    }
    return true;
}

bool Fence::creatTypeLRU(QPainter &p)  //左右上
{
    int y = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    int y2 = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y2,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y2 += 10;
    }
    int x = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    return true;
}

bool Fence::creatTypeLRD(QPainter &p)  //左右下
{
    int y = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    int y2 = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y2,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y2 += 10;
    }
    int x = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    return true;
}

bool Fence::creatTypeUDLR(QPainter &p)  //上下左右
{
    int y = 10;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    int y2 = 10;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y2,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y2 += 10;
    }
    int x = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int x2 = 20;
    for(int i = 0; i < 2; i++)
    {
        QRectF Parameter(this->sx+x2,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x2 += 10;
    }
    return true;
}

bool Fence::creatTypeUL(QPainter &p)  //上左
{
    int x = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int y = 20;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

bool Fence::creatTypeUR(QPainter &p)  //上右
{
    int x = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+10,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int y = 20;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

bool Fence::creatTypeDL(QPainter &p)  //下左
{
    int x = 10;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int y = 0;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+10,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

bool Fence::creatTypeDR(QPainter &p)  //下右
{
    int x = 0;
    for(int i = 0; i < 5; i++)
    {
        QRectF Parameter(this->sx+x,this->sy+40,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        x += 10;
    }
    int y = 0;
    for(int i = 0; i < 4; i++)
    {
        QRectF Parameter(this->sx+40,this->sy+y,10,10);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/black.png"),Stretch);
        y += 10;
    }
    return true;
}

