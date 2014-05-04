#include "qcustomplotwidget.h"
#include <QDebug>

#define DATA_SAVED 5
#define DELTA 0.02
#define NUM_POINTS 300
#define OFFSET 2
#define LIVE 1

QCustomPlotWidget::QCustomPlotWidget(){
  this->cursor_xpos = 0;
  this->dragging = 0;
  this->cur_time = 0.0;
  this->started = 0;
}


void QCustomPlotWidget::mousePressWidgetEvent(QMouseEvent *event){
  if (event->button() == Qt::LeftButton && this->selectedGraphs().count()){
    this->axisRect()->setRangeDrag(0);
    if(!LIVE)
      this->dragging = 1;
  }
}

void QCustomPlotWidget::mouseReleaseWidgetEvent(QMouseEvent *event){
  if(this->dragging == 1){
    this->axisRect()->setRangeDrag(Qt::Horizontal | Qt::Vertical);
    this->dragging = 0;
  }
}

void QCustomPlotWidget::mouseMoveWidgetEvent(QMouseEvent *event){
  if(this->selectedGraphs().count() && this->dragging){

    QCPGraph* graph = this->selectedGraphs()[0];
    QCPDataMap* dataMap = graph->data();

    if(this->cursor_xpos - event->x() > 0){
      QCPDataMap::iterator i;
      for (i = dataMap->begin(); i != dataMap->end(); ++i){
	QCPData tmpdata = i.value();
	dataMap->remove(tmpdata.key);
	graph->addData(tmpdata.key-double(DELTA),tmpdata.value);
      }
    }
    else if(this->cursor_xpos - event->x() < 0){
      QCPDataMap::iterator i;
      for (i = dataMap->begin(); i != dataMap->end(); ++i){
	QCPData tmpdata = i.value();
	dataMap->remove(tmpdata.key);
	graph->addData(tmpdata.key+double(DELTA),tmpdata.value);
      }
    }
    this->replot();
  }
  this->cursor_xpos = event->x();
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
  QCPGraph* c_graph;
  if(LIVE)
    c_graph = this->graph(0);
  else{

    if(this->graph(0)->data()->count() < NUM_POINTS) {
      c_graph = this->graph(0);
    }
    else if(this->graph(1)->data()->count() < NUM_POINTS){
      c_graph = this->graph(1);
    }
    else{
      return;
    }
  }

  //qDebug() << "add Graph Y data";
  double key = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;
  static double lastPointKey = 0;
  double time_elapsed = key-lastPointKey;
  if(time_elapsed > 0.016) // at most add point every 16 ms
    {
      if(this->started == 0){
	lastPointKey = key;
	this->started = 1;
	return;
      }
      qDebug() << cur_time;
      //qDebug() << time_elapsed;
      //qDebug() << 1.0/(key-lastPointKey);
      if(c_graph == this->graph(1))
	c_graph->addData((cur_time-8.0)*1000.0, y);
      else
	c_graph->addData(cur_time*1000.0, y);

      if(LIVE)
	c_graph->removeDataBefore((cur_time-10)*1000.0);

      if(c_graph == this->graph(0))
	c_graph->rescaleKeyAxis();

      lastPointKey = key;//save key
      cur_time += time_elapsed;
    }
  //qDebug() << c_graph->data()->count();
  if(LIVE)
    this->xAxis->setRange(cur_time, 10, Qt::AlignRight);
  
  this->replot(); //Update Plot
}
