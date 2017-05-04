#ifndef CARTESIANPLOTTER_H
#define CARTESIANPLOTTER_H
#include <chartplotter.h>

/* ДОБАВИТЬ ИСКЛЮЧЕНИЯ */

/*Абстрактный класс построения графиков с осями*/
class CartesianPlotter: public ChartPlotter
{
    Q_OBJECT
public:
    explicit CartesianPlotter(QObject *parent = 0);

    CartesianPlotter(const CartesianPlotter&)                   =delete;

    CartesianPlotter(CartesianPlotter&& )                       =delete;

    CartesianPlotter& operator=(const CartesianPlotter&)        =delete;

    CartesianPlotter& operator=(CartesianPlotter&&)             =delete;

    virtual ~CartesianPlotter() = 0 ;

    void setAxisXName(const QString& _axisXName);

    QString getAxisXName() const;

    void setAxisXFormat(const QString& _axisXFormat);

    QString getAxisXFormat() const;

    void setAxisYName(const QString& _axisYName);

    QString getAxisYName() const;

    void setAxisYFormat(const QString& _axisYFormat);

    QString getAxisYFormat() const;

    void setYTickCount(const qint32 _step);

    qint32 getYTickCount() const;

    void setXTickCount(const qint32 _step);

    qint32 getXTickCount() const;



protected:
    QString axisXName;
    QString axisXFormat;// не используется в BarPlotter
    qint32 XTickCount; // не используется в BarPlotter
    QString axisYName;
    QString axisYFormat;
    qint32 YTickCount;

private:


};
#endif // CARTESIANPLOTTER_H
