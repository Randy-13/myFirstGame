#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget{parent}
{
    this->setFixedSize(900,600);
}

GameWindow::GameWindow(int level)
{
    this->setFixedSize(900,600);          //设置窗口大小
    this->level = level;                  //标注关卡
    this->mapType = 3;                    //地图块类型
    this->initMapPixPosArr();             //初始化地图块放置位置
    this->creatMap();                     //创建地图
    this->judgeFenceType();
    QString title;                        //设置窗口标题
    switch (this->level) {
    case 1:  title = "The first level";
        break;
    case 2:  title = "The second level";
        break;
    case 3:  title = "The third level";
        break;
    default:
        break;
    }
    setWindowTitle(title);
    //this->generateEnemy();
    //this->generateSoldiers();
    QPushButton *btn = new QPushButton(this);
    btn->setText("增兵");
    btn->move(0,0);
    btn->show();
    connect(btn,&QPushButton::clicked,[=](){
        this->generateSoldiers();
    });
    QTimer * timer = new QTimer(this);
    timer->start(10);
    static int times = 0;
    connect(timer,&QTimer::timeout,[=](){
        if(times % 300 == 0)
        {
            this->generateEnemy();
        }
        if(times % 60 == 0)
        {
            this->MeleeMoveEvent(this->enemy);
            this->MeleeMoveEvent(this->soldiers);
            meet(this->roleArr);
        }
        this->MeleeMapMove(this->enemy);
        this->MeleeMapMove(this->soldiers);
        update();
        times++;

    });
    //定时器
//    QTimer * timer = new QTimer(this);
//    timer->start(1000);
//    connect(timer,&QTimer::timeout,[=](){
//        static int timetest = 1;
//        this->lab1->setText(QString::number(timetest++));
//    });
//    update();
//    this->lab1 = new QLabel;
//    lab1->setParent(this);
//    lab1->move(0,0);
//    lab1->setFixedSize(100,50);
//    lab1->show();
//    timeId = startTimer(std::chrono::seconds(1));

}

void GameWindow::initMapPixPosArr()
{
    this->mapImagePos.resize(10);
    for(int i = 0; i < mapImagePos.size();i++)
    {
        this->mapImagePos[i].resize(15);
    }
    int tx = 0; int ty = 0;
    for(int i = 0; i < mapImagePos.size(); i++)
    {
        for(int j = 0; j < mapImagePos[0].size(); j++)
        {
             mapImagePos[i][j] = new SubMap;
             mapImagePos[i][j]->updateXY(tx,ty);
             if(tx < 840)
             {
                 tx += 60;
             }else{
                 tx = 0;
             }    
        }
        ty += 60;
    }
    return;
}

void GameWindow::generateEnemy()
{
    int tx = this->eB->getX();
    int ty = this->eB->getY();
    this->updateEnemyArr(tx,ty,this->mapImagePos[tx][ty]->getX(),this->mapImagePos[tx][ty]->getY());
}

void GameWindow::updateEnemyArr(int x,int y,int mapX,int mapY)
{
    Melee * tpE = new Enemy(x,y,mapX,mapY);
    tpE->initMovePathArr(this->myMapArr.size(),this->myMapArr[0].size());
    this->enemy.push_back(tpE);
}

void GameWindow::generateSoldiers()
{
    int tx = this->mb->getX();
    int ty = this->mb->getY();
    this->updateSoldiersArr(tx,ty,this->mapImagePos[tx][ty]->getX(),this->mapImagePos[tx][ty]->getY());
}

void GameWindow::updateSoldiersArr(int x,int y,int mapX,int mapY)
{
    Melee * tpS = new Soldiers(x,y,mapX,mapY);
    tpS->initMovePathArr(this->myMapArr.size(),this->myMapArr[0].size());
    this->soldiers.push_back(tpS);
}


void GameWindow::drawBackground(QPainter &p)
{
    QRectF Parameter(0,0,900,600);
    QRectF Stretch(0,0,0,0);
    p.drawPixmap(Parameter,QPixmap(":/image/blank.png"),Stretch);
}

void GameWindow::drawMap(QPainter &p)
{
    //画基地
    for(int i = 0; i < myMapArr.size(); i++)
    {
        for(int j = 0; j < myMapArr[0].size(); j++)
        {
            if(myMapArr[i][j] == 342)
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),60,60);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(342).value(),Stretch);
            }else if(myMapArr[i][j] == 520)
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),60,60);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(520).value(),Stretch);
            }
        }
    }
    //画栅栏
    for(int i = 0; i < this->fence.size(); i++)
    {
        if(this->fence[i]->getType() == "U")
        {
            this->fence[i]->creatTypeU(p);
        }else if(this->fence[i]->getType() == "D")
        {
            this->fence[i]->creatTypeD(p);
        }else if(this->fence[i]->getType() == "UD")
        {
            this->fence[i]->creatTypeUD(p);
        }else if(this->fence[i]->getType() == "L")
        {
            this->fence[i]->creatTypeL(p);
        }else if(this->fence[i]->getType() == "R")
        {
            this->fence[i]->creatTypeR(p);
        }else if(this->fence[i]->getType() == "LR")
        {
            this->fence[i]->creatTypeLR(p);
        }else if(this->fence[i]->getType() == "UDL")
        {
            this->fence[i]->creatTypeUDL(p);
        }else if(this->fence[i]->getType() == "UDR")
        {
            this->fence[i]->creatTypeUDR(p);
        }else if(this->fence[i]->getType() == "LRU")
        {
            this->fence[i]->creatTypeLRU(p);
        }else if(this->fence[i]->getType() == "LRD")
        {
            this->fence[i]->creatTypeLRD(p);
        }else if(this->fence[i]->getType() == "UDLR")
        {
            this->fence[i]->creatTypeUDLR(p);
        }else if(this->fence[i]->getType() == "UL")
        {
            this->fence[i]->creatTypeUL(p);
        }else if(this->fence[i]->getType() == "UR")
        {
            this->fence[i]->creatTypeUR(p);
        }else if(this->fence[i]->getType() == "DL")
        {
            this->fence[i]->creatTypeDL(p);
        }else if(this->fence[i]->getType() == "DR")
        {
            this->fence[i]->creatTypeDR(p);
        }
    }

}

void GameWindow::drawEnemy(QPainter &p)   //画敌人
{
    for(int i = 0; i < this->enemy.size(); i++)
    {
        if(enemy[i]->getLiveState() == true)
        {
            QRectF Parameter(this->enemy[i]->getMapPosX()-10,this->enemy[i]->getMapPosY()-10,80,80);
            QRectF Stretch(0,0,0,0);
            p.drawPixmap(Parameter,QPixmap(":/image/GunTruck2.png"),Stretch);
        }
    }
}

void GameWindow::drawSoldiers(QPainter &p)
{
    for(int i = 0; i < this->soldiers.size(); i++)
    {
        if(soldiers[i]->getLiveState() == true)
        {
            QRectF Parameter(this->soldiers[i]->getMapPosX()-10,this->soldiers[i]->getMapPosY()-10,80,80);
            QRectF Stretch(0,0,0,0);
            p.drawPixmap(Parameter,QPixmap(":/image/soldiers1.png"),Stretch);
        }
    }
}

void GameWindow::paintEvent(QPaintEvent *pe)
{
    static int times = 1;
    //qDebug() << "多次调用" << times++;
    QPainter painter(this);
    drawBackground(painter);
    drawMap(painter);
    //画敌人
    drawEnemy(painter);
    //
    drawSoldiers(painter);
}

bool GameWindow::creatMap()
{
    //model
    int map[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //1
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //2
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //3
        {0,0,0,0,0,0,0,2,2,2,2,2,2,2,2},     //4
        {2,2,2,2,2,2,2,2,1,1,1,1,1,1,342},     //5
      {520,1,1,1,1,1,1,1,1,2,2,2,2,2,2},     //6
        {2,2,2,2,2,2,2,2,2,2,0,0,0,0,0},     //7
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //8
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //9
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //10
     };
    //firstMap
//    int map[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
//        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //1
//        {0,0,0,2,2,2,2,2,2,2,2,2,2,2,2},     //2
//        {0,0,0,2,1,1,1,1,1,1,1,1,1,1,342},   //3
//        {0,0,0,2,1,2,2,2,2,2,2,2,2,2,2},     //4
//        {0,0,0,2,1,1,1,1,1,1,1,1,2,0,0},     //5
//        {0,0,0,2,1,2,2,2,2,2,2,1,2,0,0},     //6
//        {2,2,2,2,1,2,2,2,2,2,2,1,2,0,0},     //7
//      {520,1,1,1,1,1,1,1,1,1,1,1,2,0,0},     //8
//        {2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},     //9
//        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //10
//    };
    //secondMap
//    int map[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
//        {0,0,0,0,0,0,0,2,2,2,2,2,2,2,0},     //1
//        {0,0,2,2,2,2,2,2,1,1,1,1,1,2,0},     //2
//        {0,0,2,1,1,1,1,1,1,2,2,2,1,2,342},   //3
//        {0,0,2,1,1,1,1,1,1,1,1,2,1,2,1},     //4
//        {0,0,2,2,2,2,2,2,2,2,1,2,1,1,1},     //5
//        {0,0,0,0,0,0,0,0,0,2,1,2,2,2,2},     //6
//        {2,2,2,2,2,2,2,2,2,2,1,1,2,0,0},     //7
//      {520,1,1,1,1,1,1,1,1,1,1,1,2,0,0},     //8
//        {2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},     //9
//        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //10
//    };
    //thirdMap
//    int map[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
//        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,2},     //1
//        {0,0,2,1,1,1,1,1,1,1,1,1,1,1,1},     //2
//        {0,0,2,1,2,2,2,2,2,2,2,2,2,2,342},     //3
//        {0,0,2,1,2,2,2,1,1,1,2,0,0,0,0},     //4
//        {0,0,2,1,1,1,1,1,2,1,2,0,0,0,0},     //5
//        {2,2,2,2,2,2,2,2,1,1,2,0,0,0,0},     //6
//        {2,1,1,1,1,1,1,2,1,2,2,0,0,0,0},     //7
//      {520,1,2,2,2,2,1,2,1,2,0,0,0,0,0},     //8
//        {2,2,2,0,0,2,1,1,1,2,0,0,0,0,0},     //9
//        {0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},     //10
//    };
    this->myMapArr.resize(10);
    this->visit.resize(10);
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        this->myMapArr[i].resize(15);
        this->visit[i].resize(15,false);
    }
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        for(int j = 0; j < this->myMapArr[0].size(); j++)
        {
           myMapArr[i][j] = map[i][j];
           if(map[i][j] == 342)
           {
               this->eB = new enemyBase(i,j);      //记录敌方基地地址
           }
           if(map[i][j] == 2)
           {
               Fence *tf = new Fence;
               tf->updateX(i);
               tf->updateY(j);
               tf->updateSx(this->mapImagePos[i][j]->getX());
               tf->updateSy(this->mapImagePos[i][j]->getY());
               this->fence.push_back(tf);
           }
           if(map[i][j] == 1)
           {
               this->visit[i][j] = true;
           }
           if(map[i][j] == 520)
           {
               this->mb = new myBase(i,j);
           }
        }
    }

     this->mapArrImagePath.insert(0,":/image/blank.png");         //配套键值和图片地址  0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
     this->mapArrImagePath.insert(520,":/image/base.png");
     this->mapArrImagePath.insert(342,":/image/base.png");
    return true;
}

void GameWindow::timerEvent(QTimerEvent *event)
{


}


bool GameWindow::event(QEvent *e)  //调配event事件
{
    return QWidget::event(e);
}

void GameWindow::meet(QVector<QVector<Melee*>> melee)
{
    melee.clear();
    melee.push_back(this->enemy);
    melee.push_back(this->soldiers);
    for(int j = 0; j < melee[0].size(); j++)
    {
        for(int k = 0; k < melee[1].size(); k++)
        {
            int tp = qAbs(melee[0][j]->getX() - melee[1][k]->getX()) + qAbs(melee[0][j]->getY() - melee[1][k]->getY());
            if(melee[0][j]->getMoveDirection() == 'S' && melee[1][k]->getMoveDirection() == 'S' && tp == 1)
            {
                fight(melee[0][j],melee[1][k]);
            }
        }
    }
}

void GameWindow::fight(Melee *enemy,Melee *soldiers)
{
    if(enemy->getLiveState() && soldiers->getLiveState())
    {
        if(enemy->updateHealthValue(-soldiers->getAggressivity()))
        {
            qDebug() << "敌人收到攻击！！"<< " 剩余生命值："<<enemy->getHealvalue();
        }else{
            qDebug() << "敌人死亡！";
            this->visit[enemy->getX()][enemy->getY()] = true;
            enemy->updateLiveState(false);
        }

        if(soldiers->updateHealthValue(-enemy->getAggressivity()))
        {
             qDebug() << "我方单位收到攻击！！"<< " 剩余生命值："<<soldiers->getHealvalue();
        }else{
            qDebug() << "我方战士牺牲！";
            this->visit[soldiers->getX()][soldiers->getY()] = true;
            soldiers->updateLiveState(false);
        }
    }
}

bool GameWindow::MeleeMoveEvent(QVector<Melee*> melee)
{
    //近战单位移动
    bool check = false;
    for(int k = 0; k < melee.size(); k++)
    {
        for(int i = 0; i < 4; i++)
        {
            int tx = melee[k]->getX() + mx[i];
            int ty = melee[k]->getY() + my[i];
            if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 1 && melee[k]->getLiveState() && this->visit[tx][ty] && melee[k]->getPathCondition(tx,ty))
            {
                melee[k]->updatePathCondition(tx,ty,false);
                melee[k]->updateX(tx);
                melee[k]->updateY(ty);
                this->visit[melee[k]->getPreX()][melee[k]->getPreY()] = true;
                //qDebug() << k << melee[k]->getType() << melee[k]->getPreX() << melee[k]->getPreY();
                this->visit[tx][ty] = false;  //
                //qDebug() << " 成功移动！";
                switch (i) {              //左下右上
                case 0:
                    melee[k]->updateMoveDirection('L');
                    break;
                case 1:
                    melee[k]->updateMoveDirection('D');
                    break;
                case 2:
                    melee[k]->updateMoveDirection('R');
                    break;
                case 3:
                    melee[k]->updateMoveDirection('U');
                    break;
                default:
                    break;
                }
                check = true;
                break;
            }else if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 520 && melee[k]->getLiveState() && melee[k]->getType() == "Enemy")
            {
                check = false;
                melee[k]->updateX(tx);
                melee[k]->updateY(ty);
                int dx = melee[k]->getPreX();
                int dy = melee[k]->getPreY();
                this->visit[dx][dy] = true;
                melee[k]->updateLiveState(false);
                break;
            }else if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 342 && melee[k]->getLiveState() && melee[k]->getType() == "Soldiers")
            {
                check = false;
                melee[k]->updateX(tx);
                melee[k]->updateY(ty);
                int dx = melee[k]->getPreX();
                int dy = melee[k]->getPreY();
                this->visit[dx][dy] = true;
                melee[k]->updateLiveState(false);
                break;
            }else if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 1)
            {
                melee[k]->updateMoveDirection('S');
            }
        }
    }
    return check;
}

void GameWindow::MeleeMapMove(QVector<Melee*> melee)
{
    for(int k = 0; k < melee.size(); k++)
    {
        if(melee[k]->getLiveState())
        {
            if(melee[k]->getMoveDirection() == 'D')
            {
                melee[k]->MapPosDownMove();
            }else if(melee[k]->getMoveDirection() == 'L')
            {
                melee[k]->MapPosLeftMove();
            }else if(melee[k]->getMoveDirection() == 'R')
            {
                melee[k]->MapPosRightMove();
            }else if(melee[k]->getMoveDirection() == 'U')
            {
                melee[k]->MapPosUpMove();
            }else if(melee[k]->getMoveDirection() == 'S')
            {
                continue;
            }
        }
    }
}

void GameWindow::judgeFenceType()
{
    int height = this->myMapArr.size();
    int width = this->myMapArr[0].size();
    bool checkLeft = false;
    bool checkRight = false;
    bool checkUp = false;
    bool checkDown = false;

    //判断上型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(i == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("U");
        }
    }

    //判断下型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(i == 3)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("D");
        }
    }

    //判断上下型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UD");
        }
    }

    //判断左型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(i == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("L");
        }
    }

    //判断右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(i == 0)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("R");
        }
    }

    //判断左右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("LR");
        }
    }

    //判断上左型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UL");
        }
    }

    //判断上右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UR");
        }
    }

    //判断下左型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("DL");
        }
    }

    //判断下右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("DR");
        }
    }

    //判断上下左型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 2)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UDL");
        }
    }

    //判断上下右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 2)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UDR");
        }
    }

    //判断左右上型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 2)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("LRU");
        }
    }

    //判断左右下型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 2)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            qDebug() << x << "左右下" << y;
            this->fence[m]->updateType("LRD");
        }
    }

    //判断上下左右型
    for(int m = 0; m < this->fence.size(); m++)
    {
        int x = this->fence[m]->getX();
        int y = this->fence[m]->getY();
        checkLeft = false;
        checkRight = false;
        checkUp = false;
        checkDown = false;
        for(int i = 0; i < 4; i++)
        {
            int tx = x + mx[i];             //左下右上
            int ty = y + my[i];
            if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 0 && myMapArr[tx][ty] == 1)
            {
                checkLeft = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 1 && myMapArr[tx][ty] == 1)
            {
                checkDown = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 2 && myMapArr[tx][ty] == 1)
            {
                checkRight = true;
            }else if(tx >= 0 && tx < height && ty >= 0 && ty < width && i == 3 && myMapArr[tx][ty] == 1)
            {
                checkUp = true;
            }
        }
        if(checkLeft && checkRight && checkUp && checkDown)
        {
            this->fence[m]->updateType("UDLR");
        }
    }
}

GameWindow::~GameWindow()
{

}
