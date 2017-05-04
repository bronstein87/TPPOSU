#ifndef CHARTPLOTTER_H
#define CHARTPLOTTER_H
#include <QObject>
#include <QString>
#include <QtCharts>
#include <QChartView>
#include <chartview.h>
using namespace QtCharts;

class ChartPlotterException : public std::exception
{
public:
    ChartPlotterException(const std::string &&whatStr) noexcept : whatStr(std::move(whatStr)) { }
    ChartPlotterException(const std::string &whatStr) noexcept : whatStr(whatStr) { }
    ~ChartPlotterException() noexcept=default;

    const char* what() const noexcept override
    {
        return whatStr.c_str();
    }

private:
    std::string whatStr;
};

/*Абстрактный класс для построения графиков*/
class ChartPlotter : public QObject
{
    Q_OBJECT
public:
    explicit ChartPlotter(QObject *parent = 0);

    ChartPlotter(const ChartPlotter&)                   =delete;

    ChartPlotter(ChartPlotter&& )                       =delete;

    ChartPlotter& operator=(const ChartPlotter&)        =delete;

    ChartPlotter& operator=(ChartPlotter&&)             =delete;

     virtual ~ChartPlotter() = 0 ;

    void setChartTitle(const QString& _chartTitle);

    QString getChartTitle() const;

    void setChartTheme(QChart::ChartTheme _chartTheme);

    QChart::ChartTheme getChartTheme() const;

    void setChartMargins(const QMargins& _margins);

    QMargins getChartMargins() const;

    void setChartViewRubberBand(QChartView::RubberBand _rubberBand);

    QChartView::RubberBand getChartViewRubberBand() const;

    void setChartViewRenderHind(QPainter::RenderHint _renderHint);

    QPainter::RenderHint getChartViewRenderHind() const;

    void setUseOpenGL(bool _useOpenGL);

    bool getUseOpenGL() const;

    static void deleteChart(ChartView *view);





protected:

    QChart* initializeChart();
    void plotChart (ChartView *view, QChart* chart);
    void enableLabelSwitch(QChart* chart);
    QString chartTitle;
    QChart::ChartTheme chartTheme;
    QMargins margins;
    QChartView::RubberBand rubberBand;
    QPainter::RenderHint renderHint;
    bool useOpenGL;

};




#endif // CHARTPLOTTER_H
