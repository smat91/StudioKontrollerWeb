#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

// defines for used gpio pins
#define GPIO_RED 17
#define GPIO_GREEN 27
#define GPIO_BLUE 22
#define GPIO_LIGHT 5
#define GPIO_WALL_PLUG_LEFT 6
#define GPIO_WALL_PLUG_RIGHT 13
#define GPIO_SIGN 19

// includes
//-------------------------------------------------------------------

#include <QTimer>
#include <QColor>
#include <QObject>

#include "customdatatypes.h"
#include "pigpiod_if2.h"

class GpioController : public QObject
{
    Q_OBJECT
public:
    explicit GpioController(guiParameters& guiPar, QObject* parent = nullptr);
    ~GpioController();

    guiParameters& guiPar_;

    QColor colorHSV;
    QColor colorRGB;

    float hueChange;
    int pi;

public slots:
    void timerLoop();

private:

    void getRGB();
    void updateOutputs();
};

#endif // GPIOCONTROLLER_H
