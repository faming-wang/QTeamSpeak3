set (CMAKE_INCLUDE_CURRENT_DIR ON)

set (_private_src
  private/definitions_p.h
  private/teamspeakutils_p.h
  private/teamspeakdebug_p.h
  private/cachemanager_p.h 
  private/cachemanager.cpp
  private/channeltracker_p.h
  private/channeltracker.cpp
  private/eventmanager_p.h 
  private/eventmanager.cpp
  private/interfacemanager_p.h
  private/interfacemanager_p_p.h 
  private/interfacemanager.cpp
)
set (_public_include
  exception.h
  tsnamespace.h
  teamspeaksdk.h
  library.h
  client.h
  channel.h 
  connection.h
  preprocessor.h 
  connectioninfo.h
  fileinfo.h
  filetransfer.h 
  wavehandle.h
  sounddevice.h
  teamspeakevents.h
)

set (_lib_src 
  ${_public_include}
  ${_private_src}
  library.cpp
  client.cpp
  channel.cpp
  connection.cpp
  connectioninfo.cpp
  preprocessor.cpp
  fileinfo.cpp
  filetransfer.cpp
  wavehandle.cpp
  sounddevice.cpp
  stdafx.h stdafx.cpp
)

add_library (QTeamSpeakSdk STATIC EXCLUDE_FROM_ALL ${_lib_src})
add_library (${CMAKE_PROJECT_NAME}::QTeamSpeakSdk ALIAS QTeamSpeakSdk)
target_compile_features(QTeamSpeakSdk PUBLIC cxx_std_11)

target_include_directories(QTeamSpeakSdk PUBLIC "${CMAKE_SOURCE_DIR}/include")

find_package(Qt5 COMPONENTS Core REQUIRED)
target_link_libraries(QTeamSpeakSdk Qt5::Core)

set_target_properties(QTeamSpeakSdk PROPERTIES
 SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}"
 VERSION "${_lib_version}"
 PUBLIC_HEADER "${_public_include}"
 RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin"
 LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
 ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib"
)
include (PrecompiledHeader)
add_precompiled_header (QTeamSpeakSdk stdafx.h FORCEINCLUDE SOURCE_CXX stdafx.cpp)

install(
  FILES ${_public_include}
  DESTINATION "${PROJECT_BINARY_DIR}/include"
)
