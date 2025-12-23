#include"mainwidget.h"
#include<QKeyEvent>
#include<QPainter>
#include<QDebug>
#include"drinkwidget.h"
#include<QTimer>
#include<vector>
#include<QApplication>
#include"log.h"
using namespace std;
extern QString logMessages;
vector<vector<int>> MainWidget::grid=
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,5,1},
    {1,6,7,6,1,6,7,6,1,1,1,1,1,3,3,3,3,3,4,1},
    {1,1,2,1,1,1,2,1,1,1,1,1,1,8,8,8,8,8,1,1},
    {1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,6,7,6,1,6,7,6,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,2,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
MainWidget::MainWidget(QWidget* parent):QWidget(parent)
{
    setFixedSize(800,500);
    setFocusPolicy(Qt::StrongFocus);//没有这玩意不行的,久经尝试发现了
    Customer temp1(1,1,"Aya",vector<string>{"可加冰","高酒精","烧酒","提神"},"C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Aya.png");
    Customer temp2(1,4,"Yuyuko",vector<string>{"高酒精","可加冰","鸡尾酒"},"C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Yuyuko.png");
    Customer temp3(5,1,"Marisa",vector<string>{"可加冰","低酒精"},"C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Marisa.png");
    Customer temp4(7,4,"Cirno",vector<string>{"水果","可加冰","甘"},"C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Cirno.png");
    customers.push_back(temp1);
    customers.push_back(temp2);
    customers.push_back(temp3);
    customers.push_back(temp4);//添加人物
    Table.load("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Table.png");
    Chair.load("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Chair.png");
    Bar.load("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Bar.png");
    Cooker.load("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Cooker.png");
    Table=Table.scaled(40,40);
    Chair=Chair.scaled(40,40);
    Bar=Bar.scaled(40,80);
    Cooker=Cooker.scaled(40,40);
    QTimer* timer=new QTimer(this);
    connect(timer,&QTimer::timeout,[this]()//这里一定要引用一定要引用一定要引用!!!!!
    {
        for(Customer &customer:customers)//lambda表达式,这里表示如果timeout就重新重绘
        {
            customer.Update();//这个update不是画面,是顾客状态,这里相当于每次timeout都更新一次顾客状态和画面
        }
        update();//这个是附带的方法,这里就相当于更新画图和更新人物情况了
    });
    timer->start(16);//60FPS,之前讨论过qt没有具体的delta,画面刷新由timer手动控制,人物速度也不好乘以delta在帧不同情况下归一化(游戏引擎里)
    logWidget=new QPlainTextEdit(this);
    logWidget->setGeometry(0,400,800,100);//设置区域用的
    logWidget->setObjectName("logWidget");
}//这里就是设置16秒触发一次timeout,然后连接update信号,后面人物吃东西也不是根据确实的时间来计算的而是根据绘制多少张画计算的
void MainWidget::keyPressEvent(QKeyEvent* event)
{
    player.Input(event->key(),true);
    player.Update();
    if(event->key()==Qt::Key_Return)
    {
        pair<int,int> Position=player.GetPosition();
        int x=Position.first;
        int y=Position.second;
        if(x==2&&y==1)
        {
            Customer* target=&customers[0];
            if(target&&CurrentDrink)//这里就是交互了
            {
                target->Interact(CurrentDrink);
                delete CurrentDrink;
                CurrentDrink=nullptr;
            }
        }
        else if(x==6&&y==1)
        {
            Customer* target=&customers[2];
            if(target&&CurrentDrink)
            {
                target->Interact(CurrentDrink);
                delete CurrentDrink;
                CurrentDrink=nullptr;
            }
        }
        else if(x==2&&y==4)
        {
            Customer* target=&customers[1];
            if(target&&CurrentDrink)
            {
                target->Interact(CurrentDrink);
                delete CurrentDrink;
                CurrentDrink=nullptr;
            }
        }
        else if(x==6&&y==4)
        {
            Customer* target=&customers[3];
            if(target&&CurrentDrink)
            {
                target->Interact(CurrentDrink);
                delete CurrentDrink;
                CurrentDrink=nullptr;
            }
        }
    }
    if(event->key()==Qt::Key_Return)//好像有点赘余,小问题
    {
        pair<int,int> Position=player.GetPosition();
        if(grid[Position.second][Position.first]==4)//碰到4的地方就可以开界面d
        {
            DrinkWidget* DrinkScene=new DrinkWidget();
            connect(DrinkScene,&DrinkWidget::DrinkSelected,this,&MainWidget::AddDrink);
            DrinkScene->show();
        }
    }
    //
    QRect CollisionRect=player.GetCollisionRect();
    if(!CollisionRect.isNull())//如果有碰撞发生,更新该区域
    {
        update(CollisionRect);
        player.ResetCollisionRect();//重置碰撞标记
    }
    update(player.GetOldPlayerRect());//重绘上一次的
    update(player.GetLastPlayerRect());//重绘这次的,一般update是没有参数的重绘全部区域,这是重绘指定区域,叫脏区域重绘(分现在上次两个),可以有效节省资源占用,再者如果把每一次的输出当做一个流的话每次都得输出一遍其他元素,这个流怎么整合都是个问题
}//分析player相关逻辑能不能存在,由于player必须在mainwidget类中存在,所以首先关于画图的不能移动,那就指明了update不可移动,现在只能想办法把位置矩形移到player里了
void MainWidget::keyReleaseEvent(QKeyEvent* event)
{
    player.Input(event->key(),false);
}
vector<vector<int>> MainWidget::GetGrid()
{
    return grid;
}
void MainWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    player.Render(&painter);
    for(Customer customer:customers)
    {
        customer.Render(&painter);
    }
    painter.drawPixmap(2*40,2*40,Table);
    painter.drawPixmap(6*40,2*40,Table);
    painter.drawPixmap(2*40,5*40,Table);
    painter.drawPixmap(6*40,5*40,Table);
    painter.drawPixmap(3*40,2*40,Chair.transformed(QTransform().scale(-1,1)));//这一段代表镜像
    painter.drawPixmap(3*40,5*40,Chair.transformed(QTransform().scale(-1,1)));
    painter.drawPixmap(7*40,2*40,Chair.transformed(QTransform().scale(-1,1)));
    painter.drawPixmap(5*40,5*40,Chair);
    painter.drawPixmap(18*40,0,Bar);
    painter.drawPixmap(17*40,3*40,Cooker);
    painter.drawPixmap(16*40,3*40,Cooker);
    painter.drawPixmap(15*40,3*40,Cooker);
    painter.drawPixmap(14*40,3*40,Cooker);
    painter.drawPixmap(13*40,3*40,Cooker);
}//整个主页面的绘制功能都集中到这里了
void MainWidget::AddDrink(Drink* drink)
{
    CurrentDrink=drink;
    addLog(QString::fromStdString(drink->GetName())+"添加成功(～￣▽￣)～");
}
