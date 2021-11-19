#include "wol.h"
#include "ui_wol.h"

WOL::WOL(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::WOL)
{
    ui->setupUi(this);

    // 界面显示初始化

    ui->remote_port_lineEdit->setPlaceholderText("默认 9");
    ui->ping_port_lineEdit->setPlaceholderText("为空时将尝试Ping");
    ui->remote_mac_lineEdit->setPlaceholderText("XX-XX-XX-XX-XX-XX");

    online_label = new LedLabel(this, "在线状态");
    online_label->setGeometry(270, 140, 100, 20);

    // 参数初始化
    send_ip = QHostAddress("127.0.0.1");

    remote_ip = QHostAddress("127.0.0.1");
    remote_port = 9;
    remote_mac = "";

    if_online = false;
    remote_tcping_port = 3389;

    // 初始化操作
    ui->send_ip_comboBox->addItem("Any IPv4");
    ui->send_ip_comboBox->addItem("Any IPv6");
    const QList<QHostAddress> all_local_ip = QNetworkInterface::allAddresses();
    // availableAddresses.reserve(ipAddressesList.size());
    for (const QHostAddress &ip : all_local_ip) {
        if (ip != QHostAddress::LocalHost && ip != QHostAddress::LocalHostIPv6) {
            // availableAddresses.push_back(ip);
            ui->send_ip_comboBox->addItem(ip.toString());
        }
    }

    // 信号槽绑定
    connect(this, &WOL::signal_gen, &wake_object, &WAKEONLAN::generate_magicpacket);
    connect(this, &WOL::signal_wake_ip, &wake_object, &WAKEONLAN::wake_on_ip);
    connect(&wake_object, &WAKEONLAN::signal_set_status, this, &WOL::set_online_status);

    // 启动多线程
    wake_object.moveToThread(&wakeonlan_worker);
    wakeonlan_worker.start();

}

WOL::~WOL()
{
    wakeonlan_worker.deleteLater();
    wakeonlan_worker.wait();
    delete ui;
}


void WOL::on_wakeup_pushButton_clicked()
{
    QString send_ip_string = ui->send_ip_comboBox->currentText();
    if (send_ip_string == "Any IPv4")
        send_ip = QHostAddress("0.0.0.0");
    else if (send_ip_string == "Any IPv6")
        send_ip = QHostAddress("::");
    else
        send_ip = QHostAddress(send_ip_string);

    QString remote_ip_string = ui->remote_ip_lineEdit->text();
    if (remote_ip_string != "")
        remote_ip = QHostAddress(remote_ip_string);

    QString remote_port_string = ui->remote_port_lineEdit->text();
    if (remote_port_string != "")
        remote_port = remote_port_string.toUInt();

    remote_mac = ui->remote_mac_lineEdit->text();

    emit signal_wake_ip(send_ip, remote_ip, remote_port, remote_mac);

//    emit signal_gen(QString::fromStdString("D85ED3247159"));
}


void WOL::on_send_ip_comboBox_clicked()
{
    qDebug() << "Activated ComboBox";
    ui->send_ip_comboBox->clear();
    ui->send_ip_comboBox->addItem("Any IPv4");
    ui->send_ip_comboBox->addItem("Any IPv6");

    const QList<QHostAddress> all_local_ip = QNetworkInterface::allAddresses();
    // availableAddresses.reserve(ipAddressesList.size());
    for (const QHostAddress &ip : all_local_ip) {
        if (ip != QHostAddress::LocalHost && ip != QHostAddress::LocalHostIPv6) {
            // availableAddresses.push_back(ip);
            ui->send_ip_comboBox->addItem(ip.toString());
        }
    }
}

void WOL::set_online_status(const bool is_online)
{
    if (is_online)
        online_label->updateUI(LedLabel::green);
    else
        online_label->updateUI(LedLabel::red);
}


void WOL::on_online_pushButton_clicked()
{
    // bool is_ip;
    // if (remote_ip.toIPv4Address())
    ui->online_pushButton->setText("请稍后...");
    ui->online_pushButton->setEnabled(false);

    if (QueryOnline(remote_ip))
        set_online_status(true);
    else
        set_online_status(false);

    ui->online_pushButton->setText("刷 新");
    ui->online_pushButton->setEnabled(true);
}

