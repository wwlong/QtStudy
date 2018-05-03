#ifndef QTSERIALPORT_H
#define QTSERIALPORT_H

#include <QDialog>
#include <QSerialPort>
#include <QTimer>
#include <QByteArray>
typedef struct{
    QString name;
    QSerialPort::BaudRate serialbaudRate;
    QSerialPort::DataBits serialDataBits;
    QSerialPort::Parity serialParity;
    QSerialPort::StopBits serialStopBits;
    QSerialPort::FlowControl serialFlowControl;
}SerialPortConfig;

class QtSerialPort //: public QObject
{
    //Q_OBJECT
public:
    //QtSerialPort(SerialPortConfig serialPortConfig);
    QtSerialPort();
    ~QtSerialPort();
public slots:
    void initSerialPort(SerialPortConfig serialPortConfig);
    void openSerialPort();
    void closeSerialPort();
    int writeData(const QString &data, uint32_t timeout_ms);
    int readData(QString &data, uint32_t timeout_ms);
    void handleError(QSerialPort::SerialPortError error);

private:
    QSerialPort m_serial;
    QByteArray  m_readData;
    QByteArray  m_writeData;
    QTimer      m_timer;
    SerialPortConfig serialPortConfigInternal;
};

#endif // QTSERIALPORT_H
