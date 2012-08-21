/**
 * @file    ceye.h
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

#ifndef CEYE_H
#define CEYE_H

#include "src/common/common.h"

#include <QObject>
#include <QSettings>
#include <QtDeclarative/QDeclarativeContext>
#include <qplatformdefs.h> // MEEGO_EDITION_HARMATTAN
#include <QTranslator>
#include <QApplication>

#include "qmlapplicationviewer.h"

#include "cserver.h"
#include "cclient.h"

class CEye
    : public QObject
{
    Q_OBJECT

public:
    inline static CEye* i()               { if( sp_instance == NULL ) sp_instance = new CEye(); return sp_instance; }
    inline static void  destroyInstance() { delete sp_instance; }

    void initContext(QmlApplicationViewer& viewer, QScopedPointer<QApplication> *app);
    void initRoot(QmlApplicationViewer &viewer);

    Q_INVOKABLE void changeLocale(QString locale);

    Q_INVOKABLE inline QSettings* settings() { return &m_settings; }
    Q_INVOKABLE QVariant setting(QString key, QString value = "");

private:
    explicit CEye(QObject *parent = 0);

    static CEye* sp_instance;

    QGraphicsObject*     m_root_object;
    QDeclarativeContext* m_context;

    QSettings     m_settings;

    QTranslator                   m_translator;
    QScopedPointer<QApplication> *m_app;

    CServer *m_server;
    CClient *m_client;
};

#endif // CEYE_H
