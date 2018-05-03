#include "qtserialport.h"
#include <QSerialPortInfo>
#include <QDebug>
#include <QSerialPort>
#include <QObject>

/*
 * construct function
*/
//QtSerialPort::QtSerialPort(SerialPortConfig serialPortConfig)
//{
//    serialPortConfigInternal = serialPortConfig;
//    m_serial.setPortName(serialPortConfigInternal.name);
//    m_serial.setBaudRate(serialPortConfigInternal.serialbaudRate);
//    m_serial.setDataBits(serialPortConfigInternal.serialDataBits);
//    m_serial.setParity(serialPortConfigInternal.serialParity);
//    m_serial.setStopBits(serialPortConfigInternal.serialStopBits);
//    m_serial.setFlowControl(serialPortConfigInternal.serialFlowControl);
//}
QtSerialPort::QtSerialPort()
{

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
void QtSerialPort::initSerialPort(SerialPortConfig serialPortConfig)
{
    serialPortConfigInternal = serialPortConfig;
    m_serial.setPortName(serialPortConfigInternal.name);
    m_serial.setBaudRate(serialPortConfigInternal.serialbaudRate);
    m_serial.setDataBits(serialPortConfigInternal.serialDataBits);
    m_serial.setParity(serialPortConfigInternal.serialParity);
    m_serial.setStopBits(serialPortConfigInternal.serialStopBits);
    m_serial.setFlowControl(serialPortConfigInternal.serialFlowControl);
}
/*
    open serial port
*/
void QtSerialPort::openSerialPort()
{
    if (m_serial.open(QIODevice::ReadWrite)) {
        qDebug() << "open success";
    } else {
        qDebug("Open error\n");
    }
}

/*
    close serial port
*/
void QtSerialPort::closeSerialPort()
{
    if (m_serial.isOpen()) {
        m_serial.close();
    }
}
/**
* @brief    write data
* @param
*   const QString &data, data to be writen
*   uint32_t timeout_ms = 500 , timeout ms
* @retval
*   -1, failed
*   0,timeout
*   other > 0, writen data length
*/
int QtSerialPort::writeData(const QString &data, uint32_t timeout_ms = 500)
{
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
/**
* @brief read data
* @param
*   QString &data,buffer to save data
*   uint32_t timeout_ms=500, timeout for rad data
* @retval
*   -1, failed
*   0, timeout
*   other > 0 value, readed data length
*/

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
/**
* @brief
*   error handler
* @param
*   QSerialPort::SerialPortError serialPortError,error return from QtSerialPort
* @retval
*   none
*/

void QtSerialPort::handleError(QSerialPort::SerialPortError serialPortError)
{
    if (serialPortError == QSerialPort::ReadError) {
        qDebug() << "QSerialPort::ReadError";
        return ;
    }
}
