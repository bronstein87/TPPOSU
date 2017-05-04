#ifndef INTERVALWINDOW_H
#define INTERVALWINDOW_H

#include <QWidget>

namespace Ui {
class IntervalWindow;
}

class IntervalWindow : public QWidget
{
    Q_OBJECT

public:
    explicit IntervalWindow(QWidget *parent = 0);
    ~IntervalWindow();

signals:


    void filterReady(QString);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::IntervalWindow *ui;
};

#endif // INTERVALWINDOW_H
