#ifndef SensorDatabase_H
#define SensorDatabase_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QStringList>
#include <QDateTime>
#include <QSqlDriver>
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QSqlError>
#include <QRegularExpression>
#include <QCoreApplication>
#include <QSqlRecord>
#include <libpq-fe.h>
#include <QVector>
#include <QSqlResult>
#include <QPointF>



struct SensorInfo
{
    double dispersio=0;
    double average=0;
    QVector <double> data;
};


struct connectionData
{
    QString dbName;
    QString userName;
    QString password;
    QString host;
    quint32 port;
};







/*класс exception для SensorDatabase*/
class SensorException : public std::exception
{
public:
    SensorException(const std::string &&whatStr) noexcept : whatStr(std::move(whatStr)) { }
    SensorException(const std::string &whatStr) noexcept : whatStr(whatStr) { }
    ~SensorException() noexcept=default;

    const char* what() const noexcept override
    {
        return whatStr.c_str();
    }

private:
    std::string whatStr;
};




class SensorDatabase : public QObject
{
    Q_OBJECT


public:
    explicit SensorDatabase(QString dbDriver="QPSQL",QObject *parent = 0);
    SensorDatabase(const SensorDatabase&)                   =delete;
    SensorDatabase(SensorDatabase&& )                       =delete;
    SensorDatabase& operator=(const SensorDatabase&)        =delete;
    SensorDatabase& operator=(SensorDatabase&&)             =delete;

    bool connectDb(const connectionData& cData);
    bool isDriverValid() const;
    bool isConnected() const;
    void analyzeDb();
    void disconnectDb();
    void loadIndications(const QVector<QVector<double>>& dataVector, const QString &note);
    SensorInfo getSensorInfo(const QString& channelName);
    void saveCSV(const QString& fileName);
    QPair<QDateTime,QDateTime> getMinMaxDateTime();
    QStringList getComments ();

    void setCurrentFilter(const QString & filter)
    {
        currentFilter=filter;
    }


    QString getCurrentFilter()
    {
       return currentFilter;
    }


    ~SensorDatabase();




signals:
    void dataSendedToServer();

private:
    QString currentFilter="";
    QSqlDatabase db;
    connectionData connData;

};

#endif // SensorDatabase_H
