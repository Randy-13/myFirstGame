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
    this->mapType = 4;                    //地图块类型
    this->initMapImagePosArr();           //初始化地图块放置位置
    this->creatMap();                     //创建地图
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
    QTimer * timer = new QTimer(this);
    timer->start(50);
    static int times = 0;
    connect(timer,&QTimer::timeout,[=](){
        if(times % 150 == 0)
        {
            this->generateEnemy();
            this->EnemyMoveEvent();
        }
        this->EnemyMapMove();
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

void GameWindow::initMapImagePosArr()
{
    this->mapImagePos.resize(4);
    for(int i = 0; i < mapImagePos.size();i++)
    {
        this->mapImagePos[i].resize(6);
    }
    int tx = 0; int ty = 0;
    for(int i = 0; i < mapImagePos.size(); i++)
    {
        for(int j = 0; j < mapImagePos[0].size(); j++)
        {
             mapImagePos[i][j] = new SubMap;
             mapImagePos[i][j]->updateXY(tx,ty);
             if(tx < 750)
             {
                 tx += 150;
             }else{
                 tx = 0;
             }
        }
        ty += 150;
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
    Enemy * tpE = new Enemy(x,y,mapX,mapY);
    this->enemy.push_back(tpE);
}

void GameWindow::drawMap(QPainter &p)
{
    for(int i = 0; i < myMapArr.size(); i++)
    {
        for(int j = 0; j < myMapArr[0].size(); j++)
        {
            switch (myMapArr[i][j]) {
            case 0:
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),150,150);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(0).value(),Stretch);
                break;
            }
            case 1:
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),150,150);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(1).value(),Stretch);
                break;
            }
            case 2:
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),150,150);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(2).value(),Stretch);
                break;
            }
            case 3:
            {
                QRectF Parameter(this->mapImagePos[i][j]->getX(),this->mapImagePos[i][j]->getY(),150,150);
                QRectF Stretch(0,0,0,0);
                p.drawPixmap(Parameter,this->mapArrImagePath.find(3).value(),Stretch);
                break;
            }
            default:
                break;
            }
        }
    }
}

void GameWindow::drawEnemy(QPainter &p)   //画敌人
{
    for(int i = 0; i < this->enemy.size(); i++)
    {
        if(enemy[i]->getLiveState() == true)
        {
            QRectF Parameter(this->enemy[i]->getMapPosX(),this->enemy[i]->getMapPosY()+30,80,80);
            QRectF Stretch(0,0,0,0);
            p.drawPixmap(Parameter,QPixmap(":/image/GunTruck2.png"),Stretch);
        }
    }
}


void GameWindow::paintEvent(QPaintEvent *pe)
{
    static int times = 1;
    qDebug() << "多次调用" << times++;
    QPainter painter(this);
    drawMap(painter);
    //画敌人
    drawEnemy(painter);

}

bool GameWindow::creatMap()
{
    int map[4][6] = {{0,0,0,0,0,0},{1,3,3,3,3,2},{0,0,0,0,0,0},{0,0,0,0,0,0}};                    // 0: 空地；1: 我方基地；2: 敌方基地； 3: 路径
    this->myMapArr.resize(4);
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        this->myMapArr[i].resize(6);
    }
    for(int i = 0; i < this->myMapArr.size(); i++)
    {
        for(int j = 0; j < this->myMapArr[0].size(); j++)
        {
           myMapArr[i][j] = map[i][j];
           if(map[i][j] == 2)
           {
               this->eB = new enemyBase(i,j);
           }
        }
    }
    for(int i = 0; i < this->mapType; i++)        //配套键值和图片地址  0: 空地；1: 我方基地；2: 敌方基地； 3: 路径
    {
        switch (i) {
        case 0:
            this->mapArrImagePath.insert(0,":/image/blank.png");
            break;
        case 1:
            this->mapArrImagePath.insert(1,":/image/base.png");
            break;
        case 2:
            this->mapArrImagePath.insert(2,":/image/base.png");
            break;
        case 3:
            this->mapArrImagePath.insert(3,":/image/horizontal2.png");
            break;
        default:
            break;
        }
    }
    return true;
}

void GameWindow::timerEvent(QTimerEvent *event)
{


}


bool GameWindow::event(QEvent *e)  //调配event事件
{
    return QWidget::event(e);
}

bool GameWindow::EnemyMoveEvent()
{
    //敌人移动
    bool check = false;
    for(int k = 0; k < this->enemy.size(); k++)
    {
        for(int i = 0; i < 4; i++)
        {
            int tx = this->enemy[k]->getX() + mx[i];
            int ty = this->enemy[k]->getY() + my[i];
            if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 3 && this->enemy[k]->getLiveState())
            {
                enemy[k]->updateX(tx);
                enemy[k]->updateY(ty);
                qDebug() << " 成功移动！";
                switch (i) {              //左下右上
                case 0:
                    this->enemy[k]->updateMoveDirection('L');
                    break;
                case 1:
                    this->enemy[k]->updateMoveDirection('D');
                    break;
                case 2:
                    this->enemy[k]->updateMoveDirection('R');
                    break;
                case 3:
                    this->enemy[k]->updateMoveDirection('U');
                    break;
                default:
                    break;
                }
                check = true;
                break;
            }else if(tx >= 0 && tx < this->myMapArr.size() && ty >= 0 && ty < this->myMapArr[0].size() && this->myMapArr[tx][ty] == 1 && this->enemy[k]->getLiveState())
            {
                check = false;
                this->enemy[k]->updateLiveState(false);
                break;
            }
        }
    }
    return check;
}

void GameWindow::EnemyMapMove()
{
    for(int k = 0; k < this->enemy.size(); k++)
    {
        if(this->enemy[k]->getLiveState())
        {
            if(this->enemy[k]->getMoveDirection() == 'D')
            {
                this->enemy[k]->MapPosDownMove();
            }else if(this->enemy[k]->getMoveDirection() == 'L')
            {
                this->enemy[k]->MapPosLeftMove();
            }else if(this->enemy[k]->getMoveDirection() == 'R')
            {
                this->enemy[k]->MapPosRightMove();
            }else if(this->enemy[k]->getMoveDirection() == 'U')
            {
                this->enemy[k]->MapPosUpMove();
            }
        }
    }
}

GameWindow::~GameWindow()
{

}
