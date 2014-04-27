#include "qcustomplotwidget.h"
#include <QDebug>

#define DATA_SAVED 30

QCustomPlotWidget::QCustomPlotWidget(){

}

void QCustomPlotWidget::updateGraphData(dataVector x, dataVector y){
  qDebug() << "updating the graph";
  this->graph(0)->setData(x, y);
  this->replot();
  this->xmax = 0;
  this->ymax = 0;
}

void QCustomPlotWidget::addGraphData(double x, double y){
  //qDebug() << "updating the graph";
  this->graph(0)->addData(x,y);
  this->replot();
}

void QCustomPlotWidget::addGraphDataY(double y){
  //qDebug() << "add Graph Y data";
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  static double lastPointKey = 0;
  if(key-lastPointKey > 0.0001) // at most add point every 1 ms
    {
      this->graph(0)->addData(key, y);

      this->graph(0)->removeDataBefore(key-DATA_SAVED);

      this->graph(0)->rescaleKeyAxis();
      this->graph(0)->rescaleValueAxis();

      lastPointKey = key;//save key
    }

  this->xAxis->setRange(key, DATA_SAVED, Qt::AlignRight);
  this->replot(); //Update Plot
}
