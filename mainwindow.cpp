#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "preparefilterwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStyle();
    initStatusBar();
    ui->mdiArea->setOption(QMdiArea::DontMaximizeSubWindowOnActivation,true);


    SensorDb=new SensorDatabase("QPSQL",this);
    if(!SensorDb->isDriverValid())
    {
        QMessageBox::information(NULL,tr("Ошибка"),tr("Драйвер БД не подключен"));
    }


}

void MainWindow::setStyle()
{
    QFile file(":/sources/style.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream stream(&file);
        qApp->setStyleSheet(stream.readAll());
        file.close();
    }
}

void MainWindow::on_ConnectAction_triggered()
{

    ConnectionDialog* connDialog=new ConnectionDialog();
    checkSubWindowUnique(connDialog);
    QMdiSubWindow* subWindow=ui->mdiArea->addSubWindow(connDialog,Qt::Dialog);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setFixedSize(subWindow->size());
    subWindow->show();
    connect(connDialog,&ConnectionDialog::connectionDataReady,this,&MainWindow::checkConnData);
    connect(connDialog,&ConnectionDialog::destroyed, subWindow,&QMdiSubWindow::close);

}




void MainWindow::on_LoadAction_triggered()
{
    SensorDataLoadWindow * sensorDataLoadWindow = new SensorDataLoadWindow(SensorDb);
    checkSubWindowUnique(sensorDataLoadWindow);
    QMdiSubWindow* subWindow=ui->mdiArea->addSubWindow(sensorDataLoadWindow,Qt::SubWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();



}
void MainWindow::on_ShowTableAction_triggered()
{
    PrepareFilterWindow * window = new PrepareFilterWindow(SensorDb);
    window ->setWindowModality(Qt::ApplicationModal);
    window ->show();
    connect(window,&PrepareFilterWindow::preparedFilterReady,[&](){

        qDebug()<<"qq";
        SensorTableWindow * sensorTableWindow = new SensorTableWindow(SensorDb);
        checkSubWindowUnique(sensorTableWindow);
        QMdiSubWindow* subWindow=ui->mdiArea->addSubWindow(sensorTableWindow,Qt::SubWindow);
        subWindow->setAttribute(Qt::WA_DeleteOnClose);
        subWindow->show();
    });


}


void MainWindow::checkSubWindowUnique(QWidget* widget)
{

    QList <QMdiSubWindow*> list=ui->mdiArea->subWindowList();
    for (const auto i:list)
    {
        if(i->widget()->metaObject()->className()==widget->metaObject()->className())
        {
            ui->mdiArea->removeSubWindow(i);
            delete i;
        }

    }
}


void MainWindow::initStatusBar()
{
    dbStatus=new QLabel(this);
    ui->statusbar->showMessage(tr("Оператор не авторизован"));
    QPixmap* dbstatimage=new QPixmap(":/sources/1484535369_remove-from-database.png");
    dbStatus->setPixmap(*dbstatimage);
    ui->statusbar->addPermanentWidget(dbStatus);
    delete dbstatimage;
}

bool MainWindow::checkConnData(connectionData cData)
{
    if(SensorDb->connectDb(cData))
    {
        ui->statusbar->showMessage(tr("Авторизация прошла успешно"));
        QPixmap* dbstatimage=new QPixmap(":/sources/1484535377_accept-database.png");
        dbStatus->setPixmap(*dbstatimage);
        delete dbstatimage;
        return true;
    }
    else
    {
        ui->statusbar->showMessage(tr("Авторизация не удалась"));
        return false;
    }
}

void MainWindow::on_DisconnectAction_triggered()
{
    SensorDb->disconnectDb();
    qApp->exit();

}

MainWindow::~MainWindow()
{
    SensorDb->disconnectDb();
    delete ui;
}



void MainWindow::on_AnalyzeAction_triggered()
{

    AnalyzeWindow * sensorAnalyzeWindow = new AnalyzeWindow(SensorDb);
    checkSubWindowUnique(sensorAnalyzeWindow);
    QMdiSubWindow* subWindow=ui->mdiArea->addSubWindow(sensorAnalyzeWindow,Qt::SubWindow);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->show();
}
