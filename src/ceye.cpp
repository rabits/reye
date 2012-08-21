/**
 * @file    ceye.cpp
 * @date    2012-8-21T16:00:00+0400
 *
 * @author  Rabits <home.rabits@gmail.com>
 * @copyright GNU General Public License, version 3 <http://www.gnu.org/licenses/>
 *
 * This file is a part of rEye project <https://github.com/rabits/reye>
 *
 * @brief   CEye - main object
 *
 */

#include "ceye.h"

#include <QtOpenGL/QGLWidget>
#include <QLocale>

CEye* CEye::sp_instance = NULL;

CEye::CEye(QObject *parent)
    : QObject(parent)
    , m_settings()
    , m_server(NULL)
    , m_client(NULL)
{
    // Set default settings
    log_info("Init engine");

    if( m_settings.value("preferences/locale").isNull() )
        m_settings.setValue("preferences/locale", QLocale::system().name());

    if( m_settings.value("server/enabled").isNull() )
        m_settings.setValue("server/enabled", false);

    if( m_settings.value("server/camera").isNull() )
        m_settings.setValue("server/camera", "");

    if( m_settings.value("server/output_resolution").isNull() )
        m_settings.setValue("server/output_resolution", "");

    if( m_settings.value("server/output_quality").isNull() )
        m_settings.setValue("server/output_quality", 100);

    if( m_settings.value("server/bind_port").isNull() )
        m_settings.setValue("server/bind_port", 60600);

    if( m_settings.value("client/enabled").isNull() )
        m_settings.setValue("client/enabled", false);

    if( m_settings.value("client/server").isNull() )
        m_settings.setValue("client/server", "localhost");

    if( m_settings.value("client/port").isNull() )
        m_settings.setValue("client/port", 60600);

    if( m_settings.value("client/output_resolution").isNull() )
        m_settings.setValue("client/output_resolution", "");
}

void CEye::initContext(QmlApplicationViewer &viewer, QScopedPointer<QApplication> *app)
{
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setViewport(new QGLWidget());

    m_context = viewer.rootContext();

    m_context->setContextProperty("ctab", this);

    m_app = app;
    changeLocale(setting("preferences/locale").toString());
    (*m_app)->installTranslator(&m_translator);
}

void CEye::initRoot(QmlApplicationViewer &viewer)
{
    m_root_object = viewer.rootObject();
}

void CEye::changeLocale(QString locale)
{
    log_notice("Changing locale to %1", locale);
    if( ! m_translator.load("tr_" + locale, ":/") )
    {
        m_translator.load("tr_en", ":/");
        setting("preferences/locale", "en");
    }
}

QVariant CEye::setting(QString key, QString value)
{
    if( ! value.isEmpty() )
        m_settings.setValue(key, value);

    return m_settings.value(key);
}
