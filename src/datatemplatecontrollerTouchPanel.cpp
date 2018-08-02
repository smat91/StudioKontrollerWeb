#include "requestmapper.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "template.h"

DataTemplateControllerTouchPanel::DataTemplateControllerTouchPanel(QObject* parent)
    : HttpRequestHandler(parent) {

}

void DataTemplateControllerTouchPanel::service(GuiParameters* guiPar, HttpRequest &request, HttpResponse &response) {

    // get values form webui
    QByteArray inLighting=request.getParameter("inLighting");

    QByteArray language=request.getHeader("Accept-Language");
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template t=RequestMapper::templateCache->getTemplate("files/TouchPanel",language);

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
    response.write(t.toUtf8(),true);
}
