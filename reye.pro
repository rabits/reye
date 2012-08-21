# Version
VERSION='0.0.1'
VERSTR='\\"$${VERSION}\\"'
DEFINES += PROJECT_VERSION=\"$${VERSTR}\"

# Debug on debug
debug {
    DEFINES += CONFIG_DEBUG
    message("DEBUG MODE ON")
}

release: message("DEBUG MODE OFF")

debug: release: error("debug release builds is not supported. Add to release build 'CONFIG-=debug' and to debug build 'CONFIG-=release' $${CONFIG}")

QMAKE_CXXFLAGS += -std=c++0x
QT += opengl network

# Add more folders to ship with the application, here
folder_01.source = qml/reye
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE2BE8A33

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
CONFIG += mobility
MOBILITY += multimedia

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    src/ceye.cpp \
    src/common/clog.cpp \
    src/common/cexception.cpp \
    src/cserver.cpp \
    src/cclient.cpp

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
    qtc_packaging/debian_harmattan/changelog

RESOURCES += \
    resources.qrc

HEADERS += \
    src/ceye.h \
    src/common/common.h \
    src/common/clog.h \
    src/common/cexception.h \
    src/cserver.h \
    src/cclient.h
