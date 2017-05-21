#ifndef LINEEDITICONIZED_H
#define LINEEDITICONIZED_H

#include <QLineEdit>
#include <QIcon>

class LineEditIconized : public QLineEdit
{
    Q_OBJECT

public:
    LineEditIconized(const QIcon icon, QWidget *parent = Q_NULLPTR);
    ~LineEditIconized();
    void setIcon(QIcon icon);
protected:
    virtual void paintEvent(QPaintEvent *event);
private:
    QIcon m_icon;
};

#endif // LINEEDITICONIZED_H
