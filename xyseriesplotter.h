#ifndef XYSERIESPLOTTER_H
#define XYSERIESPLOTTER_H
#include <cartesianplotter.h>
#include <xyseriesfactory.h>



/* класс для построение графиков с сериями, унаследованными от QXYSeries. Ось X для графиков с осью дата-время - это ось дата-время
 * тип серии выбирается в ооответствии с переданными в функцию перечислением XY_SERIES_ENUM. Создается через паттерн фарбрика.
 * В случае если серия точечная, проверяется приведение типа к ней, и если оно успешно - устанавливается scatterSize  */
class XYSeriesPlotter: public CartesianPlotter
{
    Q_OBJECT
public:
   explicit XYSeriesPlotter(QObject *parent=0);

    XYSeriesPlotter(const XYSeriesPlotter&)                   =delete;

    XYSeriesPlotter(XYSeriesPlotter&& )                       =delete;

    XYSeriesPlotter& operator=(const XYSeriesPlotter&)        =delete;

    XYSeriesPlotter& operator=(XYSeriesPlotter&&)             =delete;

     ~XYSeriesPlotter() ;

    void setStep(const qint32 _step);

    qint32 getStep() const;

    void setScatterSize(qint32 _scatterSize);

    qint32 getScatterSize() const;




    void plotDateTimeChart(ChartView* view, const QVector<double>& dataVec, const QVector<qint64>& dateTimeVec,XY_SERIES_ENUM seriesType);

    void plotDateTimeChart(ChartView* view,const QVector<QPointF>& dataVector,XY_SERIES_ENUM seriesType);

    void plotGroupDateTimeCharts(ChartView* view, const QVector<QVector<double>>& vecsOfData, const QVector<qint64>& dateTimeVec, QStringList seriesNames, XY_SERIES_ENUM seriesType);

    void plotGroupOwnDateTimeCharts(ChartView* view, const QVector<QVector<double>>& vecsOfData, const QVector<QVector<qint64>>& dateTimeVecs, const QStringList& seriesNames, XY_SERIES_ENUM seriesType);

    void plotDefAxisChart(ChartView* view,const QVector<double>& firstDataVec,const QVector<double>& secondDataVec,XY_SERIES_ENUM seriesType);

    void plotGroupDefAxisChart(ChartView* view, const QVector<QVector<QPointF>>& dataVec, const QStringList& seriesNames, XY_SERIES_ENUM seriesType);


private:
    qint32 scatterSize=10;
    qint32 step=1; //для функций перегруженных с QVector<QPointF> не используется
    XYSeriesFactory seriesFactory;

    void setAxisWithDateTime(QChart* chart);
};

#endif // XYSERIESPLOTTER_H
