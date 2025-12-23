#ifndef MAINWIDGET_H
#define MAINWIDGET_H
#include<QWidget>
#include<vector>
#include<QPlainTextEdit>
#include"character.h"
#include"ingredient.h"
#include<QPlainTextEdit>
using namespace std;
class MainWidget:public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget* parent=0);
    static vector<vector<int>> GetGrid();
signals:
public slots:
    void AddDrink(Drink* drink);//添加酒水方法
protected:
    void keyPressEvent(QKeyEvent* event)override;
    void keyReleaseEvent(QKeyEvent* event)override;
    void paintEvent(QPaintEvent* event)override;
private:
    static vector<vector<int>>grid;//这个用来装判定还差不多,玩家的位置还是单独来吧
    Player player;
    Drink* CurrentDrink=nullptr;
    vector<Customer> customers;
    QPixmap Table;
    QPixmap Chair;
    QPixmap Bar;
    QPixmap Cooker;
    QPlainTextEdit* logWidget;//日志显示控件
};
#endif//MAINWIDGET_H
