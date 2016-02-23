#include <QtGui>

#include "rasterwindow.h"
#include "smootharc.h"

SmoothArc::SmoothArc()
{
    setTitle("Smooth Arc");
    resize(200, 200);

    m_value = 180 * 16;
    m_valueTimerId = startTimer(100);
    m_animation.setTargetObject(this);
    m_animation.setPropertyName("value");
    m_animation.setEasingCurve(QEasingCurve::OutCirc);
    m_animation.setDuration(500);
}

int SmoothArc::value() const
{
    return m_value;
}

void SmoothArc::setValue(int value)
{
    m_value = value;
    renderLater();
}

void SmoothArc::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_valueTimerId) {
        int newValue = m_value + ((qrand() % 21 - 10) * 16);
        if (m_value > (360 * 16)) m_value = (360 * 16);
        if (m_value < 0) m_value = 0;
        if (m_animation.state() == QPropertyAnimation::Running)
            m_animation.stop();
        m_animation.setStartValue(m_value);
        m_animation.setEndValue(newValue);
        m_animation.start();
    }
}

void SmoothArc::render(QPainter *p)
{
    p->setRenderHint(QPainter::Antialiasing);
    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    QRectF rect(10, 10, 180, 180);
    QPen pen = p->pen();
    pen.setWidth(10);
    p->setPen(pen);
    p->drawArc(rect, 90 * 16, m_value);
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    SmoothArc arc;
    arc.show();
    return app.exec();
}
