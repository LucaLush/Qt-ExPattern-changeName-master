#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"dragwidget.h"
#include"autornamecollection.h"
#include<QDir>
#include<QDebug>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<QTableView>
#include<QFileDialog>
#include<QAction>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    pANC(new autorNameCollection(this)),//数据库初始化必须先于tablemodel的初始化，否则model会读不出database的数据
    model(new CustomModel(this)),//改用客制化的
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //新建一个拖拽控件，将之绑定到主窗口中
    dragWidget * d = new dragWidget();//tab 控件1 拖拽部件
    tableView = new QTableView();//tab 控件2 tableview表显示控件

    model->setTable("autors");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);//由右键按钮去上存改变

    model->select();//refresh the table view

    tableView->setModel(model);
    tableView->setContextMenuPolicy(Qt::ContextMenuPolicy::ActionsContextMenu);//选用右键QAction菜单
    submitAllAction = new QAction(tr("submit all"),this);
    revertAction = new QAction(tr("revert"),this);
    tableView->addAction(submitAllAction);
    tableView->addAction(revertAction);


    ui->tabWidget->clear();//将初始页面先删除
    ui->tabWidget->insertTab(0,d,tr("drop path"));//将拖拽控件绑定到0号界面
    ui->tabWidget->insertTab(1,tableView,tr("SQL Table"));//将tableview控件绑定到1号界面

    //信号绑定
    connect(d,&dragWidget::getURLS,this,&MainWindow::on_IsHasThisAutor);
    //将路径获取控件添加到主窗口中
    connect(ui->actionAdd_Dir,&QAction::triggered,this,&MainWindow::on_OpenFileDialog);
    //右键菜单信号绑定
    connect(submitAllAction,&QAction::triggered,this,&MainWindow::on_SubmitAllStrategy);
    connect(revertAction,&QAction::triggered,this,&MainWindow::on_RevertStrategy);

}

MainWindow::~MainWindow()
{
    delete ui;
}



QString MainWindow::getUrlRexString(const QUrl& url)//获取[*]中*的内容
{
    //设定中括号内容匹配模式
    QRegularExpression pattern("\\[(?<fileName>.*)\\]");
    //设定最小匹配模式
    pattern.setPatternOptions(QRegularExpression::InvertedGreedinessOption);
    QRegularExpressionMatch match = pattern.match(url.fileName());
    if(match.hasMatch())
    {
        //指定分组的方法获取匹配字段的特定部分;
        QString fileAutorName = match.captured("fileName").trimmed();
        qDebug()<<"Has matched:"<<fileAutorName;
        return fileAutorName;
    }
    else
        return "";

}

void MainWindow::on_IsHasThisAutor(const QList<QUrl>& urls)//确定数据库中是否有这个作者存在
{
    qDebug()<<"Message:"<<QString::number(urls.length());

    ui->statusBar->showMessage(("finish state: %1 / "+QString::number(urls.length())).arg(0));


    int i=0;
    foreach(QUrl var,urls)
    {
       QString fileAutorName = getUrlRexString(var);
       QStringList AutorNames = pANC->getUrls(fileAutorName);//以从文件名提取的作者
       if(AutorNames.length()!=0)
       {
            QString targetPath = AutorNames.first()+'/'+var.fileName();//暂时不考虑一个作者多个路径
            QDir d;
            if(d.rename(var.toLocalFile(),targetPath))
            {
                i+=1;
                ui->statusBar->showMessage(("finish state: %1 / "+QString::number(urls.length())).arg(i));
            }
            else {
                qDebug()<<var.fileName()<<" fail to change path!";
            }
       }
       else {
           qDebug()<<var.fileName()<<" can't find the path in database!";
       }
    }


}

void MainWindow::on_OpenFileDialog()
{

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::Directory);
    dialog.setDirectory(QDir::homePath());

    QStringList fileNames;
    if (dialog.exec())
        fileNames = dialog.selectedFiles();//get the absolute path of the directory
    //if get a directory that do something
    if(fileNames.length()!=0)//以Qt的机制，文件对话框只能得到一个文件夹
    {
        QDir dir(fileNames.first());//In this file mode we can only get one path
        QStringList pathList = dir.entryList(QDir::AllDirs|QDir::NoDotAndDotDot|QDir::Hidden);

        foreach (QString var, pathList)//var是文件夹里面的文件名字，所以要加上一段字符凑成完整绝对路径
        {
            QString tempPath = fileNames.first()+"/"+var;//迭代得到拼接好的文件夹地址
            QString tempAutorName=getUrlRexString(var);

            if(tempAutorName=="")
            {
                tempAutorName = "Jane Doe";
            }
            pANC->addAutor(tempAutorName,tempPath);
        }
    }
    model->select();//刷新数据库视图
}

void MainWindow::on_SubmitAllStrategy()
{
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(tableView->model());
    if (tm)
        tm->submitAll(); //手动上存改变的模式需要用到这个
}

void MainWindow::on_RevertStrategy()
{
    QSqlTableModel * tm = qobject_cast<QSqlTableModel *>(tableView->model());
    if (tm)
        tm->revertAll();

}
