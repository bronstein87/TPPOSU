#include "xyseriesfactory.h"

XYSeriesFactory::XYSeriesFactory()
{

}

QXYSeries* XYSeriesFactory::createSeries(XY_SERIES_ENUM seriesType)
{
    switch(seriesType)
    {
    case SCATTER_SERIES:
        return new QScatterSeries();
        break;
    case LINE_SERIES:
        return new QLineSeries();
        break;
    case SPLINE_SERIES:
        return new QSplineSeries();
        break;

    }
}
