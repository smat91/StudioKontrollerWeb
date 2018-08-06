#include "requestmapper.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "template.h"
#include "webguiinputcontroller.h"

DataTemplateControllerMainSite::DataTemplateControllerMainSite(QObject* parent)
    : HttpRequestHandler(parent) {

}

void DataTemplateControllerMainSite::service(GuiParameters* guiPar, HttpRequest &request, HttpResponse &response) {

    // get values form webui
    QByteArray inLighting=request.getParameter("inLighting");
    QByteArray inInfoSign=request.getParameter("inInfoSign");
    QByteArray inWallPlugLeft=request.getParameter("inWallPlugLeft");
    QByteArray inWallPlugRight=request.getParameter("inWallPlugRight");
    QByteArray inNeonFlexOnOff=request.getParameter("inNeonFlexOnOff");
    QByteArray inColorSelectionOnOff=request.getParameter("inColorSelectionOnOff");
    QByteArray inColorChangeOnOff=request.getParameter("inColorChangeOnOff");
    QByteArray inShutdown=request.getParameter("inShutdown");
    QByteArray inHue=request.getParameter("inHue");
    QByteArray inSaturation=request.getParameter("inSaturation");
    QByteArray inValue=request.getParameter("inValue");
    QByteArray inSpeed=request.getParameter("inSpeed");
    QByteArray inHueChange=request.getParameter("inHueChange");
    QByteArray inSaturationChange=request.getParameter("inSaturationChange");
    QByteArray inValueChange=request.getParameter("inValueChange");
    QByteArray inSpeedChange=request.getParameter("inSpeedChange");

    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t=RequestMapper::templateCache->getTemplate("files/MainSite",language);

    // process value for lighting
    guiPar->LightingOnOff = Button(inLighting, "valLighting", &t, guiPar->LightingOnOff).out();

    // process value for info sign
    guiPar->SignOnOff = Button(inInfoSign, "valInfoSign", &t, guiPar->SignOnOff).out();

    // process value for wall plug left
    guiPar->WallplugLOnOff = Button(inWallPlugLeft, "valWallPlugLeft", &t, guiPar->WallplugLOnOff).out();

    // process value for wall plug right
    guiPar->WallplugROnOff = Button(inWallPlugRight, "valWallPlugRight", &t, guiPar->WallplugROnOff).out();

    // process value for neonflex
    guiPar->NeonflexOnOff = Button(inNeonFlexOnOff, "valNeonFlexOnOff", &t, guiPar->NeonflexOnOff).out();

    // process value for color selection
    guiPar->ColorSelectionOnOff = Button(inColorSelectionOnOff, "valColorSelectionOnOff", &t, guiPar->ColorSelectionOnOff).out();

    // process value for color change
    guiPar->ColorChangeOnOff = Button(inColorChangeOnOff, "valColorChangeOnOff", &t, guiPar->ColorChangeOnOff).out();

    // process value for hue
    guiPar->HSV_hue = Slider(inHueChange, inHue, "valHue", &t, guiPar->HSV_hue).out();

    // process value for saturation
    guiPar->HSV_saturation = Slider(inSaturationChange, inSaturation, "valSaturation", &t, guiPar->HSV_saturation).out();

    // process value for value
    guiPar->HSV_value = Slider(inValueChange, inValue, "valValue", &t, guiPar->HSV_value).out();

    // process value for Speed
    guiPar->Speed = Slider(inSpeedChange, inSpeed, "valSpeed", &t, guiPar->Speed).out();

    // shutdown system
    if (inShutdown == "true") {
        system("sudo shutdown -P now");
    }

    response.write(t.toUtf8(),true);
}
