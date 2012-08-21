/**
 * @file    cserver.h
 * @date    2012-8-21T17:00:00+0400
 *
 * @author  Rabits <home.rabits@gmail.com>
 * @copyright GNU General Public License, version 3 <http://www.gnu.org/licenses/>
 *
 * This file is a part of rEye project <https://github.com/rabits/reye>
 *
 * @brief   CServer - server module
 *
 */

#ifndef CSERVER_H
#define CSERVER_H

#include "src/common/common.h"

#include <QObject>
#include <QCamera>
#include <QTcpSocket>

class CServer
    : public QObject
{
    Q_OBJECT

public:
    explicit CServer(QObject *parent = 0);
    ~CServer();

protected:
    QCamera        *m_camera;
    QTcpSocket     *m_socket;

    void send(QByteArray data);
};

#endif // CSERVER_H
