#include "requestmapper.h"

TemplateCache* RequestMapper::templateCache {0};
StaticFileController* RequestMapper::staticFileController {0};

RequestMapper::RequestMapper(guiParameters* guiPar, QObject* parent):
    HttpRequestHandler(parent),
    guiPar_(guiPar)
{
}

RequestMapper::~RequestMapper()
{
}

void RequestMapper::service(HttpRequest& request, HttpResponse& response)
{
    QByteArray path {request.getPath()};
    qDebug("RequestMapper: path=%s",path.data());

    if (path == "/files/TouchPanel")
    {
        DataTemplateControllerTouchPanel().service(guiPar_, request, response);
    }
    else if (path == "/files/MainSite")
    {
        DataTemplateControllerMainSite().service(guiPar_, request, response);
    }
    else if (path.startsWith("/files") && path != "/files/MainSite" && path != "/files/TouchPanel")
    {
        staticFileController->service(request,response);
    }
    else
    {
        response.setStatus(404,"Not found");
        response.write("The URL is wrong, no such document.",true);
    }

    qDebug("RequestMapper: finished request");
}
