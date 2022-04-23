#ifndef SOLDIERS_H
#define SOLDIERS_H

#include <QString>
#include <QChar>
#include <QVector>
#include <melee.h>

class Soldiers : public Melee
{
public:
    Soldiers();
    Soldiers(int x,int y,int mapX,int mapY);
    void setAggressivity();
    QString getType();
    void setHealthValue();
private:

};

#endif // SOLDIERS_H
