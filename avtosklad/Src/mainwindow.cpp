#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QScrollArea>
#include <QtCore>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->dockLeft->setWindowTitle(tr("Storage Contents"));
	//ui->dockConnection->setWindowTitle(tr("Connection Settings"));
	this->setStyleSheet("QMainWindow, QToolBar{ border: 1px solid #6593cf;"
						"border-radius: 20px;"
						"padding: 5px 15px 2px 5px;"
						"background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,"
						"stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);"
						"color: #006aff;"
						"font: bold large \"Arial\";"
						"height: 30px;"
						"}");
	ui->edtConsole->setStyleSheet("background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,"
								  "stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);"
								  "color: #006aff;"
								  "font: bold large \"Arial\";"
								  "height: 30px;");



	ui->wdgtControls->setStyleSheet(".QWidget { border-color: black;"
									"border-width: 2px;"
									"border-style: solid;}");
	ui->tabRight->setStyleSheet(".QWidget {background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,"
								"stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);"
								"color: #000000;}");
	ui->tableWidget->setStyleSheet("border-color: black;"
									"border-width: 2px;"
									"border-style: solid;"
								   "border-raduis: 20px");

	ui->tabContents->setStyleSheet("QWidget {background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,"
								  "stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);"
								  "color: #000000;"
								  "border-style: solid;"
								  "border-color: white;"
								  "border-width: 1px}");
//	ui->scrollArea->setStyleSheet(".QWidget {background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,"
//								  "stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);"
//								  "color: #000000;"
//								  "border-style: solid;"
//								  "border-color: white;"
//								  "border-width: 0px}");

	// Create comport manager
	m_comport = new ComPort;

	// Create list for drawers
	m_drawers = new QList<DRAWER_TYPE*>;

	// Setup UI grid
	m_central_widget = new QWidget(this);

	//setup layout
	m_cw_layout = new QGridLayout(ui->centralWidget);
	m_cw_layout->setHorizontalSpacing(5);
	m_cw_layout->setVerticalSpacing(1);

	m_central_widget->setLayout(m_cw_layout);
	ui->scrollArea->setWidget(m_central_widget);

	// TODO: Upload settings, if absent set default

	// Create the drawer area
	createDrawers(95, 10, 10, 75, 70);
	refreshComPorts();

	//connect signals, slots
	connect(ui->btnConnect, QPushButton::clicked, this, onConnect);
	connect(ui->btnRefreshPorts, QPushButton::clicked, this, refreshComPorts);
	connect(m_comport, ComPort::dataReceived, this, onCommunicationEvents);
	connect(ui->comboBaudRAte, QOverload<int>::of(&QComboBox::currentIndexChanged), this, onComboSeriaIndexlChanged);
	connect(ui->comboPortName, QOverload<int>::of(&QComboBox::currentIndexChanged), this, onComboSeriaIndexlChanged);
	connect(ui->actionConnect, QAction::triggered, this, onConnect);

}
bool MainWindow::openSettings(QString &path)
{
	return true;
}

void MainWindow::createDrawers(int num, int rows, int cols, int width_drwr, int height_drwr)
{
	DRAWER_TYPE *drwr = nullptr;
	int ctr = 0;
	for(int i = 0; i< rows; i++){
		for(int j = 0; j< cols; j++){
			if(ctr < num )
			{
				ctr++;
				drwr = new DRAWER_TYPE;
				drwr->setDrawerIndex(ctr);
				drwr->setMinimumHeight(height_drwr);
				drwr->setMinimumWidth(width_drwr);
				m_cw_layout->addWidget(drwr, i, j);
			}
		}
	}
	m_central_widget->adjustSize();
}

void MainWindow::refreshComPorts()
{
	QList<QString> ports = m_comport->getAvailableports();
	ui->comboPortName->clear();
	ui->comboPortName->addItems(QStringList(ports));
}

MainWindow::~MainWindow()
{
	delete ui;
}


void MainWindow::onConnect()
{
	if(m_comport->status())
	{
		m_comport->closePort();
		ui->btnConnect->setText(tr("Connect"));
	}

	else {
		// get Baud rate
		QSerialPort::BaudRate br;
		switch (ui->comboBaudRAte->currentIndex())
		{
		case 0:
			br = QSerialPort::Baud9600;
			break;
		case 1:
			br = QSerialPort::Baud1200;
			break;
		case 2:
			br = QSerialPort::Baud2400;
			break;
		case 3:
			br = QSerialPort::Baud4800;
			break;
		case 4:
			br = QSerialPort::Baud19200;
			break;
		case 5:
			br = QSerialPort::Baud38400;
			break;
		case 6:
			br = QSerialPort::Baud57600;
			break;
		case 7:
			br = QSerialPort::Baud115200;
			break;
		default:
			br = br = QSerialPort::UnknownBaud;
			break;
		}

		if(br == QSerialPort::UnknownBaud)
		{
			QMessageBox::critical(this, tr("Connection"), tr("Please select an appropriate baud rate"));
			return;
		}

		//Port name
		QString portName = ui->comboPortName->currentText();
		if(portName.simplified()=="")
		{
			QMessageBox::critical(this, tr("Connection"),tr("Please select a port"));
			return;
		}

		m_comport->setPortSettings(br);
		if(m_comport->connectPort(portName))
		{
			ui->btnConnect->setText(tr("Disconnect"));

		}
	}
}

void MainWindow::onCommunicationEvents(QString message)
{
	//get time
	static QDateTime prevDateTime = QDateTime::currentDateTime();
	QDateTime dateTime = QDateTime::currentDateTime();
	static QString localBuff;

	//QString dateTime = QDateTime::currentDateTime().toString(Qt::SystemLocaleLongDate);
	if( dateTime.toMSecsSinceEpoch() - prevDateTime.toMSecsSinceEpoch() > 100)
	{
			ui->edtConsole->append(QString("[%1]: %2%3 ")
						   .arg(prevDateTime.toString(Qt::SystemLocaleLongDate))
						   .arg(localBuff).arg("\r\n"));

			localBuff.clear();
			localBuff.append(message);

		prevDateTime = dateTime;
	}

	else
	{
		localBuff.append(message);
		//prevDateTime = dateTime;
	}
}

void MainWindow::onComboSeriaIndexlChanged()
{
	if(m_comport->isOpen())
	{
		ui->btnConnect->setText("Connect");
		m_comport->closePort();
		this->onConnect();
	}
}
