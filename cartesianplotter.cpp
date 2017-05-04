#include "cartesianplotter.h"

CartesianPlotter::CartesianPlotter(QObject *parent) :ChartPlotter(parent),
        axisXName(""),
        axisXFormat(""),
        XTickCount(10),
        axisYName(""),
        axisYFormat(""),
        YTickCount(5)
{

}

void CartesianPlotter::setAxisXName(const QString& _axisXName)
{
    axisXName=_axisXName;
}

QString CartesianPlotter::getAxisXName() const
{
    return axisXName;
}

void CartesianPlotter::setAxisXFormat(const QString& _axisXFormat)
{
    axisXFormat=_axisXFormat;
}

QString CartesianPlotter::getAxisXFormat() const
{
    return axisXFormat;
}

void CartesianPlotter::setAxisYName(const QString& _axisYName)
{
    axisYName=_axisYName;
}

QString CartesianPlotter::getAxisYName() const
{
    return axisYName;
}

void CartesianPlotter::setAxisYFormat(const QString& _axisYFormat)
{
    axisYFormat=_axisYFormat;
}

QString CartesianPlotter::getAxisYFormat() const
{
    return axisYFormat;
}


void CartesianPlotter::setYTickCount(const qint32 _YTickCount)
{
    YTickCount=_YTickCount;
}

qint32 CartesianPlotter::getYTickCount() const
{
    return YTickCount;
}

void CartesianPlotter::setXTickCount(const qint32 _XTickCount)
{
    XTickCount=_XTickCount;
}

qint32 CartesianPlotter::getXTickCount() const
{
    return XTickCount;
}


 CartesianPlotter::~CartesianPlotter()
{

}
