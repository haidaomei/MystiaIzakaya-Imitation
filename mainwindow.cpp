#include "mainwindow.h"
MainWindow::MainWindow(QWidget* parent):QMainWindow(parent)
{
    MainScene=new MainWidget(this);
    setCentralWidget(MainScene);
    setWindowTitle("Mystia Izayaka");
    resize(800,500);
}
MainWindow::~MainWindow()
{
}
