#include"ingredient.h"
#include<string>
#include<vector>
#include<QFont>
#include<QPainter>
using namespace std;
Ingredient::Ingredient(string Name,vector<string> Tags):Name(Name),Tags(Tags)
{
}
string Ingredient::GetName()const
{
    return Name;
}
QPixmap Ingredient::GetIcon()const
{
    return Icon;
}
vector<string> Ingredient::GetTags()const
{
    return Tags;
}
void Ingredient::SetIcon(string Filename)
{
    QString QFilename=QString::fromStdString(Filename);
    Icon.load(QFilename);
}
RawMaterial::RawMaterial(string Name):Ingredient(Name,{})
{
}
void RawMaterial::Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected=false)const
{
}
Dish::Dish(string Name,vector<string> Tags,vector<RawMaterial> Element,string Tool):Ingredient(Name,Tags),Element(Element),Tool(Tool)
{
}
void Dish::Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected=false)const
{
}
Drink::Drink(string Name,vector<string> Tags):Ingredient(Name,Tags)
{
}
void Drink::Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected=false)const
{
    if(!painter)
    {
        return;
    }
    QRect ItemRect(x,y,Width,Height);
    if(Selected)
    {
        painter->fillRect(ItemRect,QColor(200,230,255));//选中项背景色
        painter->setPen(QPen(Qt::blue,2));
    }
    else
    {
        painter->setPen(QPen(Qt::black,1));
    }
    if(!GetIcon().isNull())//绘制酒水图标
    {
        QPixmap icon=GetIcon();
        painter->drawPixmap(ItemRect.left()+5,ItemRect.top()+(Height-37.5)/2,icon);
    }
    painter->drawText(ItemRect.adjusted(50,-15,-30,0),Qt::AlignLeft|Qt::AlignVCenter,QString::fromStdString(GetName()));//绘制酒水名称
    QString TagsText;//绘制标签(就是文化底蕴那个)
    for(string Tag:GetTags())
    {
        TagsText+=QString::fromStdString(Tag)+" ";
    }
    painter->drawText(ItemRect.adjusted(50,20,-30,0),Qt::AlignLeft|Qt::AlignVCenter,TagsText);
    if(Selected)
    {
        painter->drawText(ItemRect.right()-25,ItemRect.center().y(),"←");
    }
}
