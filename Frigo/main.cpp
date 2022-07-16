#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QLocale>
#include <QDir>
#include <QDebug>

#include "database/database.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    qDebug() << "#####################################";
    qDebug() << "####### Starting  Application #######";
    qDebug() << "#####################################";

    if(Database::init()){
        qDebug() << "Started Database...";
    } else {
        qDebug() << "Failed to start Database...";
    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    //define app path to be used in images sources
    engine.rootContext()->setContextProperty("appPath", "file:/" + QDir::currentPath());

    Database::release();

    return app.exec();
}
