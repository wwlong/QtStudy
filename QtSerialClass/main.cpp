#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include "qtserialport.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //initSerialPort
    QtSerialPort serialPort1;
    serialPort1.initSerialPort();
    serialPort1.openSerialPort();
    //timer = new QTimer(this);
    //connect(timer, SIGNAL(timeout()), this, SLOT(readComDataSlot()));
    QString readDataBuf;
    uint32_t timeout_ms = 500;
    serialPort1.readData(readDataBuf, timeout_ms);
    qDebug() << readDataBuf;
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz ddd");
    qDebug() << current_date;
    serialPort1.writeData(current_date, timeout_ms);
    serialPort1.closeSerialPort();
    qDebug("app end");
    return a.exec();
}
