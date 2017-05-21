#ifndef PRIORITYUTILS_H
#define PRIORITYUTILS_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "priorityZone.h"

using VectorOfPriorityZones = std::vector<PriorityZone*>;

class PriorityUtils : public QObject
{
    Q_OBJECT
public:
    PriorityUtils(QObject *parent = 0);

    /** @brief
    * Retorna o volume de água disponível em cada zona de prioridade
    * @param pArray é um vetor contendo as prioridades de cada zona
    * @param vArray é o limite superior de cada zona
    * @param minimumVolume é o volume mínimo do reservatório
    * @param maximumVolume é o volume máximo do reservatório
    * @param currentVolume é o volume atual do reservatório
    */
    VectorOfPriorityZones zonesAvailableSupply(std::vector<int> pArray,
                            std::vector<double> vArray,
                            double minimumVolume, double maximumVolume, double currentVolume);
};

#endif // PRIORITYUTILS_H
