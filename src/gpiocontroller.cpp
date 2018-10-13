#include "gpiocontroller.h"
#include <QColor>
#include <QTimer>

#include "customdatatypes.h"
#include "pigpiod_if2.h"

GpioController::GpioController(guiParameters& guiPar, QObject *parent) :
    QObject(parent),
    guiPar_(guiPar),
    colorHSV(Qt::white),
    colorRGB(Qt::white),
    hueChange(0.0),
    pi(0)
{
    // init timer
    QTimer* timer {new QTimer(this)};
    connect(timer, SIGNAL(timeout()), this, SLOT(timerLoop()));
    timer->start(200);

    // start communication with gpio daemon and set pin modes
    char ip[] {"192.168.0.3"};
    pi = pigpio_start(ip, NULL);

}

GpioController::~GpioController()
{
    // reset pwm outputs
    set_PWM_dutycycle(pi, GPIO_RED, 0);
    set_PWM_dutycycle(pi, GPIO_GREEN, 0);
    set_PWM_dutycycle(pi, GPIO_BLUE, 0);

    // reset lightning output
    gpio_write(pi, GPIO_LIGHT, false);

    // reset wall plug left output
    gpio_write(pi, GPIO_WALL_PLUG_LEFT, false);

    // reset wall plug right output
    gpio_write(pi, GPIO_WALL_PLUG_RIGHT, false);

    // reset info sign output
    gpio_write(pi, GPIO_SIGN, false);

    // stop communication with gpio daemon
    pigpio_stop(pi);
}


// get RGB color from HSV
//-------------------------------------------------------------------

void GpioController::getRGB()
{

    // color selection mode
    if (guiPar_.colorSelectionOnOff)
    {
        colorHSV.setHsv(guiPar_.hsvHue, guiPar_.hsvSaturation, guiPar_.hsvValue, 255);
    }

    // color change mode
    if (guiPar_.colorChangeOnOff)
    {
        if (hueChange <= 1.0)
        {
            hueChange = hueChange + (0.0001 * (guiPar_.speed));
        }
        else
        {
            hueChange = 0.0;
        }
        colorHSV.setHsvF(hueChange, 1.0, 1.0, 1.0);
    }

    // convert HSV in RGB
    colorRGB = colorHSV.toRgb();
}


// slot to update gpio's
//-------------------------------------------------------------------

void GpioController::updateOutputs()
{
    // set neonflex outputs
    if (guiPar_.neonFlexOnOff)
    {
        set_PWM_dutycycle(pi, GPIO_RED, ( 255 - colorRGB.red()));
        set_PWM_dutycycle(pi, GPIO_GREEN, ( 255 - colorRGB.green()));
        set_PWM_dutycycle(pi, GPIO_BLUE, ( 255 - colorRGB.blue()));
    }
    else
    {
        set_PWM_dutycycle(pi, GPIO_RED, 255);
        set_PWM_dutycycle(pi, GPIO_GREEN, 255);
        set_PWM_dutycycle(pi, GPIO_BLUE, 255);
    }


    // set lightning output
    gpio_write(pi, GPIO_LIGHT, guiPar_.lightingOnOff);

    // set wall plug left output
    gpio_write(pi, GPIO_WALL_PLUG_LEFT, guiPar_.wallPlugLeftOnOff);

    // set wall plug right output
    gpio_write(pi, GPIO_WALL_PLUG_RIGHT, guiPar_.wallPlugRightOnOff);

    // set info sign output
    gpio_write(pi, GPIO_SIGN, guiPar_.signOnOff);
}


// main loop [200ms cycle time]
//-------------------------------------------------------------------
void GpioController::timerLoop()
{
    getRGB();
    updateOutputs();
}
