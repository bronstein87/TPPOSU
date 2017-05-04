#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_USE_NAMESPACE


class ChartView : public QChartView

{

public:
    ChartView(QWidget *parent = 0);

protected:

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);


private:

};

#endif
