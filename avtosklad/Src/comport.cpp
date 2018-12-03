#include "comport.h"
#include <QMessageBox>
#include <string>


ComPort::ComPort(QObject *parent) : QSerialPort(parent)
{
	m_txDataBuffer = new QList<QString>;
	m_rxDataBuffer = new QList<QString>;
	m_parity = NoParity;
	m_br = Baud9600;
	m_portName = "";
	m_isConnected = false;

	connect(this, QSerialPort::readyRead, this, ComPort::handleReadyRead);

}

bool ComPort::status()
{
	m_isConnected = this->isOpen();
	return m_isConnected;
}

QList<QString> ComPort::getAvailableports()
{
	QList<QString> ports;
	const auto infos = QSerialPortInfo::availablePorts();

	for (const QSerialPortInfo &info : infos)
		ports.append(info.portName());

	return ports;
}

void ComPort::setPortSettings(QSerialPort::BaudRate baudrate, QSerialPort::Parity parity)
{
	this->setBaudRate(baudrate);
	this->setParity(parity);
}

bool ComPort::connectPort(const QString &portName)
{
	setPortName(portName);
	bool ret =  this->open(QIODevice::ReadWrite);
	this->clear(QSerialPort::AllDirections);
	m_isConnected = ret;
	return ret;
}

void ComPort::closePort()
{
	if(m_isConnected){
		this->close();
		this->clearBuffers();
		m_isConnected = false;
	}

}

bool ComPort::txData(QString &txStr)
{
	if(m_isConnected)
	{
		QString msg = QString("Port %1 is not connected"
							  "Please check the connection").arg(m_portName);
		QMessageBox::critical(nullptr, tr("Connection"), msg);
		return false;
	}
	QByteArray txData = txStr.toUtf8();
	this->write(txData);
	m_txDataBuffer->append(txStr);
	return true;
}

void ComPort::getAllRxData(QList<QString> *rxData)
{
	rxData = m_rxDataBuffer;
}

void ComPort::handleReadyRead()
{
	QByteArray rx_bytearray = this->readAll();
	QString rx = QString(rx_bytearray);

	if(!rx.isEmpty()){
		m_txDataBuffer->append(rx);
		emit dataReceived(rx);
	}
}

void ComPort::clearBuffers()
{
	if(!m_txDataBuffer->isEmpty())
		m_txDataBuffer->clear();

	if(!m_rxDataBuffer->isEmpty())
		m_rxDataBuffer->clear();

	//this->flush();
}


void ComPort::saveToRxBuffer(QString &rxStr)
{
	m_rxDataBuffer->append(rxStr);
}
