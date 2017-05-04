#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>
#include "connectiondialog.h"
#include <QMdiSubWindow>
#include <QMessageBox>
#include <QMenu>
#include "sensordataloadwindow.h"
#include "sensortablewindow.h"
#include "analyzewindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ConnectAction_triggered();

    void on_LoadAction_triggered();

    void on_DisconnectAction_triggered();

    void on_ShowTableAction_triggered();

    void setStyle();

    void on_AnalyzeAction_triggered();

private:
    void checkSubWindowUnique(QWidget* widget);
    void initStatusBar();
    bool checkConnData(connectionData cData);
    Ui::MainWindow *ui;
    SensorDatabase* SensorDb=NULL;
    QLabel* dbStatus=NULL;
};

#endif // MAINWINDOW_H
