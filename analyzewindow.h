#ifndef ANALYZEWINDOW_H
#define ANALYZEWINDOW_H

#include <QWidget>
#include <sensordatabase.h>

namespace Ui {
class AnalyzeWindow;
}

class AnalyzeWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AnalyzeWindow(SensorDatabase* _db,QWidget *parent = 0);
    ~AnalyzeWindow();

private slots:
    void on_pushButton_clicked();

private:
    SensorDatabase* db;
    Ui::AnalyzeWindow *ui;
    void initChannelComboBox();
    QHash<QString, QString> sensorHash;
    void initSensorHash();
};

#endif // ANALYZEWINDOW_H
