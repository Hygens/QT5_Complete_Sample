#include "reservatorio.h"

Reservatorio::Reservatorio(int id, double minimumVolume, double availableVolume,
                           double maximumVolume, QObject *parent)
    : QObject(parent),id_reservatorio(id),m_minimumVolume(minimumVolume),
      m_availableVolume(availableVolume),m_maximumVolume(maximumVolume)
{

}

double Reservatorio::getAvailableVolume()
{
    return this->m_availableVolume;
}

double Reservatorio::getMinimumVolume()
{
    return this->m_minimumVolume;
}

double Reservatorio::getMaximunVolume()
{
    return this->m_maximumVolume;
}




