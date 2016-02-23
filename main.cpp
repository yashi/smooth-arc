#include <QtGui>

#include "rasterwindow.h"

class SmoothArc : public RasterWindow
{
public:
    SmoothArc();

protected:
    void timerEvent(QTimerEvent *) Q_DECL_OVERRIDE;
    void render(QPainter *p) Q_DECL_OVERRIDE;

private:
    int m_timerId;
    int m_valueTimerId;
    int m_value;
};

SmoothArc::SmoothArc()
{
    setTitle("Smooth Arc");
    resize(200, 200);

    m_timerId = startTimer(33);
    m_valueTimerId = startTimer(100);
    m_value = 50;
}

void SmoothArc::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        renderLater();
    if (event->timerId() == m_valueTimerId) {
        m_value = m_value + (qrand() % 11 - 5);
        if (m_value > 100) m_value = 100;
        if (m_value < 0) m_value = 0;
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
    p->drawArc(rect, 90*16, (360*(m_value/100.0))*16);
}

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);
    SmoothArc arc;
    arc.show();
    return app.exec();
}
