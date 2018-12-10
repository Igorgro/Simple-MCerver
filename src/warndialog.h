#ifndef WARNDIALOG_H
#define WARNDIALOG_H

#include <QDialog>

namespace Ui {
class WarnDialog;
}

class WarnDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WarnDialog(QWidget *parent = 0, QString label = "");
    ~WarnDialog();

private slots:
    void on_ok_button_clicked();

private:
    Ui::WarnDialog *ui;
};

#endif // WARNDIALOG_H
