#ifndef QCUSTOMPLOTWIDGET
#define QCUSTOMPLOTWIDGET

#include "qcustomplot.h"
#include <QVector>

typedef QVector<double> dataVector;

class QCustomPlotWidget : public QCustomPlot
{
  Q_OBJECT
public:
  QCustomPlotWidget();
  double xmax;
  double ymax;

public slots:
  void updateGraphData(dataVector x, dataVector y);
  void addGraphData(double x, double y);
  void addGraphDataY(double y);
};

#endif
