#include "xyseriesplotter.h"

XYSeriesPlotter::XYSeriesPlotter(QObject *parent): CartesianPlotter(parent)
{

}


void XYSeriesPlotter::setStep(const qint32 _step)
{
    step=_step;
}

qint32 XYSeriesPlotter::getStep() const
{
    return step;
}

void XYSeriesPlotter::setScatterSize(qint32 _scatterSize)
{
    scatterSize=_scatterSize;
}

qint32 XYSeriesPlotter::getScatterSize() const
{
    return scatterSize;
}

void XYSeriesPlotter::plotGroupDefAxisChart(ChartView* view,const QVector<QVector<QPointF>>& dataVec, const QStringList& seriesNames,XY_SERIES_ENUM seriesType)
{
    if(dataVec.size()!=seriesNames.size())
    {
        throw ChartPlotterException("plotGroupDefAxisChart: размерности входных данных не совпадают");
    }
    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }
    QChart* chart= initializeChart();

    for(int currData=0;currData<dataVec.size();currData++)
    {
        QXYSeries* series= seriesFactory.createSeries(seriesType);
        series->replace(dataVec[currData]);
        series->setName(seriesNames.at(currData));

        /*если серия точечная, задаем размер точки*/
        if(qobject_cast<QScatterSeries*>(series))
        {
            qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
        }
        series->setUseOpenGL(useOpenGL);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();

    qobject_cast<QValueAxis*>(chart->axisX())->setLabelFormat(axisXFormat);
    qobject_cast<QValueAxis*>(chart->axisY())->setLabelFormat(axisYFormat);

    qobject_cast<QValueAxis*>(chart->axisX())->setTickCount(XTickCount);
    qobject_cast<QValueAxis*>(chart->axisY())->setTickCount(YTickCount);

    chart->axisY()->setTitleText(axisYName);
    chart->axisX()->setTitleText(axisXName);


    plotChart(view, chart);
    enableLabelSwitch(chart);
    delete chartToDelete;

}




void XYSeriesPlotter::plotDefAxisChart(ChartView* view, const QVector<double>& firstDataVec, const QVector<double>& secondDataVec, XY_SERIES_ENUM seriesType)
{
    if(firstDataVec.size()!=secondDataVec.size())
    {
        throw ChartPlotterException("plotDefAxisChart: размерности входных данных не совпадают");
    }
    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }

    QChart* chart = initializeChart();

    QXYSeries* series= seriesFactory.createSeries(seriesType);

    /*если серия точечная, задаем размер точки*/
    if(qobject_cast<QScatterSeries*>(series))
    {
        qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
    }

    for(qint32 i=0;i<firstDataVec.size();i+=step)
    {
        qApp->processEvents();
        series->append(firstDataVec[i],secondDataVec[i]);
    }

    chart->addSeries(series);
    chart->createDefaultAxes();

    qobject_cast<QValueAxis*>(chart->axisX())->setLabelFormat(axisXFormat);
    qobject_cast<QValueAxis*>(chart->axisY())->setLabelFormat(axisYFormat);

    qobject_cast<QValueAxis*>(chart->axisX())->setTickCount(XTickCount);
    qobject_cast<QValueAxis*>(chart->axisY())->setTickCount(YTickCount);

    chart->axisY()->setTitleText(axisYName);
    chart->axisX()->setTitleText(axisXName);

    plotChart(view, chart);

    delete chartToDelete;

}



void XYSeriesPlotter::plotDateTimeChart(ChartView* view,const QVector<double>& dataVec,const QVector<qint64>& dateTimeVec,XY_SERIES_ENUM seriesType)
{
    if(dataVec.size()!=dateTimeVec.size())
    {
        throw ChartPlotterException("plotDateTimeChart: размерности входных данных не совпадают");
    }

    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }
    QChart* chart= initializeChart();

    QXYSeries* series= seriesFactory.createSeries(seriesType);

    /*если серия точечная, задаем размер точки*/
    if(qobject_cast<QScatterSeries*>(series))
    {
        qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
    }

    for(qint32 i=0;i<dateTimeVec.size();i+=step)
    {
        qApp->processEvents();
        series->append(dateTimeVec[i],dataVec[i]);
    }
    chart->addSeries(series);


    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setTickCount(XTickCount);
    //"yyyy-MM-dd hh:mm:ss"
    axisX->setFormat(axisXFormat);
    axisX->setTitleText(axisXName);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis;
    axisY->setLabelFormat(axisYFormat);
    axisY->setTitleText(axisYName);
    axisY->setTickCount(YTickCount);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);
    axisY->applyNiceNumbers();


    plotChart(view, chart);

    delete chartToDelete;

}

void XYSeriesPlotter::setAxisWithDateTime(QChart* chart)
{
    chart->createDefaultAxes();
    chart->axisY()->setTitleText(axisYName);
    qobject_cast<QValueAxis*>(chart->axisY())->setLabelFormat(axisYFormat);
    qobject_cast<QValueAxis*>(chart->axisY())->setTickCount(YTickCount);
    qobject_cast<QValueAxis*>(chart->axisY())->applyNiceNumbers();
    chart->removeAxis(chart->axisX());

    QDateTimeAxis *axisX = new QDateTimeAxis;
    //"yyyy-MM-dd hh:mm:ss"
    axisX->setTickCount(XTickCount);
    axisX->setFormat(axisXFormat);
    axisX->setTitleText(axisXName);
    chart->addAxis(axisX, Qt::AlignBottom);

    for(auto i:chart->series())
    {
        i->attachAxis(chart->axisX());
    }
}

void XYSeriesPlotter::plotDateTimeChart(ChartView* view, const QVector<QPointF>& dataVector, XY_SERIES_ENUM seriesType)
{
    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }
    QChart* chart= initializeChart();

    QXYSeries* series= seriesFactory.createSeries(seriesType);

    /*если серия точечная, задаем размер точки*/
    if(qobject_cast<QScatterSeries*>(series))
    {
        qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
    }

    series->replace(dataVector);
    chart->addSeries(series);
    setAxisWithDateTime(chart);


    plotChart (view, chart);
    delete chartToDelete;
}


/*строит несколько графиков в зависимости от одних значений времени*/
void XYSeriesPlotter::plotGroupDateTimeCharts(ChartView* view,const QVector<QVector<double>>& vecsOfData,const QVector<qint64>& dateTimeVec,QStringList seriesNames,XY_SERIES_ENUM seriesType)
{
    if(vecsOfData.size()!=seriesNames.size())
    {
        throw ChartPlotterException("plotGroupDateTimeCharts: размерности входных данных не совпадают");
    }

    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }
    QChart* chart= initializeChart();


    for(qint32 curSeries=0;curSeries<vecsOfData.size();curSeries++)
    {
        QXYSeries* series= seriesFactory.createSeries(seriesType);

        /*если серия точечная, задаем размер точки*/
        if(qobject_cast<QScatterSeries*>(series))
        {
            qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
        }

        series->setName(seriesNames[curSeries]);
        for(qint32 i=0;i<dateTimeVec.size();i+=step)
        {
            qApp->processEvents();
            series->append(dateTimeVec[i],vecsOfData[curSeries][i]);
        }
        chart->addSeries(series);

        /*оси еще можно присвоить здесь, если создать их до внешнего цикла*/
        //        if(curSeries==0)
        //        {
        //            chart->addAxis(axisY, Qt::AlignLeft);
        //            chart->addAxis(axisX, Qt::AlignBottom);
        //        }
        //        series->attachAxis(axisX);
        //        series->attachAxis(axisY);

    }

    setAxisWithDateTime(chart);
    plotChart(view, chart);
    enableLabelSwitch(chart);

    delete chartToDelete;
}


/*строит несколько графиков в зависимости от собственных значений времени*/
void XYSeriesPlotter::plotGroupOwnDateTimeCharts(ChartView* view,const QVector<QVector<double>>& vecsOfData,const QVector<QVector<qint64>>& dateTimeVecs,const QStringList& seriesNames,XY_SERIES_ENUM seriesType)
{
    if(vecsOfData.size()!=seriesNames.size())
    {
        throw ChartPlotterException("plotGroupOwnDateTimeCharts: размерности входных данных не совпадают");
    }
    QChart* chartToDelete=NULL;
    if(view->chart())
    {
        chartToDelete=view->chart();
    }
    QChart* chart= initializeChart();

    for(qint32 currentDeviceData=0;currentDeviceData<dateTimeVecs.size();currentDeviceData++)
    {
        QXYSeries* series= seriesFactory.createSeries(seriesType);

        /*если серия точечная, задаем размер точки*/
        if(qobject_cast<QScatterSeries*>(series))
        {
            qobject_cast<QScatterSeries*>(series)->setMarkerSize(scatterSize);
        }
        series->setName(seriesNames[currentDeviceData]);
        for(qint32 i=0;i<dateTimeVecs[currentDeviceData].size();i+=step)
        {
            qApp->processEvents();
            series->append(dateTimeVecs[currentDeviceData][i],vecsOfData[currentDeviceData][i]);
        }
        chart->addSeries(series);
    }

    setAxisWithDateTime(chart);

    plotChart(view, chart);

    enableLabelSwitch(chart);
    delete chartToDelete;
}

XYSeriesPlotter::~XYSeriesPlotter()
{

}
