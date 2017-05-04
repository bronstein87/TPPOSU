#include "connectiondialog.h"
#include "ui_connectiondialog.h"
#include <QMessageBox>
#include <QObject>

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->portlineEdit->setValidator(new QIntValidator(0,65635));
}

ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}


void ConnectionDialog::on_connectionButton_clicked()
{

    if(ui->dbNamelineEdit->text().isEmpty()
            ||ui->userNamelineEdit->text().isEmpty()
            ||ui->hostlineEdit->text().isEmpty()
            ||ui->portlineEdit->text().isEmpty()
            ||ui->passwdlineEdit->text().isEmpty())
    {
        QMessageBox::information(NULL,"","Не заданы все параметры подключения");
        return;
    }
    connectionData cData;
    cData.dbName=ui->dbNamelineEdit->text();
    // лень делать по-человечески
    QHash<QString,QString> hashUserName;
    hashUserName["Борис Юматов"]="Boris Yumatov";
    hashUserName["Дмитрий Кондрашин"]="Dmitry Kondrashin";

    cData.userName=hashUserName[ui->userNamelineEdit->text()];
    cData.host=ui->hostlineEdit->text();
    cData.port=ui->portlineEdit->text().toInt();
    cData.password=ui->passwdlineEdit->text();
    emit connectionDataReady(cData);
    this->close();

}
