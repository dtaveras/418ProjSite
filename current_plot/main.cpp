#include <QApplication>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QThread>
#include <QObject>
#include <QDebug>
#include <QFont>
#include <QMetaType>

#include "QCustomGraph/qcustomplotwidget.h"
#include "arduinoWorker.h"


#define WIND_WIDTH 800
#define WIND_HEIGHT 600

int main(int argc, char** argv){
  QApplication app(argc, argv);
  QWidget* window = new QWidget;
  
  window->setWindowTitle("Real Time Tegra K1 Current Plot");
  window->setMinimumSize(WIND_WIDTH, WIND_HEIGHT);
  window->setStyleSheet("background-color: #353439;");
  
  //Initialize widgets and layouts
  QCustomPlotWidget* customPlot = new QCustomPlotWidget;
  customPlot->addGraph();
  customPlot->addGraph();

  QPen pen;
  pen.setColor(QColor(2,97,37));
  pen.setWidth(2);
  //pen.setStyle(Qt::DotLine);
  customPlot->graph(0)->setPen(pen);
  customPlot->graph(0)->setBrush(QBrush(QColor(0, 255, 0, 20)));

  pen.setColor(QColor(0,0,100));
  pen.setWidth(2);
  //pen.setStyle(Qt::DotLine);
  customPlot->graph(1)->setPen(pen);
  customPlot->graph(1)->setBrush(QBrush(QColor(0, 0, 255, 20)));

  customPlot->yAxis->setLabel(QString::fromUtf8("Current (mA)"));
  customPlot->xAxis->setLabel(QString::fromUtf8("Time (ms)"));

  customPlot->xAxis->setLabelFont(QFont("Courier", 20, QFont::Bold));
  customPlot->yAxis->setLabelFont(QFont("Courier", 20, QFont::Bold));
  
  customPlot->yAxis->setNumberFormat("f");
  customPlot->yAxis->setNumberPrecision(3);
  //customPlot->xAxis->setTickLabels(false);
  customPlot->axisRect()->setupFullAxesBox();

  customPlot->yAxis->setAutoTickStep(false);
  customPlot->yAxis->setAutoSubTicks(false);
  customPlot->yAxis->setTickStep(100);
  customPlot->yAxis->setSubTickCount(5);
  customPlot->yAxis->setRange(0,1000);
  
  customPlot->setInteractions(QCP::iRangeDrag | QCP::iSelectPlottables);

  //customPlot->setInteractions(QCP::iSelectPlottables);
  //customPlot->graph(0)->setAdaptiveSampling(true);
  //customPlot->setNoAntialiasingOnDrag(true);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(customPlot);
  window->setLayout(mainLayout);

  QThread* listenerThread = new QThread;
  ArduinoWorker* worker = new ArduinoWorker;
  //Needed so that a new thread is actually launched
  worker->moveToThread(listenerThread);

  //Setup connections/Communication between objects
  QObject::connect(listenerThread, SIGNAL(started()), worker, SLOT(startListening()));
  QObject::connect(worker, SIGNAL(addNewDataY(double)), customPlot, 
		   SLOT(addGraphDataY(double)));
  QObject::connect(customPlot, SIGNAL(mouseMove(QMouseEvent*)), worker, 
		   SLOT(receivedMouse(QMouseEvent*)));
  listenerThread->start();
  //window->show();
  window->showMaximized();

  return app.exec();
}
