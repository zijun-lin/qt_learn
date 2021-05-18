#ifndef DISPLAY_CURVE_H
#define DISPLAY_CURVE_H
#include "qcustomplot.h"
#include "qvector.h"

void DisplayCheck(QCustomPlot *customPlot);
void setupQuadraticDemo(QCustomPlot *customPlot);
void setupSimpleDemo(QCustomPlot *customPlot);
void setupSincScatterDemo(QCustomPlot *customPlot);
void setupLineStyleDemo(QCustomPlot *customPlot);
void QCPcrv(QCustomPlot *customPlot);


class DisplayCurve {
public:
    DisplayCurve(QCustomPlot *custom_plot);
    ~DisplayCurve() = default;
    void ClearCurve();
    bool UpdateCurve(QVector<double> &curve_x, QVector<double> &curve_y,
                     const QColor &color, const Qt::PenStyle &pen_style,
                     double pen_width, double q_brush_size, bool display_termipoints);
private:
    QCPCurve *curve_;
    QCPCurve *curve_termipoint_;
};



#endif // DISPLAY_CURVE_H
