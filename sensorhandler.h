#ifndef SENSORHANDLER_H
#define SENSORHANDLER_H
#include <QVector>
#include "plant.h"
#include <QValidator>
//class SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)=0;
//};

//class SensorOneHandler: public SensorHandler
//{
//public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//        Plant plant;
//        plant_init(plant);
//        QVector <double> evidenceVector;

//        for(const int i=0;i<requestCount;i++)
//        {
//            evidenceVector.append(plant_measure(1, plant));
//        }

//        return evidenceVector;
//    }

//};

//class SensorTwoHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {
//        Plant plant;
//        plant_init(plant);
//        QVector <double> evidenceVector;

//        for(const int i=0;i<requestCount;i++)
//        {
//            double sensorData=(plant_measure(2, plant)-30)/70;
//            evidenceVector.append(sensorData);
//        }

//        return evidenceVector;
//    }

//};


//class SensorThreeHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {
//        Plant plant;
//        plant_init(plant);
//        QVector <double> evidenceVector;

//        for(const int i=0;i<requestCount;i++)
//        {
//            evidenceVector.append(plant_measure(3, plant));
//        }

//        return evidenceVector;
//    }

//};

//class SensorFourHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {
//        Plant plant;
//        plant_init(plant);
//        QVector <double> evidenceVector;

//        for(const int i=0;i<requestCount;i++)
//        {
//            evidenceVector.append(plant_measure(4, plant));
//        }

//        return evidenceVector;
//    }

//};


//class SensorFiveHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {
//        Plant plant;
//        plant_init(plant);
//        QVector <double> evidenceVector;

//        for(const int i=0;i<requestCount;i++)
//        {
//            double sensorData=plant_measure(5, plant);
//            if(sensorData>1 && sensorData<3)
//            {
//            evidenceVector.append(sensorData);
//            }
//        }

//        return evidenceVector;
//    }

//};


//class SensorSixHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};


//class SensorNineHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};


//class SensorNineTeenHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};


//class SensorFourtyNineHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};



//class SensorSixtyNineHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};


//class SensorSeventySevenHandler: public SensorHandler
//{
//    public:
//    virtual QVector<double> requesteEvidence(const int requestCount)
//    {

//    }

//};


#endif // SENSORHANDLER_H
