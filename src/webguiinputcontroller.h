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
    Button(QByteArray guiState, QByteArray guiVarName, Template* siteTemplate, bool gpioState);
    virtual ~Button();

    virtual bool out();

protected:
    QByteArray guiState_;
    QByteArray guiVarName_;
    Template* siteTemplate_;
    bool gpioState_;
};

class Slider : public WebGuiInputController
{
public:
    Slider(QByteArray guiState, QByteArray guiValue, QByteArray guiVarName, Template* siteTemplate, int gpioState);
    virtual ~Slider();

    virtual int out();

protected:
    QByteArray guiState_;
    QByteArray guiValue_;
    QByteArray guiVarName_;
    Template* siteTemplate_;
    int gpioState_;
};

#endif // WEBGUIINPUTCONTROLLER_H
