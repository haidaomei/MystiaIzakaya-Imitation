#ifndef CHARACTER_H
#define CHARACTER_H
#include<vector>
#include<utility>
#include<QPixmap>
#include<QRect>
#include"ingredient.h"
using namespace std;
class Character
{
public:
    Character();
    virtual ~Character()=default;
    virtual void Update()=0;
    virtual void Render(QPainter* painter)=0;
    virtual void Interact(Drink* drink)=0;
};
class Player:public Character
{
public:
    Player();
    virtual ~Player()=default;
    virtual void Update()override;
    virtual void Render(QPainter* painter)override;
    virtual void Interact(Drink* drink)override;
    void Input(int key,bool pressed);
    pair<int,int> GetPosition()const;
    QPixmap GetPixmap()const;
    QRect GetOldPlayerRect()const;
    QRect GetLastPlayerRect()const;
    QRect GetCollisionRect()const;
    void ResetCollisionRect();
private:
    pair<int,int> Position=pair<int,int>(10,2);//注意这里以0为起始,直接把player在类中初始化好了,后面不再在mainwidget用构造函数赋值,这点和customer设计有点不一样
    struct InputStatement
    {
        bool up=false;
        bool down=false;
        bool left=false;
        bool right=false;
    }InputKey;
    QPixmap Mystia;
    QRect OldPlayerRect;
    QRect LastPlayerRect;
    QRect CollisionPlayerRect;
};
class Customer:public Character
{
public:
    Customer(int Row,int Column,string Name,vector<string> Preferences,QString Filename);
    virtual ~Customer()=default;
    virtual void Update()override;
    virtual void Render(QPainter* painter)override;
    virtual void Interact(Drink* drink)override;
    int GetRow()const;
    int GetColumn()const;
    string GetCurrentRequest()const;
private:
    QPixmap Girl;
    int Row,Column;
    string Name;
    vector<string> Preferences;
    string CurrentRequest;
    int timer=0;
    int state=0;
};
#endif // CHARACTER_H
