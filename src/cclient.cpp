/**
 * @file    cclient.cpp
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

#include "cclient.h"
#include "ceye.h"

CClient::CClient(QObject *parent)
    : QObject(parent)
    , m_socket(NULL)
{
    log_info("Init client");
    m_socket = new QTcpSocket();
    QHostAddress address(CEye::i()->setting("client/server").toString());
    m_socket->connectToHost(address, CEye::i()->setting("client/port").toUInt(), QUdpSocket::ReadOnly);

    connect(m_socket, SIGNAL(readyRead()), this, SLOT(readDatagrams()));
}

CClient::~CClient()
{
    m_socket->close();
    delete m_socket;
}

void CClient::readDatagrams()
{
    QHostAddress sender;
    quint16 port;

    while( m_socket->hasPendingDatagrams() )
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());

        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &port);

        log_notice("Datagram recieved: '%1'", datagram.to);
    }
}
