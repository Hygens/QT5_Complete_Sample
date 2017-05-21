#-------------------------------------------------
#
# Project created by QtCreator 2017-05-09T21:32:49
#
#-------------------------------------------------

QT       += core gui widgets sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SIGAPriority
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    priorityUtils.cpp \
    priorityZone.cpp \
    reservatorio.cpp \
    zoneForm.cpp \
    mainform.cpp \
    lineediticonized.cpp \
    availshow.cpp

HEADERS  += \
    priorityZone.h \
    priorityUtils.h \
    reservatorio.h \
    mainform.h \
    zoneForm.h \
    lineediticonized.h \
    availshow.h

FORMS    += \
    availshow.ui

CONFIG += c++11

# Start copy sqldrivers sqlite3
win32|win64 {

CONFIG(debug, debug|release) {
    DESTDIR = debug
} else {
    DESTDIR = release
}
PWD_WIN = $${PWD}
DESTDIR_WIN = $${OUT_PWD}\\$${DESTDIR}
PWD_WIN ~= s,/,\\,g
DESTDIR_WIN ~= s,/,\\,g

copyfiles.commands = $$quote(cmd /c xcopy /Y /S /E /I /C $${PWD_WIN}\\sqldrivers $${DESTDIR_WIN}\\sqldrivers)

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles

}

unix|mac {

copydata.commands = $(COPY_DIR) $$PWD/sqldrivers $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata

}
# End copy sqldrivers sqlite3

DISTFILES +=

RESOURCES += \
    resources.qrc
