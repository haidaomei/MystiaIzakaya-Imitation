#ifndef DRINKWIDGET_H
#define DRINKWIDGET_H
#include<QWidget>
#include<List>
#include"ingredient.h"
using namespace std;
class DrinkWidget:public QWidget
{
    Q_OBJECT
public:
    explicit DrinkWidget(QWidget* parent=0);
    void Render(QPainter* painter);//核心渲染方法
signals:
    void DrinkSelected(Drink* drink);//选中酒水信号
protected:
    void paintEvent(QPaintEvent* event)override;
    void keyPressEvent(QKeyEvent* event)override;
private:
    vector<Drink*> DrinkList;//存储酒水对象的列表
    int CurrentIndex=0;//当前选中的酒水索引
    int ItemHeight=60;//每个酒水项的高度
    int ItemWidth=380;//每个酒水项的宽度
public slots:
};
#endif//DRINKWIDGET_H
