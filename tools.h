#ifndef TOOLS_H
#define TOOLS_H

#include <QTcpSocket>
#include <QHostAddress>
#include <QList>


bool IPLive(QHostAddress ip, int port, int timeout = 1000);

bool QueryOnline(QHostAddress ip);

#endif // TOOLS_H
