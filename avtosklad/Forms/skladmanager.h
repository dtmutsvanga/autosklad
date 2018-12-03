#ifndef SKLADMANAGER_H
#define SKLADMANAGER_H

#include <QWidget>


class QToolBar;

namespace Ui {
class skladManager;
}

class SkladManager : public QWidget
{
	Q_OBJECT

public:
	explicit SkladManager(QWidget *parent = 0);
	~SkladManager();

private:
	Ui::skladManager *ui;

	QToolBar *m_toolBar ;
};

#endif // SKLADMANAGER_H
