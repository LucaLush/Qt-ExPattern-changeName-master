#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QUrl>
#include<QSqlTableModel>
QT_FORWARD_DECLARE_CLASS(autorNameCollection);//class forward defination
QT_FORWARD_DECLARE_CLASS(QAction);
QT_FORWARD_DECLARE_CLASS(QTableView);
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:
    //确定数据库中是否有这个作者存在，获得名字后就转移路径
    void on_IsHasThisAutor(const QList<QUrl>&);
    //通过fileDialog将文件夹批量加入到数据库中
    void on_OpenFileDialog();//用于打开文件夹选择器

    void on_SubmitAllStrategy();//上存所作的改变
    void on_RevertStrategy();//复位所作的改变




public:
    explicit MainWindow(QWidget *parent = 0);//构造函数
    ~MainWindow();

private:
    QString getUrlRexString(const QUrl&);//获取[*]中*的内容,并输出作者名字

    autorNameCollection *pANC;//用于访问数据库

    QSqlTableModel *model;//用于将数据显示到table view上
    QTableView *tableView;//用于显示数据
     Ui::MainWindow *ui;
    //右键菜单
    QAction *submitAllAction;
    QAction *revertAction;

};

class CustomModel: public QSqlTableModel //重写sqltablemodel实现修改列表后表格颜色变化
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = nullptr, QSqlDatabase db = QSqlDatabase())
        : QSqlTableModel(parent, db) {}

    QVariant data(const QModelIndex &idx, int role) const override
    {
        if (role == Qt::BackgroundRole && isDirty(idx))
            return QBrush(QColor(Qt::yellow));
        return QSqlTableModel::data(idx, role);
    }
};
#endif // MAINWINDOW_H
