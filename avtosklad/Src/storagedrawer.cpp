#include "storagedrawer.h"
#include <QVBoxLayout>
#include <QtGui>
#include <QLabel>
#include <QSpacerItem>
Drawer::Drawer(PARENT_CLASS *parent) : PARENT_CLASS(parent)
{
	// Graphical privat members
	// m_grid_layout = new QGridLayout(this);
	m_vbox_layout = new QVBoxLayout(this) ;
	m_lblIndex = new QLabel(this);
	m_lblBriefContent = new QLabel(this) ;
	m_image = new QPixmap;
	lblImage = new QLabel(this) ;


	// Data private members
	m_contents = new QList<Item_t>;
	m_briefContent = "";
	m_icon_path = "";
	m_index = -1;

	//
	initLayout();
	//connect(this, QPushButton::mousePressEvent, this, slotClicked);
}

Drawer::~Drawer()
{
	delete m_contents;
	delete m_image;

}



void Drawer::setDrawerIndex(int &indx)
{
	m_index = indx;
	m_lblIndex->setText(QString("%1").arg(m_index));
}

void Drawer::setDrawerContents(QList<Item_t> &contents)
{
	m_contents = &contents;
}

bool Drawer::setIconPath(QString &path)
{
	return m_image->load(path);
}

void Drawer::setMinWidthHeight(int w, int h)
{
	this->setMinimumWidth(w);
	this->setMinimumHeight(h);
}

void Drawer::refreshSize()
{
	this->adjustSize();
}

void Drawer::setColor(QString &color)
{
	this->setStyleSheet(QString("background-color: %1").arg(color));
}

void Drawer::setColorIndex(QString &color)
{
	m_lblIndex->setStyleSheet(QString("QLabel {color : %1; }").arg(color));
}

void Drawer::setColorBrief(QString &color)
{
	m_lblBriefContent->setStyleSheet(QString("QLabel {color : %1; }").arg(color));
}

void Drawer::setBriefContents(QString &contents)
{
	m_briefContent = contents;
	m_lblBriefContent->setText(m_briefContent);
}

void Drawer::setOpenCloseCommands(QString &open, QString &close)
{
	m_openCmd = open;
	m_closeCmd = close;

	if(!m_commandsSet)
		m_commandsSet = true;
}

void Drawer::addItem(Item_t &item)
{
	m_contents->append(item);
}

void Drawer::addItems(QList<Item_t> &items)
{
	m_contents->append(items);
}

QList<Item_t> *Drawer::getItems()
{
	return m_contents;
}

bool Drawer::contentsSet()
{
	return m_contentsSet;
}

bool Drawer::commandsSet()
{
	return m_commandsSet;
}



void Drawer::mousePressEvent(QMouseEvent *e)
{
	emit sigClicked(this, e->button());
}


void Drawer::initLayout(){

	this->setLayout(m_vbox_layout);

	// Index Label
	m_lblIndex->setText(QString("%1").arg(m_index));
	m_lblIndex->setAlignment(Qt::AlignRight);
	m_vbox_layout->addWidget(m_lblIndex,0,Qt::AlignRight);

	// Icon Label
	m_image->load("icons\\sparkfun-discretesemi.png");
	lblImage->setPixmap(*m_image);
	lblImage->setMinimumSize(QSize(35,35));
	lblImage->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
	//lblImage->setAlignment();
	//lblImage->set
	m_vbox_layout->addWidget(lblImage,0,Qt::AlignHCenter|Qt::AlignTop);

	// Brief contents
	if(m_briefContent.simplified() != "")
		m_lblBriefContent->setText(m_briefContent);
	else
		m_lblBriefContent->setText(tr("Empty"));
m_lblBriefContent->setAlignment(Qt::AlignLeft);
//	QSpacerItem *spacer = new QSpacerItem;
//	QSpa
	//m_vbox_layout->insertStretch(2);
	m_vbox_layout->addWidget(m_lblBriefContent,0,Qt::AlignLeft);

	this->setStyleSheet("QPushButton:hover{\
						background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #ffd9aa,\
								stop :   0.5 #ffbb6e, stop :   0.55 #feae42, stop :   1.0 #fedb74);\
				}\
				QPushButton {\
						border: 2px solid #000000;\
						border-radius: 15px;\
						padding: 5px 15px 2px 5px;\
						background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #f5f9ff,\
								stop :   0.5 #c7dfff, stop :   0.55 #afd2ff, stop :   1.0 #c0dbff);\
						color: #006aff;\
						font: bold large \"Arial\";\
						height: 30px;\
				}\
				QPushButton:pressed {\
						background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #c0dbff,\
						stop :   0.5 #cfd26f, stop :   0.55 #c7df6f, stop :   1.0 #f5f9ff);\
						padding-top: 2px;\
						padding-left: 3px;\
				}\
				QPushButton:on {\
						background: qlineargradient(x1 : 0, y1 : 0, x2 : 0, y2 :   1, stop :   0.0 #5AA72D,\
						stop :   0.5 #B3E296, stop :   0.55 #B3E296, stop :   1.0 #f5f9ff);\
						padding-top: 2px;\
						padding-left: 3px;\
				}\
				QPushButton:disabled {\
						background: transparent #e5e9ee;\
						padding-top: 2px;        \
						padding-left: 3px;\
						color: black;\
				}");

				//this->adjustSize();

}
