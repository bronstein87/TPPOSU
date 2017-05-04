#include "preparefilterwindow.h"
#include "ui_preparefilterwindow.h"
#include <QMessageBox>

PrepareFilterWindow::PrepareFilterWindow(SensorDatabase* _db,QWidget *parent) :
    db(_db),QWidget(parent),
    ui(new Ui::PrepareFilterWindow)
{

    ui->setupUi(this);
    setWindowModality(Qt::WindowModal);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::Dialog);
    QStringList operators;
    operators<<"Все"<<"Борис Юматов"<<"Дмитрий Кондрашин";
    ui->comboBox->insertItems(0,operators);

    try
    {
    QPair<QDateTime,QDateTime> minMaxDateTime = db->getMinMaxDateTime();
    ui->dateTimeEdit->setDateTime(minMaxDateTime.first);
    ui->dateTimeEdit_2->setDateTime(minMaxDateTime.second);
    QStringList list = db->getComments();
    list.prepend("Все");
    ui->comboBox_2->insertItems(0, list );
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }
}

PrepareFilterWindow::~PrepareFilterWindow()
{
    delete ui;
}

void PrepareFilterWindow::on_pushButton_clicked()
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

    QString generalFilter=dateTimeFilter+noteFilter+userNameFilter;

    db->setCurrentFilter(generalFilter);
    }
    catch(std::exception& e)
    {
        QMessageBox::information(NULL,tr("Ошибка"),e.what());
    }
    emit preparedFilterReady();
    close();
}
