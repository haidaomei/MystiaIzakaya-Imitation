#include"character.h"
#include"mainwidget.h"
#include<Qt>
#include<utility>
#include<QPixmap>
#include<QPainter>
#include<QDebug>
#include<QtGlobal>
#include<QTime>
#include"log.h"
#include<thread>
int scores=0;//全局分数
Character::Character()
{
}
Player::Player()
{
    LastPlayerRect=QRect(Position.first*40,Position.second*40,40,40);
    Mystia.load("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/Mystia.png");
    Mystia=Mystia.scaled(40,40);//这里不能单单写成Mystia.scaled(40,40),否则对象没被改变,我看这scaled也不是引用参数,是直接复制参数执行结束就销毁的函数啊
}
void Player::Update()//玩家的位置用pair存储分别代表x和y,接收W则y减1,接收S则y加1,接收A则x减一,接收D则x加1
{
    OldPlayerRect=LastPlayerRect;
    int dx=0;
    int dy=0;
    if(InputKey.up)
    {
        dy=dy-1;
    }
    if(InputKey.down)
    {
        dy=dy+1;
    }
    if(InputKey.left)
    {
        dx=dx-1;
    }
    if(InputKey.right)
    {
        dx=dx+1;
    }
    if(dx==0&&dy==0)
    {
        return;
    }
    int x=Position.first+dx;
    int y=Position.second+dy;
    if(x<0||x>=20||y<0||y>=10)
    {
        return;
    }
    int GridValue=MainWidget::GetGrid()[y][x];
    if(GridValue>=1&&GridValue<=4)
    {
        Position={x,y};
        LastPlayerRect=QRect(x*40,y*40,40,40);
    }
    else
    {
        QRect Rect(x*40,y*40,40,40);
        CollisionPlayerRect=Rect;//能不能不加这段?这表示给碰撞区域赋值
    }
}
void Player::Render(QPainter* painter)
{
    pair<int,int> Position=GetPosition();
    painter->drawPixmap(Position.first*40,Position.second*40,Mystia);
}
void Player::Interact(Drink* drink)
{

}
void Player::Input(int key,bool pressed)
{
    switch(key)
    {
        case Qt::Key_W:
            InputKey.up=pressed;
            break;
        case Qt::Key_S:
            InputKey.down=pressed;
            break;
        case Qt::Key_A:
            InputKey.left=pressed;
            break;
        case Qt::Key_D:
            InputKey.right=pressed;
            break;
    }
}
pair<int,int> Player::GetPosition()const
{
    return Position;
}
QPixmap Player::GetPixmap()const
{
    return Mystia;
}
QRect Player::GetOldPlayerRect()const
{
    return OldPlayerRect;
}
QRect Player::GetLastPlayerRect()const
{
    return LastPlayerRect;
}
QRect Player::GetCollisionRect()const
{
    return CollisionPlayerRect;
}
void Player::ResetCollisionRect()
{
    CollisionPlayerRect=QRect();
}
Customer::Customer(int Row,int Column,string Name,vector<string> Preferences,QString Filename):Row(Row),Column(Column),Name(Name),Preferences(Preferences)
{
    timer=5000;//初始思考时间5秒
    Girl.load(Filename);
}
void Customer::Update()
{
    if(state==0)//thinking
    {
        timer=timer-16;//分析写在纸上 这timer不是QTimer 但是和mainwidget的timer->start(16)有着极大关联
        if(timer<=0)
        {
            qsrand(static_cast<uint>(QTime::currentTime().msec()));//随机选择偏好,这里的qt随机数格式我抄网上的
            int index=qrand()%static_cast<int>(Preferences.size());
            CurrentRequest=Preferences[index];
            addLog(QString::fromStdString(Name)+"想要"+QString::fromStdString(CurrentRequest)+"的酒水~");
            timer=15000;//等待时间十五秒
        }
    }
    else
    {
        timer=timer-16;
        if(timer<0)
        {
            state=0;
            timer=5000;//回到思考状态
        }
    }
}
void Customer::Render(QPainter* painter)
{
    Girl=Girl.scaled(40,40);
    painter->drawPixmap(this->GetRow()*40,(this->GetColumn()+1)*40,Girl);
}
void Customer::Interact(Drink* drink)
{
    if(!drink)
    {
        return;//表示如果没有饮料就不交互
    }
    bool match=false;//检查酒水标签是否匹配
    for(auto tag:drink->GetTags())
    {
        if(tag==CurrentRequest)
        {
            match=true;
            break;
        }
    }
    if(match)
    {
        scores++;
        addLog(QString::fromStdString(Name)+"满意ヾ(≧▽≦*)o 总分"+QString::number(scores)+"~");
        if(scores==10)
        {
            addLog("游戏结束~总分为10~");
            this_thread::sleep_for(chrono::seconds(5));//这段我写宏的时候会用,这里干脆直接用,其实就是睡眠
            exit(0);
        }
    }
    else
    {
        scores--;
        addLog(QString::fromStdString(Name)+"不满意(～﹃～)~zZ 总分"+QString::number(scores)+"~");
        if(scores==-10)
        {
            addLog("游戏失败~总分为-10~");
            this_thread::sleep_for(chrono::seconds(5));
            exit(0);
        }
    }
    state=1;//开吃
    timer=10000;//10秒享用时间,计算公式我写在纸上
    CurrentRequest.clear();
}
int Customer::GetRow()const
{
    return Row;
}
int Customer::GetColumn()const
{
    return Column;
}
string Customer::GetCurrentRequest()const
{
    return CurrentRequest;
}
