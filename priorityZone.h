#ifndef PRIORITYZONE_H
#define PRIORITYZONE_H
#include <QObject>

class PriorityZone : public QObject
{
    Q_OBJECT
protected:
    double m_availableVolume;
    int m_priority;
public:
    PriorityZone(double availableVolume, int priority, QObject *parent = 0);
    double getAvailableVolume();
    int getPriority();
};

#endif // PRIORITYZONE_H
