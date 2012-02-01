#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <QObject>

namespace QtMobility {
class QOrientationSensor;
};

class Orientation : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QString state READ state NOTIFY orientationChanged)

public:
  explicit Orientation(QObject *parent = 0);
  ~Orientation();
  inline QString state() const { return m_state; }

signals:
  void orientationChanged();

private slots:
  void onReadingChanged();

private:
  QString m_state;
  QtMobility::QOrientationSensor* m_sensor;

};

#endif // ORIENTATION_H
