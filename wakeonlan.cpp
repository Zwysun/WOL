#include "wakeonlan.h"

WAKEONLAN::WAKEONLAN()
{

}

void WAKEONLAN::wake_on_ip(const QHostAddress &local_host, const QHostAddress &remote_host, const uint &remote_port, const QString &tmp_MacAddr)
{
    QUdpSocket udp_socket;
    QByteArray magicPacket;
    QString MacAddr = tmp_MacAddr;
    int repeat_times = 3;

    MacAddr.remove(QChar(':'), Qt::CaseInsensitive);
    MacAddr.remove(QChar('-'), Qt::CaseInsensitive);

    magicPacket = generate_magicpacket(MacAddr);

    udp_socket.bind(local_host);

    // 发送幻包
    for (int i=0; i < repeat_times; ++i)
    {
        udp_socket.writeDatagram(magicPacket, remote_host, remote_port);
        udp_socket.waitForBytesWritten();
    }

    udp_socket.deleteLater();

    for (int times=0; times < 3; ++times)
    {
        QThread::sleep(3);

        if (QueryOnline(remote_host))
            emit signal_set_status(true);
        else
            emit signal_set_status(false);
    }
}

void WAKEONLAN::wake_on_broadcast()
{

}

QByteArray WAKEONLAN::generate_magicpacket(const QString &MacAddr)
{
    QByteArray magicPacket;
    magicPacket.resize(102);
    magicPacket.fill(0xFF);

    /*6个 0xFF*/

    QByteArray byteMacAddr;

    byteMacAddr = QByteArray::fromHex(MacAddr.toUtf8());

    /*16个 MAC*/
    for(int k = 0; k < 16; k++)
    {
        for(int l = 0; l < 6; l++)
            magicPacket[(k+1)*6 + l] = byteMacAddr[l];
    }
    qDebug() << magicPacket;

    return magicPacket;
}
