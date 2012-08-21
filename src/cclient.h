/**
 * @file    cclient.h
 * @date    2012-8-21T17:00:00+0400
 *
 * @author  Rabits <home.rabits@gmail.com>
 * @copyright GNU General Public License, version 3 <http://www.gnu.org/licenses/>
 *
 * This file is a part of rEye project <https://github.com/rabits/reye>
 *
 * @brief   CClient - client module
 *
 */

#ifndef CCLIENT_H
#define CCLIENT_H

#include "src/common/common.h"

#include <QObject>
#include <QTcpSocket>

class CClient
    : public QObject
{
    Q_OBJECT

public:
    explicit CClient(QObject *parent = 0);
    ~CClient();

protected slots:
    void readDatagrams();

protected:
    QTcpSocket *m_socket;
};

#endif // CCLIENT_H
