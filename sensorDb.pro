   #-------------------------------------------------
#
# Project created by QtCreator 2017-01-07T19:54:49
#
#-------------------------------------------------

QT   += core gui
QT   +=   sql
QT   += charts
QMAKE_CXXFLAGS_WARN_ON += -Wno-reorder
CONFIG += warn_on
win32:QMAKE_CXXFLAGS_WARN_ON += -Wpedantic
win32:QMAKE_CXXFLAGS_WARN_ON += -Wall
win32:QMAKE_CXXFLAGS_WARN_ON += -Wextra
QMAKE_LFLAGS += -Wl,--large-address-aware


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SensorYumatov
TEMPLATE = app
CONFIG += c++14
win32:RC_FILE = icon.rc
SOURCES += main.cpp\
    mainwindow.cpp \
    connectiondialog.cpp \
    sensordatabase.cpp \
    sensordataloadwindow.cpp \
    plant.c \
    sensortablewindow.cpp \
    intervalwindow.cpp \
    cartesianplotter.cpp \
    chartplotter.cpp \
    chartview.cpp \
    xyseriesfactory.cpp \
    xyseriesplotter.cpp \
    analyzewindow.cpp \
    preparefilterwindow.cpp

HEADERS  += \
    mainwindow.h \
    connectiondialog.h \
    mathfunc.h \
    sensordatabase.h \
    sensordataloadwindow.h \
    plant.h \
    sensortablewindow.h \
    intervalwindow.h \
    cartesianplotter.h \
    chartplotter.h \
    chartview.h \
    xyseriesfactory.h \
    xyseriesplotter.h \
    analyzewindow.h \
    preparefilterwindow.h


FORMS    += \
    mainwindow.ui \
    connectiondialog.ui \
    sensordataloadwindow.ui \
    sensortablewindow.ui \
    intervalwindow.ui \
    analyzewindow.ui \
    preparefilterwindow.ui

RESOURCES += \
    sources.qrc



#win32: LIBS += -L$$PWD/../../../../PostgreSQL/9.6/lib/ -llibpq

#INCLUDEPATH += $$PWD/../../../../PostgreSQL/9.6/include
#DEPENDPATH += $$PWD/../../../../PostgreSQL/9.6/include

#win32: LIBS += -L$$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/ -llimereport

#INCLUDEPATH += $$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/include
#DEPENDPATH += $$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/include


#win32: LIBS += -L$$PWD/../../../../PostgreSQL/9.6/lib/ -llibpq

#INCLUDEPATH += $$PWD/../../../../PostgreSQL/9.6/include
#DEPENDPATH += $$PWD/../../../../PostgreSQL/9.6/include

#win32: LIBS += -L$$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/ -llimereport

#INCLUDEPATH += $$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/include
#DEPENDPATH += $$PWD/../LimeReport-master/build/5.7.1/win32/release/lib/include



win32: LIBS += -L'C:/Program Files (x86)/PostgreSQL/9.6/lib/' -llibpq

INCLUDEPATH += 'C:/Program Files (x86)/PostgreSQL/9.6/include'
DEPENDPATH += 'C:/Program Files (x86)/PostgreSQL/9.6/include'



win32: LIBS += -LC:/Users/dKondrashin/Documents/LimeReport-master/build/5.7.1/win32/release/lib/ -llimereport

INCLUDEPATH += C:/Users/dKondrashin/Documents/LimeReport-master/build/5.7.1/win32/release/lib/include
DEPENDPATH += C:/Users/dKondrashin/Documents/LimeReport-master/build/5.7.1/win32/release/lib/include

win32: LIBS += -LC:/Users/dKondrashin/Documents/LimeReport-master/build/5.7.1/win32/release/lib/ -lQtZint

