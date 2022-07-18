#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "database/database.h"
#include "database/produto.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);

    QGuiApplication::setOrganizationName("Frigocamara");
    QGuiApplication::setOrganizationDomain("Gabriel");
    QGuiApplication::setApplicationName("Gabriel");
    QGuiApplication::setApplicationVersion("1.0");

    qDebug() << "#####################################";
    qDebug() << "####### Starting  Application #######";
    qDebug() << "#####################################";

    if(Database::init()){
        qDebug() << "Started Database...";
    } else {
        qDebug() << "Failed to start Database...";
    }

    produto_sptr produto;
    produto.reset(new Produto("Contra-Filet",28.99));
    qDebug() << "Produto Save = " << produto->save();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    Database::release();
    return app.exec();
}
