#include <QtGui/QApplication>
#include <QtGui/QFontDatabase>
#include <QtCore/QDebug>
#include <QtDeclarative/QDeclarativeContext>
//#include <QOrientationSensor>
#include <QThread>
//#include <QGraphicsObject>
#include "DatabaseManager.h"
#include "speciemodel.h"
#include "bonsaimodel.h"
#include "qmlapplicationviewer.h"
#include "monthmodel.h"
#include "weekmodel.h"

/*#ifdef Q_OS_SYMBIAN
    // Lock orientation in Symbian
    #include <eikenv.h>
    #include <eikappui.h>
    #include <aknenv.h>
    #include <aknappui.h>
#endif
*/
Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));
    QScopedPointer<QmlApplicationViewer> viewer(QmlApplicationViewer::create());

    qDebug() << "Main thread id:" << QThread::currentThreadId();

    QDeclarativeContext *rootContext = viewer->rootContext();

    // Set font
    QFontDatabase::addApplicationFont("qml/Bonsaicare/resources/NokiaPureText.ttf");
    QFontDatabase::addApplicationFont("qml/Bonsaicare/resources/NokiaPureTextBold.ttf");
    QFontDatabase::addApplicationFont("qml/Bonsaicare/resources/NokiaPureTextLight.ttf");


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

    //Open db connection
    QScopedPointer<DatabaseManager> db(new DatabaseManager());
    db->open();

    //Setting models
    //used for displaying months on top
    QScopedPointer<MonthModel> months(new MonthModel());
    rootContext->setContextProperty("months", months.data());


    //used to list all species of bonsais
    QScopedPointer<SpecieModel> bonsaiItem(new SpecieModel());
    qDebug() << "BONSAI ITEM ROW COUNT" << bonsaiItem->rowCount();
    rootContext->setContextProperty("bonsaiItem", bonsaiItem.data());

    //used to get all custom bonsais
    QScopedPointer<BonsaiModel> bonsai(new BonsaiModel(bonsaiItem.data()));
    rootContext->setContextProperty("bonsai", bonsai.data());
    bonsai->init();

    //used for displaying week days on top
    QScopedPointer<WeekModel> week(new WeekModel(bonsai.data()));
    rootContext->setContextProperty("week", week.data());



    rootContext->setContextProperty(QString("cp_versionNumber"), VERSION_NUMBER);

    // Setting database Qt class handle to QML
    /*
    rootContext->setContextProperty("db", db.data());*/




    // App version to QML in Symbian^3 version build
#ifndef Q_OS_SYMBIAN_1
    rootContext->setContextProperty("appversion", app->applicationVersion());
#endif

    viewer->setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer->setMainQmlFile(QLatin1String("qml/Bonsaicare/main.qml"));

    //Attivo il sensore di orientamento
    /*QOrientationSensor sensor;
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
#endif*/

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
    db->close();
    return ret;
}
