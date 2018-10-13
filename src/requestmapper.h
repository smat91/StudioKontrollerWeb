#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include "httprequesthandler.h"
#include "templatecache.h"
#include "datatemplatecontrollerTouchPanel.h"
#include "datatemplatecontrollerMainSite.h"
#include "staticfilecontroller.h"
#include "customdatatypes.h"

using namespace stefanfrings;

class RequestMapper : public HttpRequestHandler
{
    Q_OBJECT
public:
    RequestMapper(guiParameters* guiPar, QObject* parent = nullptr);
    ~RequestMapper();

    void service(HttpRequest& request, HttpResponse& response);
    static TemplateCache* templateCache;
    static StaticFileController* staticFileController;

    guiParameters* guiPar_;
};

#endif // REQUESTMAPPER_H
