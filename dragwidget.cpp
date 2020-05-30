#include "dragwidget.h"
#include "ui_dragwidget.h"
#include<QDebug>
#include<QDropEvent>
#include<QMimeData>
dragWidget::dragWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::dragWidget)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);//设置控件接受抛投文件

}
void dragWidget::dragEnterEvent(QDragEnterEvent *event)
{

    if (event->mimeData()->hasFormat("text/uri-list")) {
           event->acceptProposedAction();
       }
}

void dragWidget::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
    {
        qDebug()<<"Can't recevie any information";
        return;
    }
    else
    {
      emit getURLS(urls);//将URLS发射出去
    }
}

dragWidget::~dragWidget()
{
    delete ui;
}
