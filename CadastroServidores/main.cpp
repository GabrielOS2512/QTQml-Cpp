#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "classecsv.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    //App Info
    app.setOrganizationName("Gabriel");
    app.setOrganizationDomain("gabriel.com");
    app.setApplicationName("Gabriel App");

    qmlRegisterType<classeCSV> ("meuCSV",1,0,"ClasseCSV");

    QQmlApplicationEngine engine;

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    return app.exec();
}
