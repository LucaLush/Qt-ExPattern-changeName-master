#include "selectpathdialog.h"
#include "ui_selectpathdialog.h"

selectPathDialog::selectPathDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selectPathDialog)
{
    ui->setupUi(this);
}

selectPathDialog::~selectPathDialog()
{
    delete ui;
}
