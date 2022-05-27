#ifndef MAULERS_H
#define MAULERS_H

#include <QString>
#include <QChar>
#include <QVector>
#include <melee.h>

class Maulers : public Melee
{
public:
    Maulers();
    Maulers(int x,int y,int mapX,int mapY);
    void setAggressivity();
    QString getType();
    void setHealthValue();
};

#endif // MAULERS_H
