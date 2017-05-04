#ifndef XYSERIESFACTORY_H
#define XYSERIESFACTORY_H

#include <QtCharts/QXYSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QScatterSeries>
using namespace QtCharts;


enum XY_SERIES_ENUM
{
    SCATTER_SERIES,
    LINE_SERIES,
    SPLINE_SERIES
};


class XYSeriesFactory
{
public:
    explicit XYSeriesFactory();
    QXYSeries* createSeries(XY_SERIES_ENUM seriesType);
private:


};

#endif // XYSERIESFACTORY_H
