#ifndef DATATEMPLATECONTROLLERTOUCHPANEL_H
#define DATATEMPLATECONTROLLERTOUCHPANEL_H

#include "httprequesthandler.h"
#include "customdatatypes.h"

using namespace stefanfrings;

class DataTemplateControllerTouchPanel: public HttpRequestHandler
{
    Q_OBJECT
public:
    DataTemplateControllerTouchPanel(QObject* parent = nullptr);
    ~DataTemplateControllerTouchPanel();

    void service(guiParameters* guiPar, HttpRequest& request, HttpResponse& response);

private:
    QList<QString> list;
};

#endif // DATATEMPLATECONTROLLERTOUCHPANEL_H
