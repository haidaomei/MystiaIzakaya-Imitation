#ifndef INGREDIENT_H
#define INGREDIENT_H
#include<vector>
#include<string>
#include<QPixmap>
using namespace std;
class Ingredient
{
public:
    Ingredient(string Name,vector<string> Tags);//想了一下属性什么的还是不会在ingredient这里赋进去的,应该在对应的widget赋才对,这里就提供模板
    virtual ~Ingredient()=default;
    virtual void Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected=false)const=0;
    vector<string> GetTags()const;//这里就不virtual了,毕竟tag在料理和酒水不冲突,到时候直接对角色直接合进去
    string GetName()const;//因为这些是共有属性,所以不用virtual了
    QPixmap GetIcon()const;
    void SetIcon(string Filename);
private://一个物品需要有名字 需要有图标 需要有tags(食材可以无)
    string Name;
    QPixmap Icon;
    vector<string> Tags;
};
class RawMaterial:public Ingredient//这个用来显示和选中足矣
{
public:
    RawMaterial(string Name);
    virtual void Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected)const override;
};
class Dish:public Ingredient
{
public:
    Dish(string Name,vector<string> Tags,vector<RawMaterial> Element,string Tool);
    string GetTool()const;
    vector<RawMaterial> GetElement()const;
    virtual void Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected)const override;
private:
    vector<RawMaterial> Element;//所需食材
    string Tool;//烹饪工具,到时候打开某种cook显示对应的tool就行
};
class Drink:public Ingredient
{
public:
    Drink(string Name,vector<string> Tags);
    virtual void Render(QPainter* painter,int x,int y,int Width,int Height,bool Selected)const override;//这里不能二次添加参数,不然会报错
};
#endif//INGREDIENT_H
