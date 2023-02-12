add_executable(QTeamSpeak3Client main.cpp)

target_link_libraries(QTeamSpeak3Client PUBLIC QTeamSpeak3 ${TSClientSdk_LIBRARY})

