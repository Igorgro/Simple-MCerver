#include "spawn_dialog.h"
#include "ui_spawn_dialog.h"

spawn_dialog::spawn_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::spawn_dialog)
{
    ui->setupUi(this);
}

spawn_dialog::~spawn_dialog()
{
    delete ui;
}
