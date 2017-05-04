#ifndef SENSORTABLEWINDOW_H
#define SENSORTABLEWINDOW_H

#include <QWidget>
#include <sensordatabase.h>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QFileDialog>
#include <intervalwindow.h>
#include "lrreportengine.h"
#include "lrcallbackdatasourceintf.h"
#include <QDebug>

namespace Ui {
class SensorTableWindow;
}

class SensorTableWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SensorTableWindow(SensorDatabase * _db,QWidget *parent = 0);
    ~SensorTableWindow();


private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_dateTimeEdit_editingFinished();

    void on_dateTimeEdit_2_editingFinished();

    void on_groupBox_clicked(bool checked);

    void on_pushButton_clicked();

    void on_toReportPushButton_clicked();

    void on_toFilePushButton_clicked();

    void on_comboBox_2_currentTextChanged(const QString &arg1);

private:
    void updateIntervalFilter(QString);
    void setFilter();
    void initOperatorComboBox();
    void setDateTimeRange();
    void showGeneralTable();
    void showAvgTable();
    Ui::SensorTableWindow *ui;
    SensorDatabase *db;
    QSqlTableModel* generalTable;
    QSqlQueryModel * avgModel;
    QString intervalFilterStr;
    QScopedPointer<LimeReport::ReportEngine> report;


};

#endif // SENSORTABLEWINDOW_H
