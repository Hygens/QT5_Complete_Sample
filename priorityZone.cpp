#ifndef __PRIORITY_ZONE__
#define __PRIORITY_ZONE__

#include "priorityZone.h"

PriorityZone::PriorityZone(double availableVolume, int priority, QObject *parent)
    : QObject(parent), m_availableVolume(availableVolume), m_priority(priority)
{    
}

double PriorityZone::getAvailableVolume()
{
  return m_availableVolume;
}

int PriorityZone::getPriority()
{
  return m_priority;
}

#endif /* __PRIORITY_ZONE__ */
