#ifndef WEBGUIINPUTCONTROLLER_H
#define WEBGUIINPUTCONTROLLER_H

#include "httprequesthandler.h"
#include "template.h"

using namespace stefanfrings;

class WebGuiInputController
{
public:
    WebGuiInputController();
    virtual ~WebGuiInputController();
};

class Button : public WebGuiInputController
{
public:
    Button(QByteArray GuiState, QByteArray GuiVarName, Template* SiteTemplate, bool GpioState);
    virtual ~Button();

    virtual bool out();

protected:
    QByteArray GuiState_;
    QByteArray GuiVarName_;
    Template* SiteTemplate_;
    bool GpioState_;
};

class Slider : public WebGuiInputController
{
public:
    Slider(QByteArray GuiState, QByteArray GuiValue, QByteArray GuiVarName, Template* SiteTemplate, int GpioState);
    virtual ~Slider();

    virtual int out();

protected:
    QByteArray GuiState_;
    QByteArray GuiValue_;
    QByteArray GuiVarName_;
    Template* SiteTemplate_;
    int GpioState_;
};

#endif // WEBGUIINPUTCONTROLLER_H
