#ifndef QCUSTOMPLOTWIDGET
#define QCUSTOMPLOTWIDGET

#include "qcustomplot.h"
#include <QVector>

typedef QVector<double> dataVector;

class QCustomPlotWidget : public QCustomPlot
{
  Q_OBJECT
private:
  int cursor_xpos;
  int dragging;
  int started;
protected:
  virtual void mousePressWidgetEvent(QMouseEvent *event);
  virtual void mouseMoveWidgetEvent(QMouseEvent *event);
  virtual void mouseReleaseWidgetEvent(QMouseEvent *event);
public:
  QCustomPlotWidget();
  double xmax;
  double ymax;
  double cur_time;
public slots:
  void updateGraphData(dataVector x, dataVector y);
  void addGraphData(double x, double y);
  void addGraphDataY(double y);
  void savePlot(bool state);
};

#endif
