#ifndef SENSORDATALOADWINDOW_H
#define SENSORDATALOADWINDOW_H

#include <QWidget>
#include <QVector>
#include "plant.h"
#include <QPair>
#include <mathfunc.h>
#include "sensordatabase.h"
#include <QDateTime>
#include <QMessageBox>

namespace Ui {
class SensorDataLoadWindow;
}

class SensorDataLoadWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SensorDataLoadWindow(SensorDatabase* _db,QWidget *parent = 0);
    ~SensorDataLoadWindow();

private slots:
    void on_handlePushButton_clicked();

    void on_loadPushButton_clicked();

private:
    SensorDatabase* db;
    Ui::SensorDataLoadWindow *ui;
    QVector<QVector<double>> sensorsEvidence;
};

#endif // SENSORDATALOADWINDOW_H
