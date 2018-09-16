#include "requestmapper.h"

TemplateCache* RequestMapper::templateCache=0;
StaticFileController* RequestMapper::staticFileController=0;

RequestMapper::RequestMapper(GuiParameters* guiPar, QObject* parent)
    : HttpRequestHandler(parent) {
    GuiPar = guiPar;
}

RequestMapper::~RequestMapper()
{
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response) {
    QByteArray path=request.getPath();
    qDebug("RequestMapper: path=%s",path.data());

    if (path=="/files/TouchPanel") {
            DataTemplateControllerTouchPanel().service(GuiPar, request, response);
        }
    else if (path=="/files/MainSite") {
            DataTemplateControllerMainSite().service(GuiPar, request, response);
        }
    else if (path.startsWith("/files") && path!="/files/MainSite" && path!="/files/TouchPanel") {
        staticFileController->service(request,response);
    }
    else {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}
