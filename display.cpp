#include "display.h"
#include <iostream>
#include "ui_mainwindow.h"


void DisplayCheck(QCustomPlot *customPlot) {

    customPlot->resize(600, 600); // set picture size

    setupQuadraticDemo(customPlot);

    DisplayCurve display_curve(customPlot);
    QVector<double> curve_x(101), curve_y(101);
    for (int i = 0; i < 101; ++i) {
      curve_x[i] = i / 50.0 - 1;
      curve_y[i] = curve_x[i] * curve_x[i];
    }
    display_curve.ClearCurve();
    display_curve.UpdateCurve(curve_x, curve_y,
                              Qt::red, Qt::SolidLine,
                              4, 4, true);

    customPlot->xAxis->setRange(-1.5, 1.5);
    customPlot->yAxis->setRange(0, 1.5);
}


void setupQuadraticDemo(QCustomPlot *customPlot) {
    QVector<double> x(101), y(101);
    for (int i=0; i<101; ++i) {
      x[i] = i/50.0 - 1;
      y[i] = x[i]*x[i];
    }
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::red)); // set line color
    customPlot->graph(0)->setData(x, y);
    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
}

void setupSimpleDemo(QCustomPlot *customPlot) {
    // add two new graphs and set their look:
    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // set line color
    customPlot->graph(0)->setBrush(QBrush(QColor(0,0,255,20))); // set line brush
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red));
    // grnerate some point of data (y0 for first, y1 for second graph)
    QVector<double> x(251), y0(251), y1(251);
    for (int i = 0; i < 251; ++i) {
        x[i] = i;
        y0[i] = qExp(-i/150.0) * qCos(i / 10.0);
        y1[i] = qExp(-i/150.0);
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    QObject::connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    QObject::connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data point to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void setupSincScatterDemo(QCustomPlot *customPlot) {
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    // set locale to english, so we get english decimal separator
    customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    // add confidence band graphs:
    customPlot->addGraph();
    QPen pen;
    pen.setStyle(Qt::DotLine);
    pen.setWidth(1);
    pen.setColor(QColor(180, 180, 180));
    customPlot->graph(0)->setName("Confidence Brand 68%");
    customPlot->graph(0)->setPen(pen);
    customPlot->graph(0)->setBrush(QBrush(QColor(255,50,30,20)));
    customPlot->addGraph();
    customPlot->legend->removeItem(customPlot->legend->itemCount() - 1);
    customPlot->graph(1)->setPen(pen);
    customPlot->graph(0)->setChannelFillGraph(customPlot->graph(1));
    // add theory curve graph:
    customPlot->addGraph();
    pen.setStyle(Qt::DashLine);
    pen.setWidth(2);
    pen.setColor(Qt::red);
    customPlot->graph(2)->setPen(pen);
    customPlot->graph(2)->setName("Theory Curve");
    // add data point graph:
    customPlot->addGraph();
    customPlot->graph(3)->setPen(QPen(Qt::blue));
    customPlot->graph(3)->setName("Measurement");
    customPlot->graph(3)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, 4));
    // add error bars:
    QCPErrorBars *errorBars = new QCPErrorBars(customPlot->xAxis, customPlot->yAxis);
    errorBars->removeFromLegend();
    errorBars->setAntialiased(false);
    errorBars->setDataPlottable(customPlot->graph(3));
    errorBars->setPen(QPen(QColor(180,180,180)));

    // generate ideal sinc curve data and some randomly perturbed data for scatter plot:
    QVector<double> x0(250), y0(250);
    QVector<double> yConfUpper(250), yConfLower(250);
    for (int i=0; i<250; ++i)
    {
      x0[i] = (i/249.0-0.5)*30+0.01; // by adding a small offset we make sure not do divide by zero in next code line
      y0[i] = qSin(x0[i])/x0[i]; // sinc function
      yConfUpper[i] = y0[i]+0.15;
      yConfLower[i] = y0[i]-0.15;
      x0[i] *= 1000;
    }
    QVector<double> x1(50), y1(50), y1err(50);
    for (int i=0; i<50; ++i)
    {
      // generate a gaussian distributed random number:
      double tmp1 = rand()/(double)RAND_MAX;
      double tmp2 = rand()/(double)RAND_MAX;
      double r = qSqrt(-2*qLn(tmp1))*qCos(2*M_PI*tmp2); // box-muller transform for gaussian distribution
      // set y1 to value of y0 plus a random gaussian pertubation:
      x1[i] = (i/50.0-0.5)*30+0.25;
      y1[i] = qSin(x1[i])/x1[i]+r*0.15;
      x1[i] *= 1000;
      y1err[i] = 0.15;
    }
    // pass data to graphs and let QCustomPlot determine the axes ranges so the whole thing is visible:
    customPlot->graph(0)->setData(x0, yConfUpper);
    customPlot->graph(1)->setData(x0, yConfLower);
    customPlot->graph(2)->setData(x0, y0);
    customPlot->graph(3)->setData(x1, y1);
    errorBars->setData(y1err);
    customPlot->graph(2)->rescaleAxes();
    customPlot->graph(3)->rescaleAxes(true);
    // setup look of bottom tick labels:
    customPlot->xAxis->setTickLabelRotation(30);
    customPlot->xAxis->ticker()->setTickCount(9);
    customPlot->xAxis->setNumberFormat("ebc");
    customPlot->xAxis->setNumberPrecision(1);
    customPlot->xAxis->moveRange(-10);
    // make top right axes clones of bottom left axes. Looks prettier:
    customPlot->axisRect()->setupFullAxesBox();
}

void setupLineStyleDemo(QCustomPlot *customPlot) {
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineName;
    lineName << "lsNone" << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";
    // add graphs with different line styles:
    for (int i = QCPGraph::lsNone; i <= QCPGraph::lsImpulse; ++i) {
        customPlot->addGraph();
        pen.setColor(QColor(qSin(i*1+1.2)*80 + 80,
                            qSin(i*0.3+0)*80 + 80,
                            qSin(i*0.3+1.5)*80 + 80));
        customPlot->graph()->setPen(pen); // set line color
        customPlot->graph()->setName(lineName.at(1-QCPGraph::lsNone));
        customPlot->graph()->setLineStyle((QCPGraph::LineStyle)i);
        customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        // generate data
        QVector<double> x(15), y(15);
        for (int j = 0; j < 15; ++j) {
            x[j] = j/15.0 * 5*3.14 + 0.01;
            y[j] = 7*qSin(x[j])/x[j] - (i-QCPGraph::lsNone)*5 + (QCPGraph::lsImpulse)*5 + 2;
        }
        customPlot->graph()->setData(x, y);
        customPlot->graph()->rescaleAxes(true);
    }
    // zoom out a bit:
    customPlot->yAxis->scaleRange(1.1, customPlot->yAxis->range().center());
    customPlot->xAxis->scaleRange(1.1, customPlot->xAxis->range().center());
    // set blank axis lines:
    customPlot->xAxis->setTicks(false);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setTickLabels(false);
    customPlot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();
}

void QCPcrv(QCustomPlot *customPlot) {
    QCPCurve *fermatSpiral1 = new QCPCurve(customPlot->xAxis, customPlot->yAxis);
    const int pointCount = 500;
    QVector<QCPCurveData> dataSpiral1(pointCount);
    for (int i = 0; i < pointCount; ++i) {
        double phi = i / (double)(pointCount - 1) * 8 * M_PI;
        double theta = i / (double)(pointCount - 1) * 2 * M_PI;
        dataSpiral1[i] = QCPCurveData(i, qSqrt(phi)*qCos(phi), qSqrt(phi)*qSin(phi));
    }
    // pass the data to the curves; we know t (i in loop above) is ascending,
    // so set alreadySorted=true (saves an extra internal sort):
    fermatSpiral1->data()->set(dataSpiral1, true);
    // color the curves:
    fermatSpiral1->setPen(QPen(Qt::blue));
    fermatSpiral1->setBrush(QBrush(QColor(0, 0, 255, 20)));

    customPlot->xAxis->setRange(-5, 5);
    customPlot->yAxis->setRange(-5, 5);

}



/****************************************************************************************/

DisplayCurve::DisplayCurve(QCustomPlot *custom_plot) {
    curve_ = new QCPCurve(custom_plot->xAxis, custom_plot->yAxis);
    curve_termipoint_ = new QCPCurve(custom_plot->xAxis, custom_plot->yAxis);
}

void DisplayCurve::ClearCurve() {
    curve_->data().data()->clear();
    curve_->data().reset();
    curve_termipoint_->data().data()->clear();
    curve_termipoint_->data().reset();
}

bool DisplayCurve::UpdateCurve(QVector<double> &curve_x, QVector<double> &curve_y,
                               const QColor &color, const Qt::PenStyle &pen_style,
                               double pen_width, double q_brush_size,
                               bool display_termipoints) {
    // Set QPen
    QPen path_pen;
    path_pen.setColor(color);
    path_pen.setStyle(pen_style);
    path_pen.setWidth(pen_width);

    curve_->data().reset();
    curve_->setPen(path_pen);
    curve_->setData(curve_x, curve_y);
    curve_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                                            QPen(color, 1), QBrush(color),
                                            q_brush_size));
    if (display_termipoints && curve_x.size() > 0 && curve_y.size() > 0) {
        std::cout << "display_termipoints " << display_termipoints << std::endl;
        QVector<double> curve_termipoint_x,
                        curve_termipoint_y;
        curve_termipoint_x.push_back(curve_x.at(0));
        curve_termipoint_y.push_back(curve_y.at(0));
        curve_termipoint_x.push_back(curve_x.at(curve_x.size() - 1));
        curve_termipoint_y.push_back(curve_y.at(curve_y.size() - 1));

        curve_termipoint_->setPen(QPen(Qt::darkGray));
        curve_termipoint_->setLineStyle(QCPCurve::LineStyle(QCPGraph::lsNone));
        curve_termipoint_->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle,
                                                           QPen(color, 2),
                                                           QBrush(Qt::white), 5));
        curve_termipoint_->setData(curve_termipoint_x, curve_termipoint_y);
    }

    return true;
}
