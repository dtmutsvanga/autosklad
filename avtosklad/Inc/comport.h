#ifndef COMPORT_H
#define COMPORT_H

#include <QtSerialPort>
#include <QSerialPortInfo>
#include "dialog.h"

//typedef class Dialog ComPort;

class ComPort : public QSerialPort
{
	Q_OBJECT
public:
	explicit ComPort(QObject *parent = nullptr);
	bool status() ;

public slots:
	QList<QString> getAvailableports();
	void setPortSettings(BaudRate baudrate = QSerialPort::Baud9600, QSerialPort::Parity parity = NoParity);
	bool connectPort(const QString &portName);
	void closePort();
	bool txData(QString &txStr);
	void getAllRxData(QList<QString> *rxData);
	void handleReadyRead();
	void clearBuffers();
private slots:
	void saveToRxBuffer(QString &rxStr);
signals:
	void isConnected(bool connected);
	void isSendSuccess(bool success, QString data);
	void dataReceived(QString rx);

private:
	QList<QString> *m_txDataBuffer;
	QList<QString> *m_rxDataBuffer;
	BaudRate m_br;
	Parity m_parity;
	QString m_portName;
	int m_waitTimeout;
	bool m_isConnected;

};

#endif // COMPORT_H
