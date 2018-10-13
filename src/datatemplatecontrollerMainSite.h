#ifndef DATATEMPLATECONTROLLERMAINSITE_H
#define DATATEMPLATECONTROLLERMAINSITE_H

#include "httprequesthandler.h"
#include "customdatatypes.h"

using namespace stefanfrings;

class DataTemplateControllerMainSite: public HttpRequestHandler
{
    Q_OBJECT
public:
    DataTemplateControllerMainSite(QObject* parent = nullptr);
    ~DataTemplateControllerMainSite();

    void service(guiParameters* guiPar, HttpRequest& request, HttpResponse& response);

private:
    QList<QString> list;
};

#endif // DATATEMPLATECONTROLLERMAINSITE_H
