#include "gpiocontroller.h"
#include <QColor>
#include <QTimer>

#include "customdatatypes.h"
#include "pigpiod_if2.h"

GpioController::GpioController(GuiParameters& guiParameters, QObject *parent) :
    QObject(parent),
    guiParametersInt(guiParameters)
{

    // init timer
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(TimerLoop()));
    timer->start(200);

    // start communication with gpio daemon and set pin modes

    pi = pigpio_start(NULL, NULL);
}

GpioController::~GpioController()
{
    // reset pwm outputs
    set_PWM_dutycycle(pi, GPIO_Red, 0);
    set_PWM_dutycycle(pi, GPIO_Green, 0);
    set_PWM_dutycycle(pi, GPIO_Blue, 0);

    // reset lightning output
    gpio_write(pi, GPIO_Light, false);

    // reset wall plug left output
    gpio_write(pi, GPIO_WallPlugL, false);

    // reset wall plug right output
    gpio_write(pi, GPIO_WallPlugR, false);

    // reset info sign output
    gpio_write(pi, GPIO_Sign, false);

    // stop communication with gpio daemon
    pigpio_stop(pi);
}


// get RGB color from HSV
//-------------------------------------------------------------------

void GpioController::GetRGB()
{

    // color selection mode
    if ( guiParametersInt.ColorSelectionOnOff )
    {
        ColorHSV.setHsv(guiParametersInt.HSV_hue, guiParametersInt.HSV_saturation, guiParametersInt.HSV_value, 255);
    }

    if ( guiParametersInt.ColorChangeOnOff )
    {
        if ( Hue_Change <= 359.0 )
        {
            Hue_Change = Hue_Change + (0.02 * guiParametersInt.Speed);
        }
        else
        {
            Hue_Change = 0.0;
        }
        ColorHSV.setHsv(Hue_Change, 255, 255, 255);
    }

    // convert HSV in RGB
    ColorRGB = ColorHSV.toRgb();

}


// slot to update gpio's
//-------------------------------------------------------------------

void GpioController::UpdateOutputs()
{
    // set neonflex outputs
    if (guiParametersInt.NeonflexOnOff)
    {
        set_PWM_dutycycle(pi, GPIO_Red, ( 255 - ColorRGB.red()));
        set_PWM_dutycycle(pi, GPIO_Green, ( 255 - ColorRGB.green()));
        set_PWM_dutycycle(pi, GPIO_Blue, ( 255 - ColorRGB.blue()));
    }
    else
    {
        set_PWM_dutycycle(pi, GPIO_Red, 255);
        set_PWM_dutycycle(pi, GPIO_Green, 255);
        set_PWM_dutycycle(pi, GPIO_Blue, 255);
    }


    // set lightning output
    gpio_write(pi, GPIO_Light, guiParametersInt.LightingOnOff);

    // set wall plug left output
    gpio_write(pi, GPIO_WallPlugL, guiParametersInt.WallplugLOnOff);

    // set wall plug right output
    gpio_write(pi, GPIO_WallPlugR, guiParametersInt.WallplugROnOff);

    // set info sign output
    gpio_write(pi, GPIO_Sign, guiParametersInt.SignOnOff);
}


// main loop [200ms cycle time]
//-------------------------------------------------------------------
void GpioController::TimerLoop()
{
    GetRGB();
    UpdateOutputs();
}
