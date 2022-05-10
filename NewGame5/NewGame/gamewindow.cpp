#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(900,600);
}

GameWindow::GameWindow(int level)
{
    this->setFixedSize(900,600);          //设置窗口大小
    this->level = level;                  //标注关卡
    this->mapType = 3;                    //地图块类型
    this->initMapPixPosArr();             //初始化地图块放置位置
    this->towerSelect = NULL;             //初始化选择框指针
    this->creatMap(this->level);          //创建地图
    this->judgeFenceType();               //判断边界类型
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
    btn->setText("士兵出击");
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
            this->attackEnemy();
            this->MeleeMoveEvent(this->soldiers);
            meet(this->roleArr);
        }
        this->MeleeMapMove(this->enemy);
        this->MeleeMapMove(this->soldiers);
        update();
        times++;

    });

//    for(int i = 0; i < this->towerbases.size(); i++)
//    {
//        connect(this->towerbases[i],&QPushButton::clicked,[=](){
//            qDebug()<<this->towerbases[i]->getMapX();
//            QLabel * tpTower = new QLabel(this->towerbases[i]);
//            tpTower->resize(60,60);
//            QPixmap p1(":/image/tower1.jpeg");
//            p1 = p1.scaled(60,60);
//            tpTower->setPixmap(p1);
//            tpTower->move(this->towerbases[i]->getMapX(),this->towerbases[i]->getMapY());
//            tpTower->raise();
//            tpTower->setWindowFlags(Qt::WindowStaysOnTopHint);

//        });
//    }
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

void GameWindow::paintEvent(QPaintEvent *pe)
{
    static int times = 1;
    //qDebug() << "多次调用" << times++;
    QPainter painter(this);
    drawBackground(painter);
    drawMap(painter);
    //画敌人
    drawEnemy(painter);
    //画士兵
    drawSoldiers(painter);
    //画防御塔基座
    drawTowerBase(painter);
    //画选择框
    drawSelect(painter);
    //画防御塔
    drawTower(painter);
    //画激光
    drawBullet(painter);
}

void GameWindow::mousePressEvent(QMouseEvent *me)
{
    if(this->towerSelect != NULL)
    {
        if(me->button() == Qt::LeftButton)
        {
            if(me->x() >= towerSelect->getMapX() && me->x() < towerSelect->getMapX() + 60 && me->y() >= towerSelect->getMapY() && me->y() < towerSelect->getMapY() + 60)
            {
                Tower * tptower = new Tower(towerSelect->getX(),towerSelect->getY(),towerSelect->getMapX()+60,towerSelect->getMapY()+60,towerSelect->picturePath[0]);
                this->myTower.push_back(tptower);
                tptower->attackEventPos.resize(4);
                for(int i = 0; i < 4; i++)
                {
                    tptower->attackEventPos[i] = -1;
                }
                delete towerSelect;
                towerSelect = NULL;
            }else if(me->x() >= towerSelect->getMapX() + 60 && me->x() < towerSelect->getMapX() + 120 && me->y() >= towerSelect->getMapY() && me->y() < towerSelect->getMapY() + 60)
            {
                Tower * tptower = new Tower(towerSelect->getX(),towerSelect->getY(),towerSelect->getMapX()+60,towerSelect->getMapY()+60,towerSelect->picturePath[1]);
                this->myTower.push_back(tptower);
                tptower->attackEventPos.resize(4);
                for(int i = 0; i < 4; i++)
                {
                    tptower->attackEventPos[i] = -1;
                }
                delete towerSelect;
                towerSelect = NULL;
            }else if(me->x() >= towerSelect->getMapX() + 120 && me->x() < towerSelect->getMapX() + 180 && me->y() >= towerSelect->getMapY() && me->y() < towerSelect->getMapY() + 60)
            {
                Tower * tptower = new Tower(towerSelect->getX(),towerSelect->getY(),towerSelect->getMapX()+60,towerSelect->getMapY()+60,towerSelect->picturePath[2]);
                this->myTower.push_back(tptower);
                tptower->attackEventPos.resize(4);
                for(int i = 0; i < 4; i++)
                {
                    tptower->attackEventPos[i] = -1;
                }
                delete towerSelect;
                towerSelect = NULL;
            }
        }
    }

    for(int i = 0; i < this->towerbases.size(); i++)
    {
        int tx = towerbases[i]->getMapX();
        int ty = towerbases[i]->getMapY();
        if(me->x() >= tx && me->x() < tx + 60 && me->y() >= ty && me->y() < ty + 60)
        {
            if(me->button() == Qt::LeftButton)
            {
               qDebug()<<"鼠标摁下！" << tx << ty;
               Select *tpselect =new Select(towerbases[i]->getX(),towerbases[i]->getY(),tx-60,ty-60);//构造一个选择框
               this->towerSelect = tpselect;
               update();
            }
        }
    }


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

void GameWindow::drawEnemy(QPainter &p)   //画敌人
{
    for(int i = 0; i < this->enemy.size(); i++)
    {
        if(enemy[i]->getLiveState() == true)
        {
            QRectF Parameter(this->enemy[i]->getMapPosX()-10,this->enemy[i]->getMapPosY()-10,80,80);
            QRectF Stretch(0,0,0,0);
            p.drawPixmap(Parameter,QPixmap(":/image/Thief.jpeg"),Stretch);
            //画血条
            QBrush red_brush(QColor(255,0,0));//把刷子设置为红色
            p.setBrush(red_brush);//应用刷子
            float rate = 1.0*enemy[i]->getNowHealthValue()/enemy[i]->getHealvalue();//计算比例
            p.drawRect(this->enemy[i]->getMapPosX(),this->enemy[i]->getMapPosY(),rate*70,80*0.1);//绘制矩形
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
            p.drawPixmap(Parameter,QPixmap(":/image/Police.png"),Stretch);
            //画血条
            QBrush green_brush(QColor(0,255,127));//把刷子设置为绿色
            p.setBrush(green_brush);//应用刷子
            float rate = 1.0*soldiers[i]->getNowHealthValue()/soldiers[i]->getHealvalue();//计算比例
            p.drawRect(this->soldiers[i]->getMapPosX(),this->soldiers[i]->getMapPosY(),rate*70,80*0.1);//绘制矩形
        }
    }
}

 void GameWindow::drawTowerBase(QPainter &p)
 {
    for(int i = 0; i < this->towerbases.size(); i++)
    {
        QRectF Parameter(this->towerbases[i]->getMapX(),this->towerbases[i]->getMapY(),60,60);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(":/image/gray.png"),Stretch);
    }
 }

 void GameWindow::drawTower(QPainter &p)
 {
     for(int i = 0; i < this->myTower.size(); i++)
     {
         QRectF Parameter(this->myTower[i]->getMapX(),this->myTower[i]->getMapY(),60,60);
         QRectF Stretch(0,0,0,0);
         p.drawPixmap(Parameter,QPixmap(myTower[i]->getPicturePath()),Stretch);
     }
 }

 void GameWindow::drawSelect(QPainter &p)
 {
    if(this->towerSelect != NULL)
    {
        towerSelect->picturePath[0] = ":/image/tower1.png";
        towerSelect->picturePath[1] = ":/image/tower2.png";
        towerSelect->picturePath[2] = ":/image/tower1.png";
        QRectF Parameter(this->towerSelect->getMapX(),towerSelect->getMapY(),60,60);
        QRectF Stretch(0,0,0,0);
        p.drawPixmap(Parameter,QPixmap(towerSelect->picturePath[0]),Stretch);

        QRectF Parameter2(this->towerSelect->getMapX()+60,towerSelect->getMapY(),60,60);
        QRectF Stretch2(0,0,0,0);
        p.drawPixmap(Parameter2,QPixmap(towerSelect->picturePath[1]),Stretch2);

        QRectF Parameter3(this->towerSelect->getMapX()+120,towerSelect->getMapY(),60,60);
        QRectF Stretch3(0,0,0,0);
        p.drawPixmap(Parameter3,QPixmap(towerSelect->picturePath[2]),Stretch3);
    }
 }

 void GameWindow::drawBullet(QPainter &p)
 {
     for(int i = 0; i < this->myTower.size(); i++)
     {
         if(this->myTower[i]->attackEventPos[0] != -1 && this->myTower[i]->attackEventPos[1] != -1 && this->myTower[i]->attackEventPos[2] != -1 && this->myTower[i]->attackEventPos[3] != -1)
         {
             QBrush blue_brush(QColor(0,245,255));
             p.setBrush(blue_brush);//应用刷子
             p.drawLine(this->myTower[i]->attackEventPos[0],this->myTower[i]->attackEventPos[1],this->myTower[i]->attackEventPos[2],this->myTower[i]->attackEventPos[3]);
             for(int j = 0; j < 4; j++)
             {
                 this->myTower[i]->attackEventPos[j] = -1;
             }
         }
     }
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

bool GameWindow::creatMap(int level)
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
    int map1[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //1
        {0,0,0,2,2,2,2,2,2,2,2,2,2,2,2},     //2
        {0,0,0,2,1,1,1,1,1,1,1,1,1,1,342},   //3
        {0,0,0,2,1,2,2,2,2,2,2,2,2,2,2},     //4
        {0,0,0,2,1,1,1,1,1,1,1,1,2,0,0},     //5
        {0,0,0,2,2,2,2,2,2,2,2,1,2,0,0},     //6
        {2,2,2,2,2,2,2,2,2,2,2,1,2,0,0},     //7
      {520,1,1,1,1,1,1,1,1,1,1,1,2,0,0},     //8
        {2,2,2,2,2,2,2,2,2,2,2,2,2,0,0},     //9
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //10
    };
    //secondMap
    int map2[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
        {0,0,0,0,0,0,0,2,2,2,2,2,2,2,0},     //1
        {0,0,2,2,2,2,2,2,1,1,1,1,1,2,0},     //2
        {0,0,2,1,1,1,1,1,1,2,2,2,1,2,342},   //3
        {0,0,2,1,2,2,2,2,2,2,2,2,1,2,1},     //4
        {0,0,2,1,1,1,1,1,1,1,1,2,1,1,1},     //5
        {0,0,2,2,2,2,2,2,2,2,1,2,2,2,2},     //6
        {2,2,2,2,2,2,2,2,2,2,1,2,0,0,0},     //7
      {520,1,1,1,1,1,1,1,1,1,1,2,0,0,0},     //8
        {2,2,2,2,2,2,2,2,2,2,2,2,0,0,0},     //9
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},     //10
    };
    //thirdMap
    int map3[10][15] = {                      // 模板 0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
        {0,0,2,2,2,2,2,2,2,2,2,2,2,2,2},     //1
        {0,0,2,1,1,1,1,1,1,1,1,1,1,1,1},     //2
        {0,0,2,1,2,2,2,2,2,2,2,2,2,2,342},     //3
        {0,0,2,1,2,2,2,1,1,1,2,0,0,0,0},     //4
        {0,0,2,1,1,1,1,1,2,1,2,0,0,0,0},     //5
        {2,2,2,2,2,2,2,2,1,1,2,0,0,0,0},     //6
        {2,1,1,1,1,1,1,2,1,2,2,0,0,0,0},     //7
      {520,1,2,2,2,2,1,2,1,2,0,0,0,0,0},     //8
        {2,2,2,0,0,2,1,1,1,2,0,0,0,0,0},     //9
        {0,0,0,0,0,2,2,2,2,2,0,0,0,0,0},     //10
    };

    this->myMapArr.resize(10);
    this->visit.resize(10);
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        this->myMapArr[i].resize(15);
        this->visit[i].resize(15,false);
    }

    int index = 0;
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        for(int j = 0; j < this->myMapArr[0].size(); j++)
        {
            int tpmap =0;
            int tpmapL = 0;
            int tpmapR = 0;
            int tpmapU = 0;
            int tpmapD = 0;
            switch (level) {
            case 1:
                tpmap = map1[i][j];
                if(j - 1 >= 0)
                {
                    tpmapL = map1[i][j - 1];
                }
                if(j + 1 < this->myMapArr[0].size())
                {
                    tpmapR = map1[i][j + 1];
                }
                if(i - 1 >= 0)
                {
                    tpmapU = map1[i - 1][j];
                }
                if(j + 1 < this->myMapArr.size())
                {
                    tpmapD = map1[i + 1][j];
                }
                break;
            case 2:
                tpmap = map2[i][j];
                if(j - 1 >= 0)
                {
                    tpmapL = map1[i][j - 1];
                }
                if(j + 1 < this->myMapArr[0].size())
                {
                    tpmapR = map1[i][j + 1];
                }
                if(i - 1 >= 0)
                {
                    tpmapU = map1[i - 1][j];
                }
                if(j + 1 < this->myMapArr.size())
                {
                    tpmapD = map1[i + 1][j];
                }
                break;
            case 3:
                tpmap = map3[i][j];
                if(j - 1 >= 0)
                {
                    tpmapL = map1[i][j - 1];
                }
                if(j + 1 < this->myMapArr[0].size())
                {
                    tpmapR = map1[i][j + 1];
                }
                if(i - 1 >= 0)
                {
                    tpmapU = map1[i - 1][j];
                }
                if(j + 1 < this->myMapArr.size())
                {
                    tpmapD = map1[i + 1][j];
                }
                break;
            default:
                break;
            }

           myMapArr[i][j] = tpmap;
           if(tpmap == 0 && (tpmapL == 2 || tpmapR == 2 || tpmapU == 2 || tpmapD == 2) && (index++ % 2 == 0) && (i != 0))
           {
               towerBase *tptb = new towerBase(i,j,this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY());
               //tptb->setParent(this);
               //tptb->setFixedSize(60,60);
               tptb->move(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY());
               towerbases.push_back(tptb);
           }
           if(tpmap == 342)
           {
               this->eB = new enemyBase(i,j);      //记录敌方基地地址
           }
           if(tpmap == 2)
           {
               Fence *tf = new Fence;
               tf->updateX(i);
               tf->updateY(j);
               tf->updateSx(this->mapImagePos[i][j]->getX());
               tf->updateSy(this->mapImagePos[i][j]->getY());
               this->fence.push_back(tf);
           }
           if(tpmap == 1)
           {
               this->visit[i][j] = true;
           }
           if(tpmap == 520)
           {
               this->mb = new myBase(i,j);
           }
        }
    }

     this->mapArrImagePath.insert(0,":/image/blank.png");         //配套键值和图片地址  0: 空地；520: 我方基地； 342: 敌方基地； 1: 路径  2:栅栏
     this->mapArrImagePath.insert(520,":/image/base.png");
     this->mapArrImagePath.insert(342,":/image/enemyBase.png");
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
        if(enemy->updateNowHealthValue(-soldiers->getAggressivity()) > 0)
        {
            qDebug() << "敌人收到攻击！！"<< " 剩余生命值："<<enemy->getHealvalue();
        }else{
            qDebug() << "敌人死亡！";
            this->visit[enemy->getX()][enemy->getY()] = true;
            enemy->updateLiveState(false);
        }

        if(soldiers->updateNowHealthValue(-enemy->getAggressivity()))
        {
             qDebug() << "我方单位收到攻击！！"<< " 剩余生命值："<<soldiers->getHealvalue();
        }else{
            qDebug() << "我方战士牺牲！";
            this->visit[soldiers->getX()][soldiers->getY()] = true;
            soldiers->updateLiveState(false);
        }
    }
}

void GameWindow::attackEnemy()
{
    for(int i = 0; i < this->myTower.size(); i++)
    {
        for(int j = 0; j < this->enemy.size(); j++)
        {
            if(enemy[j]->getLiveState() && myTower[i]->checkAttackRange(enemy[j]->getMapPosX(),enemy[i]->getMapPosY()))
            {
                myTower[i]->attackEventPos[0] = myTower[i]->getMapX();
                myTower[i]->attackEventPos[1] = myTower[i]->getMapY();
                myTower[i]->attackEventPos[2] = enemy[j]->getMapPosX();
                myTower[i]->attackEventPos[3] = enemy[j]->getMapPosY();

                if(enemy[j]->updateNowHealthValue(-myTower[i]->getAggressivity()) > 0)
                {
                    qDebug() << "敌人收到防御塔"<<i<<"攻击！！"<< " 剩余生命值："<<enemy[j]->getHealvalue();
                }else{
                    qDebug() << "敌人死亡！";
                    this->visit[enemy[j]->getX()][enemy[j]->getY()] = true;
                    enemy[j]->updateLiveState(false);
                }
                update();
            }
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
