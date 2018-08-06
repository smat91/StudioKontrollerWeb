#include "webguiinputcontroller.h"

WebGuiInputController::WebGuiInputController()
{
}

WebGuiInputController::~WebGuiInputController()
{
}

Button::Button(QByteArray inGuiState, QByteArray GuiVarName, Template* SiteTemplate, bool GpioState)
    :GuiState_(inGuiState), GuiVarName_(GuiVarName), SiteTemplate_(SiteTemplate), GpioState_(GpioState)
{
}

Button::~Button()
{
}

bool Button::out()
{
    // process value
    if (GuiState_ == "true") {
        if (GpioState_ == false) {
            GpioState_ = true;
            SiteTemplate_->setVariable(GuiVarName_,"true");
        }
        else {
            GpioState_ = false;
            SiteTemplate_->setVariable(GuiVarName_,"false");
        }
    }
    else {
        if (GpioState_ == false) {
            SiteTemplate_->setVariable(GuiVarName_,"false");
        }
        else {
            SiteTemplate_->setVariable(GuiVarName_,"true");
        }
    }

    return GpioState_;
}


Slider::Slider(QByteArray inGuiState, QByteArray GuiValue, QByteArray GuiVarName, Template* SiteTemplate, int GpioState)
    :GuiState_(inGuiState), GuiValue_(GuiValue), GuiVarName_(GuiVarName), SiteTemplate_(SiteTemplate), GpioState_(GpioState)
{
}

Slider::~Slider()
{
}

int Slider::out()
{
    // process value
    if (GuiState_ == "true") {
        GpioState_ = QString(GuiValue_).toInt();
        QString valValue = QString::number(GpioState_);
        SiteTemplate_->setVariable(GuiVarName_, valValue );
    }
    else {
        QString valValue = QString::number(GpioState_);
        SiteTemplate_->setVariable(GuiVarName_, valValue);
    }

    return GpioState_;
}
