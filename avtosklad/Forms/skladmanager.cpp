#include "skladmanager.h"
#include "ui_skladmanager.h"
#include <QToolBar>

SkladManager::SkladManager(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::skladManager)
{
	ui->setupUi(this);
	m_toolBar = new QToolBar;



	this->layout()->addWidget(m_toolBar);
}

SkladManager::~SkladManager()
{
	delete ui;
}
