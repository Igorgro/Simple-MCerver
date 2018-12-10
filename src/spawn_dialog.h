#ifndef SPAWN_DIALOG_H
#define SPAWN_DIALOG_H

#include <QDialog>

namespace Ui {
class spawn_dialog;
}

class spawn_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit spawn_dialog(QWidget *parent = nullptr);
    ~spawn_dialog();

private:
    Ui::spawn_dialog *ui;
};

#endif // SPAWN_DIALOG_H
