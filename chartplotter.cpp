#include "chartplotter.h"

ChartPlotter::ChartPlotter(QObject *parent) : QObject(parent),
    chartTitle(""),
    chartTheme(QChart::ChartThemeLight),
    margins(QMargins(0,0,0,0)),
    rubberBand(QChartView::RectangleRubberBand),
    renderHint(QPainter::Antialiasing),
    useOpenGL(false)

{

}


void ChartPlotter::setChartTitle(const QString& _chartTitle)
{
    chartTitle=_chartTitle;
}

QString ChartPlotter::getChartTitle() const
{
    return chartTitle;
}

void ChartPlotter::setChartTheme(QChart::ChartTheme _chartTheme)
{
    chartTheme=_chartTheme;
}

QChart::ChartTheme ChartPlotter::getChartTheme() const
{
    return chartTheme;
}

void ChartPlotter::setChartMargins(const QMargins& _margins)
{
    margins=_margins;
}

QMargins ChartPlotter::getChartMargins() const
{
    return margins;
}

void ChartPlotter::setChartViewRubberBand(QChartView::RubberBand _rubberBand)
{
    rubberBand=_rubberBand;
}

QChartView::RubberBand ChartPlotter::getChartViewRubberBand() const
{
    return rubberBand;
}

void ChartPlotter::setChartViewRenderHind(QPainter::RenderHint _renderHint)
{
    renderHint=_renderHint;
}

QPainter::RenderHint ChartPlotter::getChartViewRenderHind() const
{
    return renderHint;
}

void ChartPlotter::setUseOpenGL(bool _useOpenGL)
{
    useOpenGL=_useOpenGL;
}
bool ChartPlotter::getUseOpenGL() const
{
    return useOpenGL;
}

QChart* ChartPlotter::initializeChart()
{

    QChart* chart= new QChart();
    chart->setTitle(chartTitle);
    chart->setMargins(margins);
    chart->setTheme(chartTheme);

    return chart;
}


void ChartPlotter::plotChart(ChartView *view, QChart* chart)
{
    view->setChart(chart);
    view->setRenderHint(renderHint);
    view->setRubberBand(rubberBand);
}

void ChartPlotter::enableLabelSwitch(QChart* chart)
{
    for(const auto&marker:chart->legend()->markers())
    {
        connect(marker,&QLegendMarker::clicked,
                [=]()
        {
            marker->series()->setVisible(!marker->series()->isVisible());
            marker->setVisible(true);

            /*красим маркер серым*/
            double alpha = 1.0;

            if (!marker->series()->isVisible()) {
                alpha = 0.5;
            }

            QColor color;
            QBrush brush = marker->labelBrush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setLabelBrush(brush);

            brush = marker->brush();
            color = brush.color();
            color.setAlphaF(alpha);
            brush.setColor(color);
            marker->setBrush(brush);

            QPen pen = marker->pen();
            color = pen.color();
            color.setAlphaF(alpha);
            pen.setColor(color);
            marker->setPen(pen);});
    }
}

void ChartPlotter::deleteChart(ChartView *view)
{
    if(view->chart())
    {
        delete view->chart();
        view->setChart(NULL);
    }
}

ChartPlotter::~ChartPlotter()
{

}




