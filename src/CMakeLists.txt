add_library(QTeamSpeak3 STATIC
    QTeamSpeak/event.h
    QTeamSpeak/namespace.h
    QTeamSpeak/exception.h

    QTeamSpeak/object.cpp
    QTeamSpeak/object.h
    QTeamSpeak/library.cpp
    QTeamSpeak/library.h
    QTeamSpeak/client.cpp
    QTeamSpeak/client.h
    QTeamSpeak/channel.cpp
    QTeamSpeak/channel.h
    QTeamSpeak/connection.cpp
    QTeamSpeak/connection.h
    QTeamSpeak/preprocessor.cpp
    QTeamSpeak/preprocessor.h
    QTeamSpeak/connectioninfo.cpp
    QTeamSpeak/connectioninfo.h
    QTeamSpeak/fileinfo.cpp
    QTeamSpeak/fileinfo.h
    QTeamSpeak/filetransfer.cpp
    QTeamSpeak/filetransfer.h
    QTeamSpeak/wavehandle.cpp
    QTeamSpeak/wavehandle.h
    QTeamSpeak/sounddevice.cpp
    QTeamSpeak/sounddevice.h
    QTeamSpeak/eventlistener.h
  
    QTeamSpeak/private/utils_p.h
    QTeamSpeak/private/debug_p.h
    QTeamSpeak/private/library_p.h
    QTeamSpeak/private/definition_p.h
    QTeamSpeak/private/eventmanager_p.h
    QTeamSpeak/private/eventmanager.cpp
    QTeamSpeak/private/interfacemanager_p.h
    QTeamSpeak/private/interfacemanager_p_p.h
    QTeamSpeak/private/interfacemanager.cpp
)

get_filename_component(CURRENT_DIR "." REALPATH)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

target_link_libraries(QTeamSpeak3 Qt${QT_VERSION_MAJOR}::Core)

target_include_directories(QTeamSpeak3 PUBLIC ${CURRENT_DIR} PRIVATE ${CURRENT_DIR}/QTeamSpeak)

target_precompile_headers(QTeamSpeak3 PUBLIC "<QtCore/QtCore>")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
