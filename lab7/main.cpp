#include <QtGui>
#include "rasterwindow.h"

class SecondsWindow : public RasterWindow
{
public:
    SecondsWindow();

protected:
    void timerEvent(QTimerEvent *) override;
    void render(QPainter *p) override;

private:
    int m_timerId;
};

SecondsWindow::SecondsWindow()
{
    setTitle("Seconds");
    resize(200, 200);

    m_timerId = startTimer(50);
}

void SecondsWindow::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == m_timerId)
        renderLater();
}

void SecondsWindow::render(QPainter *p)
{
    static const QPoint seconds[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -90)
    };

    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondsColor(255,0,0,128);

    p->setRenderHint(QPainter::Antialiasing);
    p->translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    p->scale(side / 200.0, side / 200.0);

    QTime time = QTime::currentTime();

    p->setPen(hourColor);

    for (int i = 0; i < 12; ++i) {
        p->drawLine(88, 0, 96, 0);
        p->rotate(30.0);
    }

    p->setPen(minuteColor);

    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            p->drawLine(92, 0, 96, 0);
        p->rotate(6.0);
    }

    p->setPen(Qt::NoPen);
    p->setBrush(secondsColor);

    p->save();
    p->rotate(6.0 * (time.second() + time.msec() / 1000.0));
    p->drawConvexPolygon(seconds, 3);
    p->restore();
}

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SecondsWindow w;
    w.show();
    return app.exec();
}
