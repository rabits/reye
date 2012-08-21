/**
 * @file    main.cpp
 * @date    2012-08-20T23:00:00+0400
 *
 * @author  Rabits <home.rabits@gmail.com>
 * @copyright GNU General Public License, version 3 <http://www.gnu.org/licenses/>
 *
 * This file is a part of rEye project <https://github.com/rabits/reye>
 *
 * @brief   Main module
 *
 */

#include "src/common/common.h"

using namespace Common;

#include <QtGui/QApplication>
#include "qmlapplicationviewer.h"

#include "src/ceye.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    log_notice("Init rEye v%1", PROJECT_VERSION);

    QCoreApplication::setOrganizationName("Rabits");
    QCoreApplication::setOrganizationDomain("rabits.ru");
    QCoreApplication::setApplicationName("reye");
    QCoreApplication::setApplicationVersion(PROJECT_VERSION);

    try {
        QScopedPointer<QApplication> app(createApplication(argc, argv));

        QmlApplicationViewer viewer;

        log_info("Creating context");
        CEye::i()->initContext(viewer, &app);

        log_info("Loading qml");
        viewer.setSource(QUrl("qrc:/qml/main.qml"));

        CEye::i()->initRoot(viewer);

        log_notice("Init done, starting");

        viewer.showExpanded();
        return app->exec();
    }
    catch( Common::CException const &e ) {
        log_emerg("An unhandled exception has occured: %1", e.what());
    }
    catch(...) {
        log_emerg("An unknown exception has occured!");
    }

    log_emerg("Abnormally exiting...");

    return 1;
}
