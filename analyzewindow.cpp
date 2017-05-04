#include "analyzewindow.h"
#include "ui_analyzewindow.h"
#include "xyseriesplotter.h"
#include <QDebug>



AnalyzeWindow::AnalyzeWindow(SensorDatabase* _db,QWidget *parent ) :
    db(_db),QWidget(parent),
    ui(new Ui::AnalyzeWindow)
{
    ui->setupUi(this);
    initChannelComboBox();
    initSensorHash();
}


void AnalyzeWindow::initChannelComboBox()
{
    QStringList channels;
    channels<<"Канал №1"<<"Канал №2"<<"Канал №3"
           <<"Канал №4"<<"Канал №5"<<"Канал №6"
          <<"Канал №9"<<"Канал №19"<<"Канал №49"
         <<"Канал №69"<<"Канал №77";
    ui->comboBox->insertItems(0,channels);
}

void AnalyzeWindow::initSensorHash()
{
    sensorHash["Канал №1"] = "sen1";
    sensorHash["Канал №2"] = "sen2";
    sensorHash["Канал №3"] = "sen3";
    sensorHash["Канал №4"] = "sen4";
    sensorHash["Канал №5"] = "sen5";
    sensorHash["Канал №6"] = "sen6";
    sensorHash["Канал №7"] = "sen7";
    sensorHash["Канал №8"] = "sen8";
    sensorHash["Канал №9"] = "sen9";
    sensorHash["Канал №10"] = "sen10";
    sensorHash["Канал №11"] = "sen11";
}

AnalyzeWindow::~AnalyzeWindow()
{
    delete ui;
}

void AnalyzeWindow::on_pushButton_clicked()
{
    try
    {
        QString channelName=sensorHash[ui->comboBox->currentText()];
        qDebug()<<channelName;
        SensorInfo info=db->getSensorInfo(channelName);
        if(info.data.isEmpty())
        {
            QMessageBox::information(NULL,tr("Ошибка"),"Нет данных по данному фильтру");
        }
        XYSeriesPlotter plotter;
        plotter.setAxisYFormat("%i");
        plotter.setAxisXFormat("%i");
        plotter.setChartTitle(QString("Среднее: %1, Дисперсия: %2").arg(info.average).arg(info.dispersio));
        QVector<double> xData;
        for(int i=0;i<info.data.size();i++)
        {
            xData.append(i);
        }
        plotter.plotDefAxisChart(ui->chartView,xData,info.data,XY_SERIES_ENUM::LINE_SERIES);
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }
}
