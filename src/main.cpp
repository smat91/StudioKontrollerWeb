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

// Set the configuration file.
// Aborts the application if not found.
// @return The valid filename
QString setConfigFile()
{
    QString binDir {QCoreApplication::applicationDirPath()};
    QString appName {QCoreApplication::applicationName()};
    QFile file;

    // set pat
    file.setFileName(binDir+"/WebApp.ini");
    if (!file.exists())
    {
        file.setFileName(binDir+"/etc/WebApp.ini");
        if (!file.exists())
        {
            file.setFileName(binDir+"/../etc/WebApp.ini");
            if (!file.exists())
            {
                file.setFileName(binDir+"/../"+appName+"/etc/WebApp.ini");
                if (!file.exists())
                {
                    file.setFileName(binDir+"/../../"+appName+"/etc/WebApp.ini");
                    if (!file.exists())
                    {
                        file.setFileName(binDir+"/../../../../../"+appName+"/etc/WebApp.ini");
                        if (!file.exists())
                        {
                            file.setFileName(QDir::rootPath()+"etc/WebApp.ini");
                        }
                    }
                }
            }
        }
    }

    // check if file exists
    if (file.exists())
    {
        QString configFileName {QDir(file.fileName()).canonicalPath()};
        qDebug("using config file %s", qPrintable(configFileName));
        return configFileName;
    }
    else
    {
        qFatal("config file not found");
    }
}

int main(int argc, char* argv[])
{
    static bool init {false};
    guiParameters guiPar;
    QCoreApplication app(argc, argv);

    // init guiPar
    if (!init)
    {
        guiPar.hsvHue = 0;
        guiPar.hsvSaturation = 255;
        guiPar.hsvValue = 255;
        guiPar.speed = 100;

        guiPar.neonFlexOnOff = false;
        guiPar.colorChangeOnOff = false;
        guiPar.colorSelectionOnOff = false;
        guiPar.lightingOnOff = false;
        guiPar.wallPlugLeftOnOff = false;
        guiPar.wallPlugRightOnOff = false;
        guiPar.signOnOff = false;

        init = true;
    }

    // Load the configuration file
    QString configFileName {setConfigFile()};
    QSettings* listenerSettings {new QSettings(configFileName, QSettings::IniFormat, &app)};
    listenerSettings->beginGroup("listener");

    // Start the HTTP server
    new HttpListener(listenerSettings,new RequestMapper(&guiPar, &app),&app);

    // Configure template cache
    QSettings* templateSettings {new QSettings(configFileName,QSettings::IniFormat,&app)};
    templateSettings->beginGroup("templates");
    RequestMapper::templateCache = new TemplateCache(templateSettings,&app);

    // Static file controller
    QSettings* fileSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    fileSettings->beginGroup("files");
    RequestMapper::staticFileController = new StaticFileController(fileSettings,&app);

    // raspberry pi gpio controller
    new GpioController(guiPar, &app);

    return app.exec();
}
