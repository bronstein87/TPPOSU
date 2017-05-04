#include "intervalwindow.h"
#include "ui_intervalwindow.h"

IntervalWindow::IntervalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IntervalWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);
}

IntervalWindow::~IntervalWindow()
{
    delete ui;
}

void IntervalWindow::on_pushButton_2_clicked()
{
    close();
}

void IntervalWindow::on_pushButton_clicked()
{
    QString intervalFilter;
    if(ui->groupBox->isChecked())
    {
        intervalFilter+=QString(" AND sen1 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox->value()).arg(ui->doubleSpinBox_2->value());
    }
    if(ui->groupBox_2->isChecked())
    {
        intervalFilter+=QString(" AND sen2 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_3->value()).arg(ui->doubleSpinBox_4->value());
    }
    if(ui->groupBox_3->isChecked())
    {
        intervalFilter+=QString(" AND sen3 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_5->value()).arg(ui->doubleSpinBox_6->value());
    }
    if(ui->groupBox_4->isChecked())
    {
        intervalFilter+=QString(" AND sen4 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_7->value()).arg(ui->doubleSpinBox_8->value());
    }
    if(ui->groupBox_5->isChecked())
    {
        intervalFilter+=QString(" AND sen5 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_9->value()).arg(ui->doubleSpinBox_10->value());
    }
    if(ui->groupBox_6->isChecked())
    {
        intervalFilter+=QString(" AND sen6 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_11->value()).arg(ui->doubleSpinBox_12->value());
    }
    if(ui->groupBox_7->isChecked())
    {
        intervalFilter+=QString(" AND sen7 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_13->value()).arg(ui->doubleSpinBox_14->value());
    }
    if(ui->groupBox_8->isChecked())
    {
        intervalFilter+=QString(" AND sen8 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_15->value()).arg(ui->doubleSpinBox_16->value());
    }
    if(ui->groupBox_9->isChecked())
    {
        intervalFilter+=QString(" AND sen9 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_17->value()).arg(ui->doubleSpinBox_18->value());
    }
    if(ui->groupBox_10->isChecked())
    {
        intervalFilter+=QString(" AND sen10 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_19->value()).arg(ui->doubleSpinBox_20->value());
    }
    if(ui->groupBox_11->isChecked())
    {
        intervalFilter+=QString(" AND sen11 BETWEEN %1 AND %2")
                .arg(ui->doubleSpinBox_20->value()).arg(ui->doubleSpinBox_21->value());
    }
    emit filterReady(intervalFilter);

}
