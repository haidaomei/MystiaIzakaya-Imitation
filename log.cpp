#include"log.h"
#include<QPlainTextEdit>
#include<QApplication>
QPlainTextEdit* logWidget=nullptr;
void addLog(QString message)
{
    foreach(QWidget* topWidget,QApplication::topLevelWidgets())//查找主窗口中的日志控件
    {
        logWidget=topWidget->findChild<QPlainTextEdit*>("logWidget");
        if(logWidget)
        {
           break;
        }
    }
    logWidget->appendPlainText(message);//往日志控件输入信息
    QTextCursor cursor=logWidget->textCursor();//滚动
    cursor.movePosition(QTextCursor::End);
    logWidget->setTextCursor(cursor);
}
