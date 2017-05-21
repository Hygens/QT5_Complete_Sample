#ifndef RESERVATORIO_H
#define RESERVATORIO_H

#include <QObject>

class Reservatorio : public QObject
{
    Q_OBJECT
protected:
    double m_availableVolume;
    double m_minimumVolume;
    double m_maximumVolume;

public:
    explicit Reservatorio(int id, double minimumVolume,
                          double availableVolume, double maximumVolume,
                          QObject *parent = 0);
    double getAvailableVolume();
    double getMinimumVolume();
    double getMaximunVolume();

signals:

public slots:

private:
    int id_reservatorio;
};

#endif // RESERVATORIO_H
