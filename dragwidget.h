#ifndef DRAGWIDGET_H
#define DRAGWIDGET_H

#include <QWidget>
#include<QString>
#include<QUrl>
namespace Ui {
class dragWidget;
}
//该类主要以控件获取拖拽文件的URL地址，然后发送出去
class dragWidget : public QWidget
{
    Q_OBJECT

public:
    explicit dragWidget(QWidget *parent = 0);
    ~dragWidget();

signals:
    void getURLS(const QList<QUrl>&);//拖拽完成后将获得的地址以信号的方式传递出去
protected:

    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
private:
    Ui::dragWidget *ui;
};

#endif // DRAGWIDGET_H
