#include "sensordataloadwindow.h"
#include "ui_sensordataloadwindow.h"
#include <QDebug>

SensorDataLoadWindow::SensorDataLoadWindow(SensorDatabase *_db, QWidget *parent) :
    QWidget(parent),db(_db),
    ui(new Ui::SensorDataLoadWindow)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,100);
    ui->progressBar->setValue(0);

}



void SensorDataLoadWindow::on_handlePushButton_clicked()
{


    sensorsEvidence.clear();

    ui->progressBar->setValue(0);
    Plant plant;
    plant_init(plant);
    const int countOfMeasures = ui->frameCountSpinBox->text().toInt();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(countOfMeasures);


    QVector<double> sensorEvidence;

    int sensorNumber=1;
    for(int i=0;i<countOfMeasures;i++)
    {
        sensorEvidence.append(plant_measure(sensorNumber,plant));
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 0 , newItem);

        qApp->processEvents();
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(9);


    sensorNumber=2;
    for(int i=0;i<countOfMeasures;i++)
    {
        double sensorData=(plant_measure(sensorNumber, plant)-30)/70;
        sensorEvidence.append(sensorData);
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 1 , newItem);
        qApp->processEvents();
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(18);


    sensorNumber=3;
    for(int i=0;i<countOfMeasures;i++)
    {
        sensorEvidence.append(plant_measure(sensorNumber,plant));
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 2 , newItem);
        qApp->processEvents();
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(27);


    sensorNumber=4;
    for(int i=0;i<countOfMeasures;i++)
    {
        sensorEvidence.append(plant_measure(sensorNumber,plant));
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 3 , newItem);
        qApp->processEvents();
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(36);



    sensorNumber=5;
    for(int i=0;i<countOfMeasures;i++)
    {
        double sensorData=plant_measure(sensorNumber,plant);
        sensorEvidence.append(sensorData);
        if(sensorData>=1 && sensorData<=3)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1 ( + )").arg(sensorEvidence.back()));
            ui->tableWidget->setItem(i, 4 , newItem);
            qApp->processEvents();
        }
        else
        {
            ui->errorTextEdit->append(QString("Канал №: %3. Кадр № %1. Значение: %2 - выход за пределы интервала \n")
                                      .arg(countOfMeasures).arg(sensorData).arg(sensorNumber));
        }
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(45);


    sensorNumber=6;
    for(int i=0;i<countOfMeasures;i++)
    {
        QVector <double> frameData;
        int countOfMeasuresInFrame=7;
        for(int j=0;j<countOfMeasuresInFrame;j++)
        {
            frameData.append(plant_measure(sensorNumber,plant));
            qApp->processEvents();
        }

        auto statValues=calculateMeanStDv(frameData.begin(),frameData.end(),0.0);
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("Среднее: %1  СКО : %2")
                                                         .arg(statValues.first).arg(statValues.second));
        ui->tableWidget->setItem(i, 5 , newItem);
        sensorEvidence.append(statValues.first);
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(54);




    sensorNumber=9;
    for(int i=0;i<countOfMeasures;i++)
    {
        int countOfMeasuresInFrame=3;
        double sensorDataToCheck=plant_measure(sensorNumber,plant);
        for(int j=0;j<countOfMeasuresInFrame;j++)
        {
            double sensorData = plant_measure(sensorNumber,plant);
            //ui->sensorNineTextEdit->append(QString::number(sensorData)+"\n");
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("+"));
            ui->tableWidget->setItem(i, 6 , newItem);
            qApp->processEvents();
            if(abs(sensorDataToCheck-sensorData)>0.1)
            {
                ui->errorTextEdit->append(QString("Канал  %1. Кадр № %2.Нарушена стабильность. Опрос канала прерван.\n")
                                          .arg(sensorNumber).arg(countOfMeasuresInFrame));
                break;
            }
        }
        sensorEvidence.append(sensorDataToCheck);
    }
    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(63);


    sensorNumber=19;

    for(int i=0;i<countOfMeasures;i++)
    {
        sensorEvidence.append(plant_measure(sensorNumber,plant));
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 7 , newItem);
        qApp->processEvents();
    }

    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(72);


    sensorNumber=49;

    for(int i=0;i<countOfMeasures;i++)
    {
        sensorEvidence.append(plant_measure(sensorNumber,plant));
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 8 , newItem);
        qApp->processEvents();
    }

    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(81);



    sensorNumber=69;

    for(int i=0;i<countOfMeasures;i++)
    {
        double sensorData = plant_measure(sensorNumber,plant);
        sensorData=0.3*sensorData/(0.1*sensorData-154);
        sensorEvidence.append(sensorData);
        QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg(sensorEvidence.back()));
        ui->tableWidget->setItem(i, 9 , newItem);
        qApp->processEvents();
    }

    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(90);


    sensorNumber=77;

    for(int i=0;i<countOfMeasures;i++)
    {
        int countOfMeasuresInFrame=4;
        double sensorDataToCheck=plant_measure(sensorNumber,plant);
        for(int j=0;j<countOfMeasuresInFrame;j++)
        {
            double sensorData = plant_measure(sensorNumber,plant);
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("+"));
            ui->tableWidget->setItem(i, 10 , newItem);
            qApp->processEvents();
            if(abs(sensorDataToCheck-sensorData)>0.1)
            {
                ui->errorTextEdit->append(QString("Канал № %1. Кадр № %2.Нарушена стабильность. Опрос канала прерван.\n")
                                          .arg(sensorNumber).arg(countOfMeasuresInFrame));
                break;
            }
        }
        sensorEvidence.append(sensorDataToCheck);
    }



    sensorsEvidence.append(sensorEvidence);
    sensorEvidence.clear();
    ui->progressBar->setValue(100);






}

void SensorDataLoadWindow::on_loadPushButton_clicked()
{

    ui->progressBar->setValue(0);

    try
    {
        ui->progressBar->setValue(50);
        QString note= ui->noteLineEdit->text();
        if(note.isEmpty())
        {
            note="Без замечаний";
        }
        db->loadIndications(sensorsEvidence,note);
        ui->progressBar->setValue(100);
        QMessageBox::information(NULL,tr("Информация"),"Загрузка данных в базу успешно завершена.");
        sensorsEvidence.clear();
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }
}


SensorDataLoadWindow::~SensorDataLoadWindow()
{
    delete ui;
}

