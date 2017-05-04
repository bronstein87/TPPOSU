#include "sensortablewindow.h"
#include "ui_sensortablewindow.h"
#include "preparefilterwindow.h"


void SensorTableWindow::initOperatorComboBox()
{
    QStringList operators;
    operators<<"Все"<<"Борис Юматов"<<"Дмитрий Кондрашин";
    ui->comboBox->insertItems(0,operators);
    QStringList list = db->getComments();
    list.prepend("Все");
    ui->comboBox_2->insertItems(0, list );

}

void SensorTableWindow::setDateTimeRange()
{
    try
    {
    QPair<QDateTime,QDateTime> minMaxDateTime = db->getMinMaxDateTime();
    ui->dateTimeEdit->setDateTime(minMaxDateTime.first);
    ui->dateTimeEdit_2->setDateTime(minMaxDateTime.second);
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }
}

SensorTableWindow::SensorTableWindow(SensorDatabase *_db, QWidget *parent) :
    QWidget(parent),db(_db),
    ui(new Ui::SensorTableWindow)
{
    ui->setupUi(this);
    setDateTimeRange();
    initOperatorComboBox();
    showGeneralTable();
    showAvgTable();
    qDebug()<<"qq";
    generalTable->setFilter(db->getCurrentFilter());
    avgModel->setQuery(QString("select avg(sen1),avg(sen2),avg(sen3),avg(sen4),avg(sen5),avg(sen6)"
                               ",avg(sen7),avg(sen8),avg(sen9),avg(sen10),avg(sen11) "
                               "FROM sensor WHERE %1 ").arg(db->getCurrentFilter()));
    qDebug()<<"qq";
}

SensorTableWindow::~SensorTableWindow()
{
    delete ui;
}

void SensorTableWindow::showGeneralTable()
{

    generalTable= new QSqlTableModel(this);
    generalTable->setTable("sensor");
    generalTable->select();


    generalTable->setHeaderData(0, Qt::Horizontal,
                                QObject::tr("Дата|время"));
    generalTable->setHeaderData(1, Qt::Horizontal,
                                QObject::tr("Оператор"));
    generalTable->setHeaderData(2, Qt::Horizontal,
                                QObject::tr("К1"));
    generalTable->setHeaderData(3, Qt::Horizontal,
                                QObject::tr("К2"));
    generalTable->setHeaderData(4, Qt::Horizontal,
                                QObject::tr("К3"));
    generalTable->setHeaderData(5, Qt::Horizontal,
                                QObject::tr("К4"));
    generalTable->setHeaderData(6, Qt::Horizontal,
                                QObject::tr("К5"));
    generalTable->setHeaderData(7, Qt::Horizontal,
                                QObject::tr("К6"));
    generalTable->setHeaderData(8, Qt::Horizontal,
                                QObject::tr("К9"));
    generalTable->setHeaderData(9, Qt::Horizontal,
                                QObject::tr("К19"));
    generalTable->setHeaderData(10, Qt::Horizontal,
                                QObject::tr("К49"));
    generalTable->setHeaderData(11, Qt::Horizontal,
                                QObject::tr("К69"));
    generalTable->setHeaderData(12, Qt::Horizontal,
                                QObject::tr("К77"));
    generalTable->setHeaderData(13, Qt::Horizontal,
                                QObject::tr("Замечания"));


    ui->genTableView->setModel(generalTable);
    ui->genTableView->setSortingEnabled(true);
    report.reset(new LimeReport::ReportEngine());
    report->dataManager()->addModel("sensor_table",generalTable,true);
    qDebug()<<report->loadFromFile("://sources/template_report5.lrxml");

}

void SensorTableWindow::showAvgTable()
{

    avgModel= new QSqlQueryModel(this);
    avgModel->setQuery("select avg(sen1),avg(sen2),avg(sen3),avg(sen4),avg(sen5),avg(sen6),avg(sen7),avg(sen8),avg(sen9),avg(sen10),avg(sen11) from sensor");


    avgModel->setHeaderData(0, Qt::Horizontal,
                            QObject::tr("К1"));
    avgModel->setHeaderData(1, Qt::Horizontal,
                            QObject::tr("К2"));
    avgModel->setHeaderData(2, Qt::Horizontal,
                            QObject::tr("К3"));
    avgModel->setHeaderData(3, Qt::Horizontal,
                            QObject::tr("К4"));
    avgModel->setHeaderData(4, Qt::Horizontal,
                            QObject::tr("К5"));
    avgModel->setHeaderData(5, Qt::Horizontal,
                            QObject::tr("К6"));
    avgModel->setHeaderData(6, Qt::Horizontal,
                            QObject::tr("К9"));
    avgModel->setHeaderData(7, Qt::Horizontal,
                            QObject::tr("К19"));
    avgModel->setHeaderData(8, Qt::Horizontal,
                            QObject::tr("К49"));
    avgModel->setHeaderData(9, Qt::Horizontal,
                            QObject::tr("К69"));
    avgModel->setHeaderData(10, Qt::Horizontal,
                            QObject::tr("К77"));
    ui->avgTableView->setModel(avgModel);
}


void SensorTableWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(ui->groupBox->isChecked())
        setFilter();
}

void SensorTableWindow::on_dateTimeEdit_editingFinished()
{
    if(ui->groupBox->isChecked())
        setFilter();
}

void SensorTableWindow::on_dateTimeEdit_2_editingFinished()
{
    if(ui->groupBox->isChecked())
        setFilter();
}

void SensorTableWindow::on_groupBox_clicked(bool checked)
{
    if(checked)
    {
        setFilter();
    }
    else
    {
        generalTable->setFilter("");
        generalTable->select();
        avgModel->setQuery("select avg(sen1),avg(sen2),avg(sen3),avg(sen4),avg(sen5),avg(sen6),avg(sen7),avg(sen8),avg(sen9),avg(sen10),avg(sen11) from sensor");
    }
}

void SensorTableWindow::setFilter()
{
    try
    {
    QString fromDate=ui->dateTimeEdit->dateTime().toString(Qt::ISODate);
    QString toDate=ui->dateTimeEdit_2->dateTime().toString(Qt::ISODate);
    QString dateTimeFilter=QString("datetime BETWEEN '%1' AND '%2'")
            .arg(fromDate).arg(toDate);
    QString username=ui->comboBox->currentText();
    QString userNameFilter;
    if(username=="Все")
    {
        userNameFilter="";
    }
    else
    {
        userNameFilter=QString(" AND username="+QString("'")+username+QString("'"));
    }

    QString noteFilter;
    QString note = ui->comboBox_2->currentText();

    if(note=="Все")
    {
        noteFilter ="";
    }
    else
    {
        noteFilter = QString(" AND note="+QString("'")+note+QString("'"));
    }

    QString generalFilter=dateTimeFilter+userNameFilter+ noteFilter +intervalFilterStr;
    generalTable->setFilter(generalFilter);
    avgModel->setQuery(QString("select avg(sen1),avg(sen2),avg(sen3),avg(sen4),avg(sen5),avg(sen6)"
                               ",avg(sen7),avg(sen8),avg(sen9),avg(sen10),avg(sen11) "
                               "FROM sensor WHERE %1 ").arg(generalFilter));
    db->setCurrentFilter(generalFilter);
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }


}

void SensorTableWindow::on_pushButton_clicked()
{
    IntervalWindow* window= new IntervalWindow();
    window->show();
    connect(window,&IntervalWindow::filterReady,this,&SensorTableWindow::updateIntervalFilter);
}


void SensorTableWindow::updateIntervalFilter(QString filter)
{
    intervalFilterStr=filter;
    setFilter();
}


void SensorTableWindow::on_toReportPushButton_clicked()
{
    //report->designReport();
    report->previewReport();

}

void SensorTableWindow::on_toFilePushButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                 "",
                                 tr("Tables (*.csv)"));
    db->saveCSV(fileName);
    QMessageBox::information(NULL,"","Успешно сохранено.");

}

void SensorTableWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(ui->groupBox->isChecked())
        setFilter();
}
