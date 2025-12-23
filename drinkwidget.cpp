#include"drinkwidget.h"
#include<list>
#include<QPainter>
#include<QKeyEvent>
#include"ingredient.h"
DrinkWidget::DrinkWidget(QWidget* parent):QWidget(parent)
{
    setFixedSize(800,400);
    setFocusPolicy(Qt::StrongFocus);
    DrinkList.push_back(new Drink("玉露茶",{"无酒精","可加热","古典"}));
    DrinkList.push_back(new Drink("梅酒",{"中酒精","可加冰","可加热","利口酒","水果"}));
    DrinkList.push_back(new Drink("冬酿",{"低酒精","可加冰","可加热","甘","古典"}));
    DrinkList.push_back(new Drink("果味SOUR",{"低酒精","可加冰","烧酒","鸡尾酒","水果","甘","苦"}));
    DrinkList.push_back(new Drink("大冰棍儿!",{"无酒精","甘","现代","提神"}));
    DrinkList[0]->SetIcon("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/玉露茶.png");
    DrinkList[1]->SetIcon("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/梅酒.png");
    DrinkList[2]->SetIcon("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/冬酿.png");
    DrinkList[3]->SetIcon("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/果味SOUR.png");
    DrinkList[4]->SetIcon("C:/Users/DDdao/Desktop/MystiaIzakaya/MystiaIzakaya/Assets/大冰棍儿!.png");
}
void DrinkWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setFont(QFont("Arial",12.5));
    painter.drawText(rect().adjusted(10,10,-10,-10),Qt::AlignTop,"酒水菜单");//绘制标题,adjusted是调整上下左右位置的
    for(int i=0;i<DrinkList.size();i++)
    {
        int Temp=50+i*ItemHeight;
        DrinkList[i]->Render(&painter,10,Temp,ItemWidth,ItemHeight-5,(i==CurrentIndex));
    }//调用Render绘制酒水列表
}
void DrinkWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_W:
        if(CurrentIndex>0)
        {
            CurrentIndex--;
            update();
        }
        break;
    case Qt::Key_S:
        if(CurrentIndex<DrinkList.size()-1)
        {
            CurrentIndex++;
            update();
        }
        break;
    case Qt::Key_Return:
        if(CurrentIndex>=0&&CurrentIndex<DrinkList.size())
        {
            emit DrinkSelected(DrinkList[CurrentIndex]);
            this->close();
        }
        break;
    }
    QWidget::keyPressEvent(event);
}
