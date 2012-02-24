# Add more folders to ship with the application, here
folder_01.source = qml/Bonsaicare
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01
QT += sql core gui declarative
QT += xmlpatterns
# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =
VERSION = 1.1
symbian:TARGET.UID3 = 0xE2D1DDA8

# Publish the app version to source code.
VERSTR = '\\"$${VERSION}\\"'
DEFINES += VER=\"$${VERSTR}\"
DEFINES += QMLJSDEBUGGER
# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qt-components qdeclarative-boostable

# If your application uses the Qt Mobility libraries, uncomment
# the following lines and add the respective components to the
# MOBILITY variable.
 CONFIG += mobility
 MOBILITY += sensors
# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    DatabaseManager.cpp \
    weekmodel.cpp \
    daymodel.cpp \
    speciemodel.cpp \
    bonsaimodel.cpp \
    bonsai.cpp \
    specie.cpp \
    monthmodel.cpp \
    day.cpp \
    bonsaiworker.cpp \
    Orientation.cpp \
    operationmodel.cpp \
    operation.cpp \
    slot.cpp \
    slotmodel.cpp \
    scheduler.cpp \
    bonsaiserializer.cpp

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    resources/db.xml \
    resources/operations-by-specie.xq \
    resources/species.xq

HEADERS += \
    DatabaseManager.h \
    weekmodel.h \
    daymodel.h \
    speciemodel.h \
    bonsaimodel.h \
    bonsai.h \
    specie.h \
    monthmodel.h \
    day.h \
    bonsaiworker.h \
    orientationfilter.h \
    Orientation.h \
    operationmodel.h \
    operation.h \
    slot.h \
    slotmodel.h \
    scheduler.h \
    bonsaiserializer.h

RESOURCES += \
    resources.qrc
