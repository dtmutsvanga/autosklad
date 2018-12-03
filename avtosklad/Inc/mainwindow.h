#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "storagedrawer.h"
#include "comport.h"
#include "ui_mainwindow.h"
namespace Ui {
class MainWindow;
}

#define DRAWER_TYPE Drawer

class QPushButton;
class QGridLayout;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
	bool openSettings(QString &path);
	void createDrawers(int num, int rows, int cols, int width_drwr = 100, int height_drwr = 75);
	void refreshComPorts();

    ~MainWindow();


public slots:
	//void onListPortsrefresh();
	void onConnect();
	void onCommunicationEvents(QString message);
	void onComboSeriaIndexlChanged();
private:
    Ui::MainWindow *ui;
	QGridLayout *m_cw_layout;
	QList<DRAWER_TYPE *> *m_drawers;
	QWidget *m_central_widget;
	ComPort *m_comport;
};

#endif // MAINWINDOW_H
