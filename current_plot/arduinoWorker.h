#include <QObject>
#include <QMouseEvent>

class ArduinoWorker : public QObject
{
  Q_OBJECT
public:
  ArduinoWorker();
  ~ArduinoWorker();
private:
public slots:
  void startListening();
private:
  int openPort(const char *path, int speed, int bits, int parity, int stops, int openFlags);
  int inputfd;
signals:
  void addNewData(double x, double y);
  void addNewDataY(double y);
public slots:
};
