#include "requestmapper.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "template.h"

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
    if (inLighting == "true") {
        if (guiPar->LightingOnOff == false) {
            guiPar->LightingOnOff = true;
            t.setVariable("valLighting","true");
        }
        else {
            guiPar->LightingOnOff = false;
            t.setVariable("valLighting","false");
        }
    }
    else {
        if (guiPar->LightingOnOff == false) {
            t.setVariable("valLighting","false");
        }
        else {
            t.setVariable("valLighting","true");
        }
    }

    // process value for info sign
    if (inInfoSign == "true") {
        if (guiPar->SignOnOff == false) {
            guiPar->SignOnOff = true;
            t.setVariable("valInfoSign","true");
        }
        else {
            guiPar->SignOnOff = false;
            t.setVariable("valInfoSign","false");
        }
    }
    else {
        if (guiPar->SignOnOff == false) {
            t.setVariable("valInfoSign","false");
        }
        else {
            t.setVariable("valInfoSign","true");
        }
    }

    // process value for wall plug left
    if (inWallPlugLeft == "true") {
        if (guiPar->WallplugLOnOff == false) {
            guiPar->WallplugLOnOff = true;
            t.setVariable("valWallPlugLeft","true");
        }
        else {
            guiPar->WallplugLOnOff = false;
            t.setVariable("valWallPlugLeft","false");
        }
    }
    else {
        if (guiPar->WallplugLOnOff == false) {
            t.setVariable("valWallPlugLeft","false");
        }
        else {
            t.setVariable("valWallPlugLeft","true");
        }
    }

    // process value for wall plug right
    if (inWallPlugRight == "true") {
        if (guiPar->WallplugROnOff == false) {
            guiPar->WallplugROnOff = true;
            t.setVariable("valWallPlugRight","true");
        }
        else {
            guiPar->WallplugROnOff = false;
            t.setVariable("valWallPlugRight","false");
        }
    }
    else {
        if (guiPar->WallplugROnOff == false) {
            t.setVariable("valWallPlugRight","false");
        }
        else {
            t.setVariable("valWallPlugRight","true");
        }
    }

    // process value for neonflex
    if (inNeonFlexOnOff == "true") {
        if (guiPar->NeonflexOnOff == false) {
            guiPar->NeonflexOnOff = true;
            t.setVariable("valNeonFlexOnOff","true");
        }
        else {
            guiPar->NeonflexOnOff = false;
            t.setVariable("valNeonFlexOnOff","false");
        }
    }
    else {
        if (guiPar->NeonflexOnOff == false) {
            t.setVariable("valNeonFlexOnOff","false");
        }
        else {
            t.setVariable("valNeonFlexOnOff","true");
        }
    }

    // process value for color selection
    if (inColorSelectionOnOff == "true") {
        if (guiPar->ColorSelectionOnOff == false) {
            guiPar->ColorSelectionOnOff = true;
            t.setVariable("valColorSelectionOnOff","true");
        }
        else {
            guiPar->ColorSelectionOnOff = false;
            t.setVariable("valColorSelectionOnOff","false");
        }
    }
    else {
        if (guiPar->ColorSelectionOnOff == false) {
            t.setVariable("valColorSelectionOnOff","false");
        }
        else {
            t.setVariable("valColorSelectionOnOff","true");
        }
    }

    // process value for color change
    if (inColorChangeOnOff == "true") {
        if (guiPar->ColorChangeOnOff == false) {
            guiPar->ColorChangeOnOff = true;
            t.setVariable("valColorChangeOnOff","true");
        }
        else {
            guiPar->ColorChangeOnOff = false;
            t.setVariable("valColorChangeOnOff","false");
        }
    }
    else {
        if (guiPar->ColorChangeOnOff == false) {
            t.setVariable("valColorChangeOnOff","false");
        }
        else {
            t.setVariable("valColorChangeOnOff","true");
        }
    }

    // process value for hue
    if (inHueChange == "true") {
        guiPar->HSV_hue = QString(inHue).toInt();
        QString valHue = QString::number(guiPar->HSV_hue);
        t.setVariable("valHue", valHue );
    }
    else {
        QString valHue = QString::number(guiPar->HSV_hue);
        t.setVariable("valHue", valHue );
    }

    // process value for saturation
    if (inSaturationChange == "true") {
        guiPar->HSV_saturation = QString(inSaturation).toInt();
        QString valSaturation = QString::number(guiPar->HSV_saturation);
        t.setVariable("valSaturation", valSaturation );
    }
    else {
        QString valSaturation = QString::number(guiPar->HSV_saturation);
        t.setVariable("valSaturation", valSaturation );
    }

    // process value for value
    if (inValueChange == "true") {
        guiPar->HSV_value = QString(inValue).toInt();
        QString valValue = QString::number(guiPar->HSV_value);
        t.setVariable("valValue", valValue );
    }
    else {
        QString valValue = QString::number(guiPar->HSV_value);
        t.setVariable("valValue", valValue );
    }

    // process value for value
    if (inSpeedChange == "true") {
        guiPar->Speed = QString(inSpeed).toInt();
        QString valSpeed = QString::number(guiPar->Speed);
        t.setVariable("valSpeed", valSpeed );
    }
    else {
        QString valSpeed = QString::number(guiPar->Speed);
        t.setVariable("valSpeed", valSpeed);
    }

    response.write(t.toUtf8(),true);
}
