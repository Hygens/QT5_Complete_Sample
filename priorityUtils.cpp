#ifndef __PRIORITY_UTILS__
#define __PRIORITY_UTILS__

#include "priorityUtils.h"

PriorityUtils::PriorityUtils(QObject *parent) : QObject(parent)
{

}

/** @brief
* Retorna o volume de água disponível em cada zona de prioridade
* @param pArray é um vetor contendo as prioridades de cada zona
* @param vArray é o limite superior de cada zona
* @param minimumVolume é o volume mínimo do reservatório
* @param maximumVolume é o volume máximo do reservatório
* @param currentVolume é o volume atual do reservatório
*/
VectorOfPriorityZones PriorityUtils::zonesAvailableSupply(std::vector<int> pArray,
                        std::vector<double> vArray,
                        double minimumVolume, double maximumVolume, double currentVolume) {
  std::vector<std::pair<int,double>> pairs;
  std::transform( pArray.begin(), pArray.end(), vArray.begin(),
         std::inserter( pairs, pairs.begin() ),
         [] (int i, double d) { return std::make_pair(i, d); });
  std::sort(pairs.begin(), pairs.end(), [](std::pair<int,double> &left, std::pair<int,double> &right) {
      return left.first < right.first;
  });
  VectorOfPriorityZones pZones(pArray.size());
  double slimit = 0.0;
  for(int i=0;i<pArray.size();i++) {
      if (slimit==0.0) {
        pZones[i] = new PriorityZone(pairs[i].second-minimumVolume,pairs[i].first);
      }      
      else {
        pZones[i] = new PriorityZone(pairs[i].second-slimit,pairs[i].first);
      }
      slimit = pairs[i].second;
  }
  return pZones;
}
#endif /** __PRIORITY_UTILS__ **/
