#ifndef EMMCRAW_H
#define EMMCRAW_H

#include <QWidget>
#include "TabWidgetBase.h"

namespace Ui {
class EmmcRawWidget;
}
class MainWindow;
class EmmcRawWidget : public TabWidgetBase
{
    Q_OBJECT

public:
    enum Column{
            ColumnEnable = 0,
            ColumnName,
            ColumnReadFlag,
            ColumnAddr,
            ColumnLength,
            ColumnRegion,
            ColumnFile
        };
    explicit EmmcRawWidget(QTabWidget *parent, MainWindow *window);
    ~EmmcRawWidget();
    DECLARE_TABWIDGET_VFUNCS()
int AddItem();
private slots:
    void on_pushButton_7_clicked();

private:
    Ui::EmmcRawWidget *ui;
    MainWindow *main_window_;
};

#endif // EMMCRAW_H
