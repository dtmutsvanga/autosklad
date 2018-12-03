#ifndef STORAGEDRAWER_H
#define STORAGEDRAWER_H
#include <QMainWindow>
#include <Qtcore>


//Change parnt class to suite application
#define PARENT_CLASS QPushButton
#define PARENT_CLASS_INCL <QPushButton>

// Include parent qt class
#include <QPushButton> //PARENT_CLASS_INCL

class QGridLayout;
class QVBoxLayout;
class QLabel;
class StorageItem;

typedef struct
{
	QString name;
	QString type;
	QString desc;
	QString dataSheetLink;
	int qty;
} Item_t;

class Drawer : public PARENT_CLASS {
	Q_OBJECT

public:
	explicit Drawer(PARENT_CLASS * parent = nullptr);
	~Drawer();

	// Flags
	bool contentsSet();
	bool commandsSet();

	// Graphics
	void setMinWidthHeight(int w, int h);
	void refreshSize();
	void setColor(QString &color);
	void setColorIndex(QString &color);
	void setColorBrief(QString &color);
	QList<Item_t> *getItems();

	//sklad items
	void setDrawerIndex(int &indx);
	void setDrawerContents(QList<Item_t> &contents);
	bool setIconPath(QString &path);
	void setBriefContents(QString &contents);
	void setOpenCloseCommands(QString &open, QString &close);
	void addItem(Item_t &item);
	void addItems(QList<Item_t> &items);


public slots:

private slots:
	//void slotClicked(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e) override;
signals:
	void sigClicked(Drawer *drawer, Qt::MouseButton btn);

protected:
	void initLayout();

private:

	// Graphical privat members
	//QGridLayout *m_grid_layout;
	QVBoxLayout *m_vbox_layout;
	QLabel *m_lblIndex;
	QLabel *m_lblBriefContent;

	// Data private members
	QString m_icon_path;
	QString m_briefContent;
	QList<Item_t> *m_contents;
	QPixmap *m_image;
	QLabel *lblImage;


	// Control params
	bool m_contentsSet = false;
	bool m_commandsSet = false;

	int m_index;
	QString m_openCmd;
	QString m_closeCmd;

};

#endif // STORAGEDRAWER_H
