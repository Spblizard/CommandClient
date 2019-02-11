#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "client.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    Client client;

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    engine.rootContext()->setContextProperty("client", &client);
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
