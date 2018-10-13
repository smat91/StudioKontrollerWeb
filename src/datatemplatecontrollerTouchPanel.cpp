#include "requestmapper.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "template.h"
#include "webguiinputcontroller.h"

DataTemplateControllerTouchPanel::DataTemplateControllerTouchPanel(QObject* parent):
    HttpRequestHandler(parent)
{
}

DataTemplateControllerTouchPanel::~DataTemplateControllerTouchPanel()
{
}

void DataTemplateControllerTouchPanel::service(guiParameters* guiPar, HttpRequest &request, HttpResponse &response)
{

    // get values form webui
    QByteArray inLighting {request.getParameter("inLighting")};

    QByteArray language {request.getHeader("Accept-Language")};
    response.setHeader("Content-Type", "text/html; charset=UTF-8");

    Template touchPanel {RequestMapper::templateCache->getTemplate("files/TouchPanel",language)};

    // process value for lighting
    guiPar->lightingOnOff = Button(inLighting, "valLighting", &touchPanel, guiPar->lightingOnOff).out();

    response.write(touchPanel.toUtf8(),true);
}
