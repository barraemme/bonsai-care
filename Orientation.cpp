#include <QOrientationSensor>
#include "Orientation.h"

QTM_USE_NAMESPACE

    Orientation::Orientation(QObject *parent) :
    QObject(parent), m_state("Portrait")
{
  m_sensor = new QOrientationSensor(this);
  connect(m_sensor, SIGNAL(readingChanged()), SLOT(onReadingChanged()));
  m_sensor->start();
}

Orientation::~Orientation() {
  delete m_sensor;
}

void Orientation::onReadingChanged()
{
  QOrientationReading* reading = m_sensor->reading();
  switch(reading->orientation())
  {
  case QOrientationReading::TopUp:
    m_state = "Landscape";
    emit orientationChanged();
    break;
  case QOrientationReading::TopDown:
    m_state = "LandscapeInverted";
    emit orientationChanged();
    break;
  case QOrientationReading::LeftUp:
    m_state = "Portrait";
    emit orientationChanged();
    break;
  case QOrientationReading::RightUp:
    m_state = "PortraitInverted";
    emit orientationChanged();
  default:
    break;
  }
}
