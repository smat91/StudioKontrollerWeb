#include "requestmapper.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "template.h"
#include "webguiinputcontroller.h"

DataTemplateControllerMainSite::DataTemplateControllerMainSite(QObject* parent):
    HttpRequestHandler(parent)
{
}

DataTemplateControllerMainSite::~DataTemplateControllerMainSite()
{
}

void DataTemplateControllerMainSite::service(guiParameters* guiPar, HttpRequest &request, HttpResponse &response)
{

    // get values form webui
    QByteArray inLighting {request.getParameter("inLighting")};
    QByteArray inInfoSign {request.getParameter("inInfoSign")};
    QByteArray inWallPlugLeft {request.getParameter("inWallPlugLeft")};
    QByteArray inWallPlugRight {request.getParameter("inWallPlugRight")};
    QByteArray inNeonFlexOnOff {request.getParameter("inNeonFlexOnOff")};
    QByteArray inColorSelectionOnOff {request.getParameter("inColorSelectionOnOff")};
    QByteArray inColorChangeOnOff {request.getParameter("inColorChangeOnOff")};
    QByteArray inShutdown {request.getParameter("inShutdownChange")};
    QByteArray inHue {request.getParameter("inHue")};
    QByteArray inSaturation {request.getParameter("inSaturation")};
    QByteArray inValue {request.getParameter("inValue")};
    QByteArray inSpeed {request.getParameter("inSpeed")};
    QByteArray inHueChange {request.getParameter("inHueChange")};
    QByteArray inSaturationChange {request.getParameter("inSaturationChange")};
    QByteArray inValueChange {request.getParameter("inValueChange")};
    QByteArray inSpeedChange {request.getParameter("inSpeedChange")};
    QByteArray inOn {request.getParameter("inOnChange")};
    QByteArray inOff {request.getParameter("inOffChange")};

    QByteArray language {request.getHeader("Accept-Language")};
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template mainSite {RequestMapper::templateCache->getTemplate("files/MainSite",language)};

    // all on
    if (inOn == "true")
    {
        guiPar->lightingOnOff       = true;     mainSite.setVariable("valLighting","true");
        guiPar->signOnOff           = true;     mainSite.setVariable("valInfoSign","true");
        guiPar->wallPlugLeftOnOff   = true;     mainSite.setVariable("valWallPlugLeft","true");
        guiPar->wallPlugRightOnOff  = true;     mainSite.setVariable("valWallPlugRight","true");
        guiPar->neonFlexOnOff       = true;     mainSite.setVariable("valNeonFlexOnOff","true");
        guiPar->colorSelectionOnOff = true;     mainSite.setVariable("valColorSelectionOnOff","true");
        guiPar->colorChangeOnOff    = false;    mainSite.setVariable("valColorChangeOnOff","false");
        guiPar->hsvHue              = 0;        mainSite.setVariable("valHue","0");
        guiPar->hsvSaturation       = 0;        mainSite.setVariable("valSaturation","0");
        guiPar->hsvValue            = 255;      mainSite.setVariable("valValue","255");
        guiPar->speed               = 0;        mainSite.setVariable("valSpeed","0");
    }

    // all off
    if (inOff == "true")
    {
        guiPar->lightingOnOff       = false;    mainSite.setVariable("valLighting","false");
        guiPar->signOnOff           = false;    mainSite.setVariable("valInfoSign","false");
        guiPar->wallPlugLeftOnOff   = false;    mainSite.setVariable("valWallPlugLeft","false");
        guiPar->wallPlugRightOnOff  = false;    mainSite.setVariable("valWallPlugRight","false");
        guiPar->neonFlexOnOff       = false;    mainSite.setVariable("valNeonFlexOnOff","false");
        guiPar->colorSelectionOnOff = false;    mainSite.setVariable("valColorSelectionOnOff","false");
        guiPar->colorChangeOnOff    = false;    mainSite.setVariable("valColorChangeOnOff","false");
        guiPar->hsvHue              = 0;        mainSite.setVariable("valHue","0");
        guiPar->hsvSaturation       = 0;        mainSite.setVariable("valSaturation","0");
        guiPar->hsvValue            = 0;        mainSite.setVariable("valValue","0");
        guiPar->speed               = 0;        mainSite.setVariable("valSpeed","0");
    }

    // process value for lighting
    guiPar->lightingOnOff = Button(inLighting, "valLighting", &mainSite, guiPar->lightingOnOff).out();

    // process value for info sign
    guiPar->signOnOff = Button(inInfoSign, "valInfoSign", &mainSite, guiPar->signOnOff).out();

    // process value for wall plug left
    guiPar->wallPlugLeftOnOff = Button(inWallPlugLeft, "valWallPlugLeft", &mainSite, guiPar->wallPlugLeftOnOff).out();

    // process value for wall plug right
    guiPar->wallPlugRightOnOff = Button(inWallPlugRight, "valWallPlugRight", &mainSite, guiPar->wallPlugRightOnOff).out();

    // process value for neonflex
    guiPar->neonFlexOnOff = Button(inNeonFlexOnOff, "valNeonFlexOnOff", &mainSite, guiPar->neonFlexOnOff).out();

    // process value for color selection
    guiPar->colorSelectionOnOff = Button(inColorSelectionOnOff, "valColorSelectionOnOff", &mainSite, guiPar->colorSelectionOnOff).out();

    // process value for color change
    guiPar->colorChangeOnOff = Button(inColorChangeOnOff, "valColorChangeOnOff", &mainSite, guiPar->colorChangeOnOff).out();

    // process value for hue
    guiPar->hsvHue = Slider(inHueChange, inHue, "valHue", &mainSite, guiPar->hsvHue).out();

    // process value for saturation
    guiPar->hsvSaturation = Slider(inSaturationChange, inSaturation, "valSaturation", &mainSite, guiPar->hsvSaturation).out();

    // process value for value
    guiPar->hsvValue = Slider(inValueChange, inValue, "valValue", &mainSite, guiPar->hsvValue).out();

    // process value for Speed
    guiPar->speed = Slider(inSpeedChange, inSpeed, "valSpeed", &mainSite, guiPar->speed).out();

    // shutdown system
    if (inShutdown == "true") {
        system("sudo shutdown -h now");
    }

    response.write(mainSite.toUtf8(),true);
}
