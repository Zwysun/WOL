#ifndef WOL_H
#define WOL_H

#include <QMainWindow>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QThread>
#include "ledlabel.h"
#include "wakeonlan.h"
#include "tools.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WOL; }
QT_END_NAMESPACE

class WOL : public QMainWindow
{
    Q_OBJECT
signals:
    void signal_wake_ip(const QHostAddress &local_host, const QHostAddress &remote_host, const uint &remote_port, const QString &tmp_MacAddr);
    void signal_gen(const QString& mac);
public:
    WOL(QWidget *parent = nullptr);
    ~WOL();

private slots:
    void on_wakeup_pushButton_clicked();

    void on_send_ip_comboBox_clicked();

    void set_online_status(const bool is_online=false);

    void on_online_pushButton_clicked();

private:
    Ui::WOL *ui;

    QHostAddress send_ip;

    QHostAddress remote_ip;
    uint remote_port;
    QString remote_mac;

    bool if_online;
    uint remote_tcping_port;

    LedLabel *online_label;

    WAKEONLAN wake_object;

    // 多线程
    QThread wakeonlan_worker;

};
#endif // WOL_H
