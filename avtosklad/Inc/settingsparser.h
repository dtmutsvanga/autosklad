#ifndef SETTINGSPARSER_H
#define SETTINGSPARSER_H

#include <QtCore>
#include <QDomDocument>
/*
 *  @author : Mutsvanga Dan Tarisai
 *  @brief: Class declarations for settings parsing for Autosklad system
 *
 * */
typedef struct{
    QString label;
    int baudrate;
    bool parity;
}comPortSettings_t;

class SettingsParser : public QObject{
    Q_OBJECT
public:
    explicit SettingsParser(QObject *parent = nullptr);
    int parseSettings();

public slots:
    int getRowsCols(int &row, int &cols, int &numDrawers);
    void setSettingsPath(QString path);
    bool getUsers();

protected:
    bool openFile(QString path);

private:
    QString m_settingsPath;
    QDomDocument *m_settingsXML;
    int rows;
    int cols;
    QList<QString> *m_userDatabases;
    QList<QString> *m_componentsDataBases;
    QString m_connType;
    comPortSettings_t m_compportSettings;
};

#endif // SETTINGSPARSER_H
