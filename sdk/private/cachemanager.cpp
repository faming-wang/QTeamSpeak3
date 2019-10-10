#include "cachemanager_p.h"
#include "threadsafecontainer_p.h"

#include "connection.h"
#include "client.h"
#include "channel.h"
#include "wavehandle.h"
#include "sounddevice.h"
#include "filetransfer.h"
// 
// namespace TeamSpeakSdk {
// 
// class CacheManagerPrivate
// {
// public:
//     CacheManagerPrivate()
//     {
// 
//     }
// 
//     QList<CustomDevice*> custom_devices;
//     ThreadSafeCache<Client::ID, Client> clients;
//     ThreadSafeCache<Channel::ID, Channel> channels;
//     ThreadSafeCache<Connection::ID, Connection> servers;
//     ThreadSafeCache<WaveHandle::ID, WaveHandle> wave_handles;
//     ThreadSafeCache<FileTransfer::ID, FileTransfer> transfers;
// };
// 
// static CacheManager* m_instance = Q_NULLPTR;
// static CacheManagerPrivate*   d = Q_NULLPTR;
// CacheManager* CacheManager::instance()
// {
//     return m_instance;
// }
// 
// CacheManager::CacheManager(QObject* parent)
//     : QObject(parent)
// {
//     d = new CacheManagerPrivate;
//     m_instance = this;
// }
// 
// CacheManager::~CacheManager()
// {
//     m_instance = Q_NULLPTR;
//     delete d;d = Q_NULLPTR;
// }
// 
// Connection* CacheManager::getServer(Connection::ID id, bool create_if_not_exists)
// {
//     return d->servers[id];
// }
// 
// void CacheManager::addServer(Connection* server)
// {
//     d->servers.insert(server->id(), server);
// }
// 
// void CacheManager::removeServer(Connection::ID id)
// {
//     d->servers.remove(id);
// }
// 
// void CacheManager::addChannel(Channel* channel)
// {
//     d->channels.insert(channel->id(), channel);
// }
// 
// Channel* CacheManager::getChannel(Channel::ID id, bool create_if_not_exists)
// {
//     return d->channels[id];
// }
// 
// void CacheManager::removeChannel(Channel::ID id)
// {
//     d->channels.remove(id);
// }
// 
// void CacheManager::addClient(Client* client)
// {
//     d->clients.insert(client->id(), client);
// }
// 
// Client* CacheManager::getClient(Client::ID id)
// {
//     return d->clients[id];
// }
// 
// void CacheManager::removeClient(Client::ID id)
// {
//     d->clients.remove(id);
// }
// 
// void CacheManager::addTransfer(FileTransfer* transfer)
// {
//     d->transfers.insert(transfer->id(), transfer);
// }
// 
// FileTransfer* CacheManager::getTransfer(FileTransfer::ID id, bool create_if_not_exists)
// {
//     return d->transfers[id];
// }
// 
// void CacheManager::removeTransfer(FileTransfer::ID id)
// {
//     d->transfers.remove(id);
// }
// 
// void CacheManager::addWaveHandle(WaveHandle* wave)
// {
//     d->wave_handles.insert(wave->id(), wave);
// }
// 
// WaveHandle* CacheManager::getWaveHandle(WaveHandle::ID id, bool create_if_not_exists)
// {
//     return d->wave_handles[id];
// }
// 
// void CacheManager::removeWaveHandle(WaveHandle::ID id)
// {
//     d->wave_handles.remove(id);
// }
// 
// QList<CustomDevice*> CacheManager::customDevices()
// {
//     return d->custom_devices;
// }
// 
// void __init_cache_manager()
// {
//     (void) new CacheManager(qApp);
// }
// Q_COREAPP_STARTUP_FUNCTION(__init_cache_manager)
// 
// } // namespace TeamSpeakSdk
