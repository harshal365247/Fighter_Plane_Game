QT       += core gui multimedia sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $${PWD}/headers
INCLUDEPATH += $${PWD}/sources

SOURCES += \
    $${PWD}/sources/bullet.cpp \
    $${PWD}/sources/containerwidget.cpp \
    $${PWD}/sources/database.cpp \
    $${PWD}/sources/enemy.cpp \
    $${PWD}/sources/gameoverwidget.cpp \
    $${PWD}/sources/health.cpp \
    $${PWD}/sources/main.cpp \
    $${PWD}/sources/menuwidget.cpp \
    $${PWD}/sources/player_plane.cpp \
    $${PWD}/sources/playername.cpp \
    $${PWD}/sources/score.cpp \
    $${PWD}/sources/scoreWidget.cpp \
    $${PWD}/sources/scorelistitem.cpp \
    $${PWD}/sources/widget.cpp

HEADERS += \
    $${PWD}/headers/bullet.h \
    $${PWD}/headers/containerwidget.h \
    $${PWD}/headers/database.h \
    $${PWD}/headers/enemy.h \
    $${PWD}/headers/gameoverwidget.h \
    $${PWD}/headers/health.h \
    $${PWD}/headers/menuwidget.h \
    $${PWD}/headers/player_plane.h \
    $${PWD}/headers/playername.h \
    $${PWD}/headers/score.h \
    $${PWD}/headers/scoreWidget.h \
    $${PWD}/headers/scorelistitem.h \
    $${PWD}/headers/widget.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc

