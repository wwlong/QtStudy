#include "qtserialport.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QSerialPort>
#include <QObject>

/*
 * construct function
*/
QtSerialPort::QtSerialPort()
{
    //m_serial = new QSerialPort();
}
/*
    destruct function
*/
QtSerialPort::~QtSerialPort()
{
    //delete m_serial;
}

/*
    init Serial Port
*/
void QtSerialPort::initSerialPort()
{
//    SerialPortConfig SerialPortDefConfig = {
//        .name = "ttyUSB0",
//        .stringBaudRate = "115200",
//        .stringDataBits = "8",
//        .stringParity = "None",
//        .stringStopBits = "1",
//        .stringFlowControl = "None",
//        .localEchoEnabled = true
//    };
//    m_serial.setPortName(SerialPortDefConfig.name);
//    m_serial.setBaudRate(SerialPortDefConfig.stringBaudRate.toInt());
//    m_serial.setDataBits(static_cast<QSerialPort::DataBits>(SerialPortDefConfig.stringDataBits.toInt()));
//    m_serial.setParity(static_cast<QSerialPort::Parity>(SerialPortDefConfig.stringParity.toInt()));
//    m_serial.setStopBits(static_cast<QSerialPort::StopBits>(SerialPortDefConfig.stringStopBits.toInt()));
//    m_serial.setFlowControl(static_cast<QSerialPort::FlowControl>(SerialPortDefConfig.stringFlowControl.toInt()));

    m_serial.setPortName("ttyUSB0");
    m_serial.setBaudRate(QSerialPort::Baud115200);
    m_serial.setDataBits(QSerialPort::Data8);
    m_serial.setParity(QSerialPort::NoParity);
    m_serial.setStopBits(QSerialPort::OneStop);
    m_serial.setFlowControl(QSerialPort::NoFlowControl);
    if (m_serial.open(QIODevice::ReadWrite)) {
        qDebug() << "open success";
        //QObject::connect(m_serial, SIGNAL(readyRead()), this, SLOT(recSerialData())); // 连接串口收到数据事件与读取数据函数
        //m_console->setEnabled(true);
        //m_console->setLocalEchoEnabled(SerialPortDefConfig.localEchoEnabled);
        //m_ui->actionConnect->setEnabled(false);
        //m_ui->actionDisconnect->setEnabled(true);
        //m_ui->actionConfigure->setEnabled(false);
        /*showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
                          .arg(SerialPortDefConfig.name).arg(SerialPortDefConfig.stringBaudRate).arg(SerialPortDefConfig.stringDataBits)
                          .arg(SerialPortDefConfig.stringParity).arg(SerialPortDefConfig.stringStopBits).arg(SerialPortDefConfig.stringFlowControl));*/
    } else {
        //QMessageBox::critical(this, tr("Error"), m_serial.errorString());

        //showStatusMessage(tr("Open error"));
        qDebug("Open error\n");
    }
}
void QtSerialPort::openSerialPort()
{

}

void QtSerialPort::closeSerialPort()
{
    if (m_serial.isOpen()) {
        m_serial.close();
    }
}


int QtSerialPort::writeData(const QString &data, uint32_t timeout_ms = 500)
{
    //QByteArray writeData("1232141");

    if (data.isEmpty()) {
        qDebug() << "write data empty";
        return -1;
    }

    const qint64 bytesWritten = m_serial.write(data.toLatin1());

    if (bytesWritten == -1) {
        qDebug() << "bytesWritten == -1";
        return -1;
    } else if (bytesWritten != data.size()) {
        return bytesWritten;
    } else if (!m_serial.waitForBytesWritten(timeout_ms)) {

        return bytesWritten;
    }
    return 0;
}

int QtSerialPort::readData(QString &data, uint32_t timeout_ms=500)
{
     m_readData = m_serial.readAll();
     while (m_serial.waitForReadyRead(timeout_ms))
        m_readData.append(m_serial.readAll());

    if (m_serial.error() == QSerialPort::ReadError) {
        qDebug() << "QSerialPort::ReadError";
        return -1;
    } else if (m_serial.error() == QSerialPort::TimeoutError && m_readData.isEmpty()) {
        return 0;
    }
    data = m_readData;
    m_timer.start(5000);
    return data.size();
}

void QtSerialPort::handleReadyRead()
{
    m_readData.append(m_serial.readAll());

    if (!m_timer.isActive())
        m_timer.start(5000);
}

void QtSerialPort::handleTimeout()
{
    if (m_readData.isEmpty()) {
        //m_standardOutput << QObject::tr("No data was currently available for reading from port %1").arg(m_serialPort->portName()) << endl;
    } else {
        //m_standardOutput << QObject::tr("Data successfully received from port %1").arg(m_serialPort->portName()) << endl;
        //m_standardOutput << m_readData << endl;
        qDebug() << m_readData ;
    }

    //QCoreApplication::quit();
}

void QtSerialPort::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << "QSerialPort::ReadError";
        return ;
        //m_standardOutput << QObject::tr("An I/O error occurred while reading the data from port %1, error: %2").arg(m_serialPort->portName()).arg(m_serialPort->errorString()) << endl;
       // QCoreApplication::exit(1);

    }
}
