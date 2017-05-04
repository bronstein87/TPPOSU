#ifndef CONNECTIONDIALOG_H
#define CONNECTIONDIALOG_H

#include <QDialog>
#include <sensordatabase.h>
#include <QValidator>


namespace Ui {
class ConnectionDialog;
}

class ConnectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectionDialog(QWidget *parent = 0);
    ~ConnectionDialog();

private slots:
    void on_connectionButton_clicked();

signals:
    void connectionDataReady(connectionData cData);
private:
    Ui::ConnectionDialog *ui;

};

#endif // CONNECTIONDIALOG_H
