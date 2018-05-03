#include <QCoreApplication>
#include <QDateTime>
#include <QDebug>
#include "qtserialport.h"
/*
    Qt SerialPort demo
    1.  init
    2.  open
    3.  read
    4.  write
    5.  close
*/
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //initSerialPort
    SerialPortConfig serialPortDefConfig = {
        .name = "ttyUSB0",
        .serialbaudRate = QSerialPort::Baud115200,
        .serialDataBits = QSerialPort::Data8,
        .serialParity = QSerialPort::NoParity,
        .serialStopBits = QSerialPort::OneStop,
        .serialFlowControl = QSerialPort::NoFlowControl
    };
    QtSerialPort serialPort1;
    serialPort1.initSerialPort(serialPortDefConfig);
    serialPort1.openSerialPort();
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
    return 0;
}
