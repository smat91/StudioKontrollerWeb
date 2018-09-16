// QT includes
#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>

// user includes
#include "customdatatypes.h"
#include "httplistener.h"
#include "httprequesthandler.h"
#include "requestmapper.h"
#include "gpiocontroller.h"

// namespaces
using namespace stefanfrings;

/**
 * Search the configuration file.
 * Aborts the application if not found.
 * @return The valid filename
 */
QString searchConfigFile() {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QFile file;
    file.setFileName(binDir+"/WebApp.ini");
    if (!file.exists()) {
        file.setFileName(binDir+"/etc/WebApp.ini");
        if (!file.exists()) {
            file.setFileName(binDir+"/../etc/WebApp.ini");
            if (!file.exists()) {
                file.setFileName(binDir+"/../"+appName+"/etc/WebApp.ini");
                if (!file.exists()) {
                    file.setFileName(binDir+"/../../"+appName+"/etc/WebApp.ini");
                    if (!file.exists()) {
                        file.setFileName(binDir+"/../../../../../"+appName+"/etc/WebApp.ini");
                        if (!file.exists()) {
                            file.setFileName(QDir::rootPath()+"etc/WebApp.ini");
                        }
                    }
                }
            }
        }
    }
    if (file.exists()) {
        QString configFileName=QDir(file.fileName()).canonicalPath();
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else {
        qFatal("config file not found");
    }
}

int main(int argc, char *argv[])
{
    static bool init = false;

    GuiParameters GuiPar;

    QCoreApplication app(argc, argv);

    new GpioController(GuiPar, &app);

    if (!init) {
        GuiPar.HSV_hue = 0;
        GuiPar.HSV_saturation = 255;
        GuiPar.HSV_value = 255;
        GuiPar.Speed = 100;

        GuiPar.NeonflexOnOff = false;
        GuiPar.ColorChangeOnOff = false;
        GuiPar.ColorSelectionOnOff = false;
        GuiPar.LightingOnOff = false;
        GuiPar.WallplugLOnOff = false;
        GuiPar.WallplugROnOff = false;
        GuiPar.SignOnOff = false;

        init = true;
    }

    // Load the configuration file
    QString configFileName=searchConfigFile();
    QSettings* listenerSettings=new QSettings(configFileName, QSettings::IniFormat, &app);
    listenerSettings->beginGroup("listener");

    // Start the HTTP server
    new HttpListener(listenerSettings,new RequestMapper(&GuiPar, &app),&app);

    // Configure template cache
    QSettings* templateSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    templateSettings->beginGroup("templates");
    RequestMapper::templateCache=new TemplateCache(templateSettings,&app);

    // Static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("files");
    RequestMapper::staticFileController=new StaticFileController(fileSettings,&app);

    return app.exec();
}
