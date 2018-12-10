#include "warndialog.h"
#include "ui_warndialog.h"

WarnDialog::WarnDialog(QWidget *parent, QString label) :
    QDialog(parent),
    ui(new Ui::WarnDialog)
{
    ui->setupUi(this);
    ui->warn_label->setText(label);
}

WarnDialog::~WarnDialog()
{
    delete ui;
}

void WarnDialog::on_ok_button_clicked()
{
    this->close();
}
