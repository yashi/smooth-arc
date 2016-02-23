#ifndef SMOOTHARC_H
#define SMOOTHARC_H

#include "rasterwindow.h"

class SmoothArc : public RasterWindow
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)

public:
    SmoothArc();
    int value() const;
    void setValue(int value);

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;
    void render(QPainter *p) Q_DECL_OVERRIDE;

private:
    int m_value;
    int m_valueTimerId;
    QPropertyAnimation m_animation;
};

#endif
