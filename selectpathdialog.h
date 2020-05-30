#ifndef SELECTPATHDIALOG_H
#define SELECTPATHDIALOG_H

#include <QDialog>

namespace Ui {
class selectPathDialog;
}

class selectPathDialog : public QDialog
{
    Q_OBJECT

public:
    explicit selectPathDialog(QWidget *parent = nullptr);
    ~selectPathDialog();

private:
    Ui::selectPathDialog *ui;
};

#endif // SELECTPATHDIALOG_H
