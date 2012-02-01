#include <QtGui/QApplication>
#include <QtGui/QFontDatabase>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeContext>
#include <QOrientationSensor>
#include <QThread>
#include <QGraphicsObject>
#include "DatabaseManager.h"
#include "bonsaiitemmodel.h"
#include "bonsaimodel.h"
#include "qmlapplicationviewer.h"
#include "orientationfilter.h"
#include "monthmodel.h"
#include "weekmodel.h"

#ifdef Q_OS_SYMBIAN
    // Lock orientation in Symbian
    #include <eikenv.h>
    #include <eikappui.h>
    #include <aknenv.h>
    #include <aknappui.h>
#endif

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qDebug() << "Main thread id:" << QThread::currentThreadId();

    QDeclarativeContext *rootContext = viewer->rootContext();

    // Set font
    int fontId = QFontDatabase::addApplicationFont("qml/resources/nokia_pure_font.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    for(int i = 0; i < fontFamilies.count(); i++) {
        qDebug() << "Font family: " << fontFamilies.at(i);
    }

    QFont nokiaFont;
    nokiaFont.setFamily("Nokia Pure Text");
    QApplication::setFont(nokiaFont);

    viewer->setAttribute(Qt::WA_NoSystemBackground);

#if defined(Q_OS_SYMBIAN)
    // Workaround for an issue with Symbian: "X.Y.Z" -> X.Y.Z
    static const QString VERSION_NUMBER(QString("%1").arg(VER).mid(1, QString(VER).length()-2));
#else
    static const QString VERSION_NUMBER(QString("%1").arg(VER)); // X.Y.Z by itself
#endif

    app->setApplicationVersion(VERSION_NUMBER);


    //Setting models
    QScopedPointer<MonthModel> months(new MonthModel());
    rootContext->setContextProperty("months", months.data());

    QScopedPointer<WeekModel> week(new WeekModel());
    rootContext->setContextProperty("week", week.data());

    rootContext->setContextProperty(QString("cp_versionNumber"), VERSION_NUMBER);
    // Setting database Qt class handle to QML
    QScopedPointer<DatabaseManager> db(new DatabaseManager());
    db->open();
    rootContext->setContextProperty("db", db.data());

    QScopedPointer<BonsaiItemModel> bonsaiItem(new BonsaiItemModel());
    qDebug() << "BONSAI ITEM ROW COUNT" << bonsaiItem->rowCount();
    rootContext->setContextProperty("bonsaiItem", bonsaiItem.data());

    QScopedPointer<BonsaiModel> bonsai(new BonsaiModel(db->getDB(), bonsaiItem.data()));
    bonsai->init();    
    rootContext->setContextProperty("bonsai", bonsai.data());


    // App version to QML in Symbian^3 version build
#ifndef Q_OS_SYMBIAN_1
    rootContext->setContextProperty("appversion", app->applicationVersion());
#endif

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/Bonsaicare/main.qml"));

    //Attivo il sensore di orientamento
    QOrientationSensor sensor;
    OrientationFilter filter;
    sensor.addFilter(&filter);
    QObject *item = viewer->rootObject();

    // Connect the Qt signal to QML function
    QObject::connect(&filter, SIGNAL(orientationChanged(const QVariant&)),
                     item , SLOT(orientationChanged(const QVariant&)));
    sensor.start();

#ifdef Q_WS_MAEMO_5
    QGLFormat fmt = QGLFormat::defaultFormat();
    fmt.setDoubleBuffer(true);

    QGLWidget *glWidget = new QGLWidget(fmt);
    viewer->setViewport(glWidget);
#endif

#if defined(Q_WS_MAEMO_5) || defined(Q_OS_SYMBIAN) || defined(QT_SIMULATOR)
    viewer->showFullScreen();
#else
    viewer->showExpanded();
#endif
    /*con splash screen
    // First set a QML file that's quick to load and show it as a splash screen.
    viewer.setMainQmlFile(QLatin1String("qml/weeklyplanner/Splash.qml"));
    // Then trigger loading the *real* main.qml file, which can take longer to load.
    LoadHelper loadHelper(&viewer);
    QTimer::singleShot(1, &loadHelper, SLOT(loadMainQML()));
     */

    // Start the application
    int ret = app->exec();    
    return ret;
}
