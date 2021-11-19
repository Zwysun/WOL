#include "tools.h"


bool IPLive(QHostAddress ip, int port, int timeout) {
    QTcpSocket tcpClient;
    tcpClient.abort();
    tcpClient.connectToHost(ip, port);
    //100毫秒没有连接上则判断不在线
    return tcpClient.waitForConnected(timeout);
}

bool QueryOnline(QHostAddress ip)
{
    static QList<int> tcping_port = QList<int>() << 20 << 21 << 22 << 80 << 135 << 139 << 143 << 445 << 3020 << 3306 << 3389 << 8080;

    for (int i=0; i < tcping_port.size(); ++i)
    {
        if (IPLive(ip, tcping_port.at(i)))
        {
            return true;
            break;
        }
    }

    return false;
}
