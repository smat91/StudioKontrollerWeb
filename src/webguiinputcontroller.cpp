#include "webguiinputcontroller.h"

WebGuiInputController::WebGuiInputController()
{
}

WebGuiInputController::~WebGuiInputController()
{
}

Button::Button(QByteArray guiState, QByteArray guiVarName, Template* siteTemplate, bool gpioState):
    guiState_(guiState),
    guiVarName_(guiVarName),
    siteTemplate_(siteTemplate),
    gpioState_(gpioState)
{
}

Button::~Button()
{
}

bool Button::out()
{
    // process value
    if (guiState_ == "true")
    {
        if (gpioState_ == false)
        {
            gpioState_ = true;
            siteTemplate_->setVariable(guiVarName_,"true");
        }
        else
        {
            gpioState_ = false;
            siteTemplate_->setVariable(guiVarName_,"false");
        }
    }
    else
    {
        if (gpioState_ == false)
        {
            siteTemplate_->setVariable(guiVarName_,"false");
        }
        else
        {
            siteTemplate_->setVariable(guiVarName_,"true");
        }
    }

    return gpioState_;
}


Slider::Slider(QByteArray guiState, QByteArray guiValue, QByteArray guiVarName, Template* siteTemplate, int gpioState):
    guiState_(guiState),
    guiValue_(guiValue),
    guiVarName_(guiVarName),
    siteTemplate_(siteTemplate),
    gpioState_(gpioState)
{
}

Slider::~Slider()
{
}

int Slider::out()
{
    // process value
    if (guiState_ == "true") {
        gpioState_ = QString(guiValue_).toInt();
        QString valValue {QString::number(gpioState_)};
        siteTemplate_->setVariable(guiVarName_, valValue );
    }
    else {
        QString valValue {QString::number(gpioState_)};
        siteTemplate_->setVariable(guiVarName_, valValue);
    }

    return gpioState_;
}
