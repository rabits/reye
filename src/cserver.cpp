/**
 * @file    cserver.cpp
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

#include "cserver.h"

#include "ceye.h"

CServer::CServer(QObject *parent)
    : QObject(parent)
    , m_camera(NULL)
    , m_socket(NULL)
{
    log_info("Init server");
    QList<QByteArray> devices = QCamera::availableDevices();
    foreach( QByteArray device, devices )
    {
        if( device == CEye::i()->setting("server/camera").toByteArray() )
            m_camera = new QCamera(device);
    }
    if( m_camera == NULL )
        m_camera = new QCamera(devices.first());

    m_socket = new QTcpSocket();
    m_socket->(CEye::i()->setting("server/bind_port").toUInt());

    connect(m_camera, SIGNAL(error(QCamera::Error)), this, SLOT(cameraError()));
    connect(m_camera, SIGNAL(stateChanged(QCamera::State)), this, SLOT(cameraStateChanged(QCamera::State)));

    m_camera->captureMode(QCamera::CaptureVideo);

    m_camera->service()->requestControl();

    m_camera->focus();
    m_camera->start();
}

CServer::~CServer()
{
    m_camera->stop();
    m_socket->close();

    delete m_camera;
    delete m_socket;
}

void CServer::send(QByteArray data)
{
    QByteArray out_data;
    QDataStream out(&out_data, QIODevice::WriteOnly);
    out << qint64(0);
    out << data;
    out.device()->seek(qint64(0));
    out << qint64(out_data.size() - sizeof(qint64));
    m_socket->writeDatagram(out_data, m_client_address, m_client_port);
}
