#include "mainwindow.h"
#include "ui_mainwindow.h"



QListWidgetItem* MainWindow::find_item (QListWidget* list_widget, QString& name)
{
    for (int i = 0; i < list_widget->count(); i++)
    {
        if (!list_widget->item(i)->text().compare(name)) return list_widget->item(i);
    }
    return nullptr;
}
