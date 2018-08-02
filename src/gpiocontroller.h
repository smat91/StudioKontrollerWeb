#ifndef GPIOCONTROLLER_H
#define GPIOCONTROLLER_H

#define GPIO_Red 17
#define GPIO_Green 27
#define GPIO_Blue 22
#define GPIO_Light 5
#define GPIO_WallPlugL 6
#define GPIO_WallPlugR 13
#define GPIO_Sign 19

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
    explicit GpioController(GuiParameters& guiParameters, QObject *parent = 0);
    ~GpioController();

    int pi;

    GuiParameters& guiParametersInt;

    float Hue_Change;

    QColor ColorHSV = Qt::white;
    QColor ColorRGB = Qt::white;

public slots:
    void TimerLoop();


private:

    void GetRGB();

    void UpdateOutputs();
};

#endif // GPIOCONTROLLER_H
