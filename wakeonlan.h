#ifndef WAKEONLAN_H
#define WAKEONLAN_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>
#include <QByteArray>
#include "tools.h"

class WAKEONLAN:public QObject
{
    Q_OBJECT
signals:
    void signal_set_status(const bool is_online);
public:
    WAKEONLAN();

    void wake_on_ip(const QHostAddress &local_host, const QHostAddress &remote_host, const uint &remote_port, const QString &tmp_MacAddr);
    void wake_on_broadcast();

    QByteArray generate_magicpacket(const QString &MacAddr);
};

#endif // WAKEONLAN_H
