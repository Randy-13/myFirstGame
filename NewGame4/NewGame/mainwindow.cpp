#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "gamewindow.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/GunTruck.jpeg")); //设置图标
    setWindowTitle("Welcome!!!");//命名主窗口

    connect(ui->btn1,&QPushButton::clicked,[=](){ //链接第一个按钮
        GameWindow *gamewindow = new GameWindow(1);
        //this->hide();
        gamewindow->show();
    });

    connect(ui->btn2,&QPushButton::clicked,[=](){ //链接第二个按钮
        GameWindow *gamewindow = new GameWindow(2);
        // this->hide();
        gamewindow->show();
    });

    connect(ui->btn3,&QPushButton::clicked,[=](){ //链接第三个按钮
        GameWindow *gamewindow = new GameWindow(3);
         //this->hide();
        gamewindow->show();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

