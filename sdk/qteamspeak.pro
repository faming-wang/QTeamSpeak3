QT       -= gui

TARGET = QTeamSpeakSdk
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
DEFINES += _UNICODE

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += library.cpp
SOURCES += client.cpp
SOURCES += channel.cpp
SOURCES += connection.cpp
SOURCES += connectioninfo.cpp
SOURCES += preprocessor.cpp
SOURCES += fileinfo.cpp
SOURCES += filetransfer.cpp
SOURCES += wavehandle.cpp
SOURCES += sounddevice.cpp
SOURCES += private/cachemanager.cpp
SOURCES += private/channeltracker.cpp
SOURCES += private/eventmanager.cpp
SOURCES += private/interfacemanager.cpp

HEADERS += exception.h
HEADERS += tsnamespace.h
HEADERS += teamspeaksdk.h
HEADERS += library.h
HEADERS += client.h
HEADERS += channel.h 
HEADERS += connection.h
HEADERS += preprocessor.h 
HEADERS += connectioninfo.h
HEADERS += fileinfo.h
HEADERS += filetransfer.h 
HEADERS += wavehandle.h
HEADERS += sounddevice.h
HEADERS += teamspeakevents.h
HEADERS += private/definitions_p.h
HEADERS += private/teamspeakutils_p.h
HEADERS += private/teamspeakdebug_p.h
HEADERS += private/cachemanager_p.h 
HEADERS += private/channeltracker_p.h
HEADERS += private/eventmanager_p.h 
HEADERS += private/interfacemanager_p.h
HEADERS += private/interfacemanager_p_p.h 

# precompile support
!contains(CONFIG, precompile_header) {
    CONFIG += precompile_header
}

PRECOMPILED_HEADER = stdafx.h
PRECOMPILED_DIR = $$OBJECTS_DIR
precompile_header:!isEmpty(PRECOMPILED_HEADER) {
    DEFINES += USING_PCH
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}