#ifndef PREPAREFILTERWINDOW_H
#define PREPAREFILTERWINDOW_H

#include <QWidget>
#include "sensordatabase.h"

namespace Ui {
class PrepareFilterWindow;
}

class PrepareFilterWindow : public QWidget
{
    Q_OBJECT

public:
    explicit PrepareFilterWindow(SensorDatabase* _db,QWidget *parent = 0);
    ~PrepareFilterWindow();

private slots:
    void on_pushButton_clicked();
signals:

   void preparedFilterReady();

private:
    SensorDatabase* db;
    Ui::PrepareFilterWindow *ui;
};

#endif // PREPAREFILTERWINDOW_H
