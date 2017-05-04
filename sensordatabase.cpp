#include "sensordatabase.h"
#include <QDebug>

SensorDatabase::SensorDatabase(QString dbDriver,QObject *parent) : QObject(parent)
{
    db=QSqlDatabase::addDatabase(dbDriver);

}


//CREATE TABLE public.sensor
//(
//  datetime timestamp without time zone NOT NULL,
//  username text NOT NULL,
//  sen1 double precision,
//  sen2 double precision,
//  sen3 double precision,
//  sen4 double precision,
//  sen5 double precision,
//  sen6 double precision,
//  sen7 double precision,
//  sen8 double precision,
//  sen9 double precision,
//  sen10 double precision,
//  sen11 double precision,
//  note text NOT NULL
//)
//WITH (
//  OIDS=FALSE
//);
//ALTER TABLE public.sensor
//  OWNER TO postgres;


bool SensorDatabase::connectDb(const connectionData &cData)
{

    if(!isDriverValid())
    {
        throw SensorException("Драйвер не подключен");
    }
    db.setHostName(cData.host);
    db.setPort(cData.port);
    db.setDatabaseName(cData.dbName);
    db.setUserName(cData.userName);
    db.setPassword(cData.password);
    connData=cData;
    return db.open();

}




bool SensorDatabase::isDriverValid() const
{
    return db.isDriverAvailable("QPSQL")&& db.isValid();
}




void SensorDatabase::disconnectDb()
{
    db.close();
}




bool SensorDatabase::isConnected() const
{
    return db.isOpen();
}



SensorDatabase::~SensorDatabase()
{
    disconnectDb();
}


void SensorDatabase::loadIndications(const QVector<QVector<double>> &dataVector,const QString& note)

{
    if(!isConnected())
    {
        throw SensorException("Соединение с БД не установлено.");
    }

    QSqlQuery query;
    QString loadDateTime=QDateTime::currentDateTime().toString(Qt::ISODate);
    query.prepare("INSERT INTO sensor("
                  "datetime, username, sen1, sen2, sen3, sen4, sen5, sen6, sen7, sen8, sen9, sen10, sen11, note)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
    int countOfFrames=dataVector[0].size();


    QHash<QString,QString> hashUserName;
    hashUserName["Boris Yumatov"]="Борис Юматов";
    hashUserName["Dmitry Kondrashin"]="Дмитрий Кондрашин";

    for(int i=0;i<countOfFrames;i++)
    {
        query.addBindValue(loadDateTime);
        query.addBindValue(hashUserName[connData.userName]);
        for(int j=0;j<dataVector.size();j++)
        {
            query.addBindValue(dataVector[j][i]);
        }
        query.addBindValue(note);
        if(!query.exec())
        {
            throw SensorException(query.lastError().text().toStdString());
        }

    }

}

QStringList SensorDatabase::getComments ()
{
    if(!isConnected())
    {
        throw SensorException("Соединение с БД не установлено.");
    }

    QSqlQuery query;
    if(!query.exec(QString("SELECT note from sensor GROUP BY note;")))

    {
        throw SensorException(query.lastError().text().toStdString());
    }
    QStringList list;
    while(query.next())
    {
        list.append(query.value(0).toString());
    }
    return list;
}


SensorInfo SensorDatabase::getSensorInfo(const QString& channelName)
{

    if(!isConnected())
    {
        throw SensorException("Соединение с БД не установлено.");
    }

    QString filter=this->getCurrentFilter();
    if(!filter.isEmpty())
    {
        filter=QString("WHERE " + filter);
    }
    QSqlQuery query;
    if(!query.exec(QString("SELECT AVG(%1),VARIANCE(%1) from sensor %2;")
                   .arg(channelName).arg(filter)))
    {
        throw SensorException(query.lastError().text().toStdString());
    }
    SensorInfo info;
    query.next();
    info.average=query.value(0).toDouble();
    info.dispersio=query.value(1).toDouble();

    if(!query.exec(QString("SELECT %1 from sensor %2;")
                   .arg(channelName).arg(filter)))
    {
        throw SensorException(query.lastError().text().toStdString());
    }
    while(query.next())
    {
        info.data.append(query.value(0).toDouble());
    }
    return info;


}

void SensorDatabase::saveCSV(const QString& fileName)
{
    if(!isConnected())
    {
        throw SensorException("Соединение с БД не установлено.");
    }

    QSqlQuery query;
    if(!query.exec(QString("COPY (SELECT * FROM sensor WHERE %1) TO '%2' WITH CSV DELIMITER ',';")
            .arg(getCurrentFilter()).arg(fileName)))
    {
        throw SensorException(query.lastError().text().toStdString());
    }
}

QPair<QDateTime,QDateTime> SensorDatabase::getMinMaxDateTime()
{
    if(!isConnected())
    {
        throw SensorException("Соединение с БД не установлено.");
    }

    QSqlQuery query;

    if(!query.exec("SELECT min(datetime), max(datetime) FROM sensor;"))
    {
        throw SensorException(query.lastError().text().toStdString());
    }
    QPair<QDateTime,QDateTime> minMaxDateTime;
    query.next();
    minMaxDateTime.first=QDateTime::fromString(query.value(0).toString(),Qt::ISODate);
    minMaxDateTime.second=QDateTime::fromString(query.value(1).toString(),Qt::ISODate);

    return minMaxDateTime;

}


