#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QMainWindow>
#include"mainwidget.h"
#include"drinkwidget.h"
class MainWindow:public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent=0);
    ~MainWindow();
private:
    MainWidget* MainScene;
    DrinkWidget* DrinkScene;
};
#endif // MAINWINDOW_H
