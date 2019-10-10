#pragma once

#include "connection.h"
#include "channel.h"
#include "client.h"
#include "filetransfer.h"
#include "wavehandle.h"

namespace TeamSpeakSdk {

class Client;
class Channel;
class Connection;
class WaveHandle;
class CustomDevice;
class FileTransfer;

// class CacheManager : public QObject
// {
// public:
//     static CacheManager* instance();
//     ~CacheManager();
// 
//     static void addServer(Connection* connection);
//     static Connection* getServer(Connection::ID id, bool create_if_not_exists = false);
//     static void removeServer(Connection::ID id);
// 
//     static void addChannel(Channel* channel);
//     static Channel* getChannel(Channel::ID id, bool create_if_not_exists = false);
//     static void removeChannel(Channel::ID id);
// 
//     static void addClient(Client* client);
//     static Client* getClient(Client::ID id);
//     static void removeClient(Client::ID id);
//     static void addTransfer(FileTransfer* transfer);
//     static FileTransfer* getTransfer(FileTransfer::ID id, bool create_if_not_exists = false);
//     static void removeTransfer(FileTransfer::ID id);
// 
//     static void addWaveHandle(WaveHandle* transfer);
//     static WaveHandle* getWaveHandle(WaveHandle::ID id, bool create_if_not_exists = false);
//     static void removeWaveHandle(WaveHandle::ID id);
// 
//     static QList<CustomDevice*> customDevices();
// 
// private:
//     CacheManager(QObject* parent = Q_NULLPTR);
//     friend void __init_cache_manager();
// };

} // namespace TeamSpeakSdk
