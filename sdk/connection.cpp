#include "connection.h"

#include "channel.h"
#include "fileinfo.h"
#include "wavehandle.h"
#include "sounddevice.h"
#include "preprocessor.h"
#include "teamspeakevents.h"
#include "private/cachemanager_p.h"
#include "private/teamspeakdebug_p.h"
#include "private/interfacemanager_p.h"

namespace TeamSpeakSdk {

class Cache
{

public:
    Cache(Connection* server)
        : connection(server)
    {
    }

    ~Cache()
    {
        clear();
    }

    Client* getClient(Client::ID clientID)
    {
        if (clientID == 0)
            return Q_NULLPTR;

        if (clients.contains(clientID))
            return clients[clientID];

        auto client = new Client(connection, clientID);
        clients.insert(clientID, client);
        return client;
    }

    Channel* getChannel(Channel::ID channelID)
    {
        if (channelID == 0) 
            return Q_NULLPTR;

        if (channels.contains(channelID))
            return channels[channelID];

        auto channel = new Channel(connection, channelID);
        channels.insert(channelID, channel);
        return channel;
    }

    WaveHandle* getWaveHandle(WaveHandle::ID waveHandleID)
    {
        if (waveHandleID == 0)
            return Q_NULLPTR;

        if (waveHandles.contains(waveHandleID))
            return waveHandles[waveHandleID];

        auto waveHandle = new WaveHandle(connection, waveHandleID);
        waveHandles.insert(waveHandleID, waveHandle);
        return waveHandle; 
    }

    FileTransfer* getFileTransfer(FileTransfer::ID fileTransferID)
    {
        if (fileTransferID == 0)
            return Q_NULLPTR;

        if (fileTransfers.contains(fileTransferID))
            return fileTransfers[fileTransferID];

        auto fileTransfer = new FileTransfer(connection, fileTransferID);
        fileTransfers.insert(fileTransferID, fileTransfer);
        return fileTransfer;
    }

    void clear()
    {
        qDeleteAll(clients);
        clients.clear();
        qDeleteAll(channels);
        channels.clear();
        qDeleteAll(waveHandles);
        waveHandles.clear();
        qDeleteAll(fileTransfers);
        fileTransfers.clear();
    }

    Connection* connection;
    QHash<Client::ID, Client*> clients;
    QHash<Channel::ID, Channel*> channels;
    QHash<WaveHandle::ID, WaveHandle*> waveHandles;
    QHash<FileTransfer::ID, FileTransfer*> fileTransfers;
};


class Connection::Private
{
public:
    bool isConnecting = false;
    bool isVoiceRecording = false;

    ID id = 0;
    TestMode localTestMode = TestMode::Off;
    time::seconds timeout = time::seconds(1000 * 10);

    Cache* cache = Q_NULLPTR;
    Client* self = Q_NULLPTR;
    Channel* zeroChannel = Q_NULLPTR;
    ISoundDevice* playbackDevice = Q_NULLPTR;
    ISoundDevice* captureDevice = Q_NULLPTR;

    ~Private()
    {
        delete cache;
        delete self;
        delete zeroChannel;
        delete playbackDevice;
        delete captureDevice;
    }

    void initialize(Connection* connection)
    {
        cache = new Cache(connection);
        self = new Client(connection, 0);
        zeroChannel = new Channel(connection, 0);
    }

    int getInt(const Connection* connection, VirtualServerProperty flag) const
    {
        return api().getServerVariableAsInt(connection, flag);
    }
    uint64 getUInt64(const Connection* connection, VirtualServerProperty flag) const
    {
        return api().getServerVariableAsUInt64(connection, flag);
    }
    QString getString(const Connection* connection, VirtualServerProperty flag) const
    {
        return api().getServerVariableAsString(connection, flag);
    }
    
    QString getString(ConnectionProperty flag) const
    {
        return api().getConnectionVariableAsString(self, flag);
    }
    uint64 getUInt64(ConnectionProperty flag) const
    {
        return api().getConnectionVariableAsUInt64(self, flag);
    }

    float getPlaybackConfigValueAsFloat(const Connection* connection, const QString& ident) const
    {
        return api().getPlaybackConfigValueAsFloat(connection, ident);
    }

    void setPlaybackConfigValue(const Connection* connection, const QString& ident, const QString& value)
    {
        api().setPlaybackConfigValue(connection, ident, value);
    }
};

Connection::Connection(Connection::ID id)
    : d(new Private)
{
    d->id = id;
    d->initialize(this);
    Library::addServer(this);
}

Connection::Connection()
    : Connection(api().spawnNewServerConnectionHandler(0))
{
}

Connection::~Connection()
{
    delete d;
}

/*!
* ID of the client
*/
Connection::ID Connection::id() const
{
    return d->id;
}

/*!
* the connection as a client object
*/
Client* Connection::self() const
{
    return d->self;
}

/*!
* A list of channels who have the channel as a parent
*/
QList<Channel*> Connection::rootChannels() const
{
    return QList<Channel*>();
}

/*!
* A list of all channels on the virtual server
*/
QList<Channel*> Connection::allChannels() const
{
    return api().getChannelList(this);
}

/*!
* A list of all currently visible clients on the virtual server
*/
QList<Client*> Connection::allClients() const
{
    return api().getClientList(this);
}

Client* Connection::getClient(Client::ID id) const
{
    return d->cache->getClient(id);
}

Channel* Connection::getChannel(Channel::ID id) const
{
    return d->cache->getChannel(id);
}

FileTransfer* Connection::getTransfer(FileTransfer::ID id) const
{
    return d->cache->getFileTransfer(id);
}

WaveHandle* Connection::getWaveHandle(WaveHandle::ID id) const
{
    return d->cache->getWaveHandle(id);
}

/*!
* IP of the server (seen from the client side)
*/
QString Connection::serverIp() const
{
    return d->getString(ConnectionProperty::ServerIp);
}

/*!
* Port of the server (seen from the client side)
*/
uint64 Connection::serverPort() const
{
    return d->getUInt64(ConnectionProperty::ServerPort);
}

/*!
* Unique ID for this virtual server.
* Stays the same after restarting the server application.
* Always available when connected.
*/
QString Connection::uniqueIdentifier() const
{
    return d->getString(this, VirtualServerProperty::UniqueIdentifier);
}

/*!
* Name of this virtual server. Always available when connected.
*/
QString Connection::name() const
{
    return d->getString(this, VirtualServerProperty::Name);
}

/*!
* Optional welcome message sent to the client on login.
* This value should be queried by the client after connection has been established, it is not updated afterwards.
*/
QString Connection::welcomeMessage() const
{
    return d->getString(this, VirtualServerProperty::Welcomemessage);
}

/*!
* Operating system used by this server. Always available when connected.
*/
QString Connection::platform() const
{
    return d->getString(this, VirtualServerProperty::Platform);
}

/*!
* Application version of this server. Always available when connected.
*/
QString Connection::version() const
{
    return d->getString(this, VirtualServerProperty::Version);
}

/*!
* Defines maximum number of clients which may connect to this server.
* Needs to be requested using \sa refreshProperties().
*/
int Connection::maxClients() const
{
    return d->getInt(this, VirtualServerProperty::Maxclients);
}

/*!
* Number of clients currently on this virtual server.
* Needs to be requested using \sa refreshProperties().
*/
int Connection::clientsOnline() const
{
    return d->getInt(this, VirtualServerProperty::ClientsOnline);
}

/*!
* Number of channels currently on this virtual server.
* Needs to be requested using \sa refreshProperties().
*/
int Connection::channelsOnline() const
{
    return d->getInt(this, VirtualServerProperty::ChannelsOnline);
}

/*!
* Time when this virtual server was created. Always available when connected.
*/
QDateTime Connection::created() const
{
    const auto time = d->getUInt64(this, VirtualServerProperty::Created);
    return utils::to_date_time(time);
}

/*!
* Uptime of this virtual server. Needs to be requested using \sa refreshProperties().
*/
QDateTime Connection::uptime() const
{
    const auto time = d->getInt(this, VirtualServerProperty::Uptime);
    return utils::to_date_time(time);
}

/*!
* Defines if voice data encryption is configured per channel,
* globally forced on or globally forced off for this virtual server.
* The default behavior is configure per channel,
* in this case modifying \sa Channel::codecIsUnencrypted()
* defines voice data encryption of individual channels.
*/
CodecEncryptionMode Connection::codecEncryptionMode() const
{
    const auto codec = d->getInt(this, VirtualServerProperty::CodecEncryptionMode);
    return static_cast<CodecEncryptionMode>(codec);
}

/*!
* When using \sa Library::editCapturedVoiceDataHandler() to record voice,
* you should notify the server when recording starts or stops
*/
bool Connection::isVoiceRecording() const
{
    return d->isVoiceRecording;
}

void Connection::setVoiceRecording(bool value)
{
    if (value)
        api().startVoiceRecording(this);
    else
        api().stopVoiceRecording(this);
    d->isVoiceRecording = value;
}

/*!
* Determines how long the client will wait for a reply from the server.
*/
time::seconds Connection::timeout() const
{
    return d->timeout;
}

void Connection::setTimeout(time::seconds value)
{
    d->timeout = value;
}

/*!
* Currently open playback device. Set using \sa openPlayback(ISoundDevice)
*/
ISoundDevice* Connection::playbackDevice() const
{
    return d->playbackDevice;
}

/*!
* Currently open capture device. Set using \sa openCapture(ISoundDevice)
*/
ISoundDevice* Connection::captureDevice() const
{
    return d->captureDevice;
}

/*!
* Status of the connection to the given server
*/
ConnectStatus Connection::status() const
{
    return api().getConnectionStatus(this);
}

/*!
* The upload speed limit for the specified virtual server in bytes/s.
*/
uint64 Connection::speedLimitUp() const
{
    return api().getServerConnectionHandlerSpeedLimitUp(this);
}

void Connection::setSpeedLimitUp(uint64 value)
{
    api().setServerConnectionHandlerSpeedLimitUp(this, value);
}

/*!
*  The download speed limit for the specified virtual server in bytes/s.
*/
uint64 Connection::speedLimitDown() const
{
    return api().getServerConnectionHandlerSpeedLimitDown(this);
}

void Connection::setSpeedLimitDown(uint64 value)
{
    api().setServerConnectionHandlerSpeedLimitDown(this, value);
}

/*!
* Instead of sending the sound through the network,
* it can be routed directly through the playback device,
* so the user will get immediate audible feedback when for example configuring some sound settings.
*/
TestMode Connection::localTestMode() const
{
    return d->localTestMode;
}

void Connection::setLocalTestMode(TestMode value)
{
    api().setLocalTestMode(this, value);
    d->localTestMode = value;
}

/*!
* Modify the voice volume of other speakers. Value is in decibel, so 0 is no modification,
* negative values make the signal quieter and values greater than zero boost the signal louder than it is.
* Be careful with high positive values, as you can really cause bad audio quality due to clipping.
* The maximum possible Value is 30. Zero and all negative values cannot cause clipping and distortion,
* and are preferred for optimal audio quality. Values greater than zero and less than +6 dB
* might cause moderate clipping and distortion, but should still be within acceptable bounds.
* Values greater than +6 dB will cause clipping and distortion that will negatively affect your audio quality.
* It is advised to choose lower values. Generally we recommend to not allow values higher than 15 db.
*/
float Connection::volumeModifier() const
{
    return d->getPlaybackConfigValueAsFloat(this, "volume_modifier");
}

void Connection::setVolumeModifier(float value)
{
    d->setPlaybackConfigValue(this, "volume_modifier", QString::number(value));
}

/*!
* Adjust the volume of wave files played by \sa playWaveFile(string, bool).
* The value is a float defining the volume reduction in decibel.
* Reasonable values range from "-40.0" (very silent) to "0.0" (loudest).
*/
float Connection::volumeFactorWave() const
{
    return d->getPlaybackConfigValueAsFloat(this, "volume_factor_wave");
}

void Connection::setVolumeFactorWave(float value)
{
    d->setPlaybackConfigValue(this, "volume_factor_wave", QString::number(value));
}

/*!
* To initialize a playback device
* \a device the device to be used. when null, the default playback is used.
*/
void Connection::openPlaybackDevice(ISoundDevice* device)
{
    api().openPlaybackDevice(this, device);
    d->playbackDevice = device;
    if (!d->playbackDevice) {
        api().openPlaybackDevice(this, Q_NULLPTR);
        auto mode = api().getCurrentPlayBackMode(this);
        auto id = api().getCurrentPlaybackDeviceName(this);
        auto soundDeviceSource = ( mode != CustomDevice::modeName)
            ? Library::getPlaybackDevices(mode)
            : utils::dynamic_cast_c<ISoundDevice*>(Library::getCustomDevices());
        if (soundDeviceSource.isEmpty()) {
            d->playbackDevice = new SoundDevice(mode, id, QString());
        } else {
            d->playbackDevice = soundDeviceSource.takeFirst();
            qDeleteAll(soundDeviceSource);
        }
    }
}

/*!
* To initialize a capture device
* \a device the device to be used. when null, the default capture is used.
*/
void Connection::openCaptureDevice(ISoundDevice* device)
{
    api().openCaptureDevice(this, device);
    d->captureDevice = device;
    if (!d->captureDevice) {
        auto mode = api().getCurrentCaptureMode(this);
        auto id = api().getCurrentCaptureDeviceName(this);
        auto soundDeviceSource = (mode != CustomDevice::modeName)
            ? Library::getPlaybackDevices(mode)
            : utils::dynamic_cast_c<ISoundDevice*>(Library::getCustomDevices());
        if (soundDeviceSource.isEmpty()) {
            d->captureDevice = new SoundDevice(mode, id, QString());
        } else {
            d->captureDevice = soundDeviceSource.takeFirst();
            qDeleteAll(soundDeviceSource);
        }
    }
}

/*!
* Close the playback device
*/
void Connection::closePlaybackDevice()
{
    api().closePlaybackDevice(this);
}

/*!
* Close the capture device
*/
void Connection::closeCaptureDevice()
{
    api().closeCaptureDevice(this);
}

/*!
* When connecting to multiple servers with the same client,
* the capture device can only be active for one server at the same time.
* As soon as the client connects to a new server,
* the \sa Library will deactivate the capture device for the previously active server.
* When a user wants to talk to that previous server again, the client needs to reactivate the capture device.
*/
void Connection::activateCaptureDevice()
{
    api().activateCaptureDevice(this);
}

/*!
* Set the position, velocity and orientation of the listener in 3D space
* \a position 3D position of the listener. If passing null, the parameter is ignored and the value not updated.
* \a forward Forward orientation of the listener. The Vector3D must be of unit length and perpendicular to the up Vector3D. If passing null, the parameter is ignored and the value not updated.
* \a up Upward orientation of the listener. The Vector3D must be of unit length and perpendicular to the forward Vector3D. If passing null, the parameter is ignored and the value not updated.
*/
void Connection::set3DListenerAttributes(Vector3D* position, Vector3D* forward, Vector3D* up)
{
    api().systemset3DListenerAttributes(this, position, forward, up);
}

/*!
* Adjusts 3D sound system settings
* \a distanceFactor Relative distance factor. Default is 1.0 = 1 meter
* \a rolloffScale Scaling factor for 3D sound roll-off. Defines how fast sound volume will attenuate. As higher the value, as faster the sound is toned with increasing distance.
*/
void Connection::set3DSettings(float distanceFactor, float rolloffScale)
{
    api().systemset3DSettings(this, distanceFactor, rolloffScale);
}

/*!
* Prepares the playback device be closed via \sa closePlaybackDevice().
* Should be used to prevent interrupting of still playing sounds.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::playbackShutdown()
{
    auto error = api().initiateGracefulPlaybackShutdown(this);
}

/*!
* Connect to a TeamSpeak 3 server
* \a "identity" Unique identifier for this server connection. Created with <see cref="Library.CreateIdentity"/>
* \a "ip" Hostname or IP of the TeamSpeak 3 server.
* \a "port" UDP port of the TeamSpeak 3 server, by default 9987.
* \a "nickname" On login, the client attempts to take this nickname on the connected server. Note this is not necessarily the actually assigned nickname, as the server can modify the nickname ("gandalf_1" instead the requested "gandalf") or refuse blocked names.
* \a "defaultChannelID" The \sa Channel::id() to a channel on the TeamSpeak 3 server. If the channel exists and the user has sufficient rights and supplies the correct password if required, the channel will be joined on login.
* \a "defaultChannelPassword" Password for the default channel. Pass null or an empty string if no password is required or no default channel is specified
* \a "serverPassword" Password for the server. Pass null or an empty string if the server does not require a password.
* Returns \c A task that represents the asynchronous operation.
* If you pass a hostname instead of an IP, the Client Lib will try to resolve it to an IP, but the function may block for an unusually long period of time while resolving is taking place. If you are relying on the function to return quickly, we recommend to resolve the hostname yourself (e.g.asynchronously) and then call with the IP instead of the hostname.
*/
void Connection::startWithChannelID(const ConnectInfo& option,
                       Channel::ID defaultChannelID,
                       const QString& defaultChannelPassword)
{
    const auto error = api().startConnection(
        this,
        option.identity,
        option.address,
        option.port,
        option.nickname,
        defaultChannelID,
        defaultChannelPassword,
        option.serverPassword
    );

}

/*!
* Connect to a TeamSpeak 3 server
* \a "identity" Unique identifier for this server connection. Created with \sa Library::createIdentity()
* \a "ip" Hostname or IP of the TeamSpeak 3 server.
* \a "port" UDP port of the TeamSpeak 3 server, by default 9987.
* \a "nickname" On login, the client attempts to take this nickname on the connected server. Note this is not necessarily the actually assigned nickname, as the server can modify the nickname ("gandalf_1" instead the requested "gandalf") or refuse blocked names.
* \a "defaultChannelArray" The path to a channel on the TeamSpeak 3 server. If the channel exists and the user has sufficient rights and supplies the correct password if required, the channel will be joined on login. To define the path to a subchannel of arbitrary level, create an array of channel names detailing the position of the default channel (e.g. { "grandparent", "parent", "mydefault" } ).
* \a "defaultChannelPassword" Password for the default channel. Pass null or an empty string if no password is required or no default channel is specified.
* \a "serverPassword" Password for the server. Pass null or an empty string if the server does not require a password.
* Returns \c A task that represents the asynchronous operation.
* If you pass a hostname instead of an IP,
* the Client Lib will try to resolve it to an IP,
* but the function may block for an unusually long period of time while resolving is taking place.
* If you are relying on the function to return quickly,
* we recommend to resolve the hostname yourself (e.g.asynchronously)
* and then call with the IP instead of the hostname.
*/
void Connection::start(const ConnectInfo& option,
                       const QStringList& defaultChannels,
                       const QString& defaultChannelPassword)
{
    const auto error = api().startConnection(
        this,
        option.identity, 
        option.address,
        option.port, 
        option.nickname, 
        defaultChannels, 
        defaultChannelPassword, 
        option.serverPassword
    );
}

/*!
* Disconnect from a TeamSpeak 3 server
* \a quitMessage A message like for example "leaving".
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::stop(const QString& quitMessage)
{
    auto error = api().stopConnection(this, quitMessage);
}

/*!
* Subscribe to all channels on the server
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::subscribeAll()
{
    api().requestChannelSubscribeAll(this, TODO_RETURN_CODE);
}

/*!
* Unsubscribe from all channels on the server
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::unsubscribeAll()
{
    api().requestChannelUnsubscribeAll(this, TODO_RETURN_CODE);
}

/*!
* Refreshing the server information.
* \remarks \sa "ServerUpdated" is called when the information is available
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::refreshProperties()
{
    api().requestServerVariables(this);
}

/*!
* Subscribes to one or more channels
* \a channels list of channels to subscribe to.
* \returns A task that represents the asynchronous operation.
*/
void Connection::subscribe(const QList<Channel*>& channels)
{
    if (channels.isEmpty())
        return;
    if (utils::has_null(channels))
        return;
    api().requestChannelSubscribe(channels, TODO_RETURN_CODE);
}

/*!
* Unsubscribes from one or more channels
* \a channels list of channels to unsubscribe from.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::unsubscribe(const QList<Channel*>& channels)
{
    if (channels.isEmpty())
        return;
    if (utils::has_null(channels))
        return;
    api().requestChannelUnsubscribe(channels, TODO_RETURN_CODE);
}

/*!
* Mutes one or more clients
* \a clients list of clients to be muted
* Returns \c A task that represents the asynchronous operation.
* Clients can be locally muted. This information is handled client-side only and not visible to other clients. It mainly serves as a sort of individual "ban" or "ignore" feature, where users can decide not to listen to certain clients anymore.
* When a client becomes muted, he will no longer be heard by the muter. Also the TeamSpeak 3 server will stop sending voice packets.
* The mute state is not visible to the muted client nor to other clients. It is only available to the muting client by checking \sa "Client.Muted"
*/
void Connection::mute(const QList<Client*>& clients)
{
    if (clients.isEmpty())
        return;
    if (utils::has_null(clients))
        return;
    api().requestMuteClients(clients, TODO_RETURN_CODE);
}

/*!
* Unmute one or more clients
* \a "clients" Array of clients to be muted
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::unmute(const QList<Client*>& clients)
{
    if (clients.isEmpty())
        return;
    if (utils::has_null(clients))
        return;
    api().requestUnmuteClients(clients, TODO_RETURN_CODE);
}

/*!
* Create a new Channel
* \a "name" Name of the channel
* \a "parent" The parent channel
* \a "topic" Single-line channel topic
* \a "description" Channel description. Can have multiple lines.
* \a "password" Password for password-protected channels.
* \a "order" the \sa "Channel" after which the new \sa "Channel" is sorted. <see langword="null" meaning its going to be the first \sa "Channel" under <paramref "parent".
* \a "isPermanent" Permanent channels will be restored when the server restarts.
* \a "isSemiPermanent" Semi-permanent channels are not automatically deleted when the last user left but will not be restored when the server restarts.
* \a "codec" Codec used for this channel
* \a "codecQuality" Quality of channel codec of this channel. Valid values range from 0 to 10, default is 7. Higher values result in better speech quality but more bandwidth usage
* \a "codecIsUnencrypted" If true, this channel is not using encrypted voice data. If false, voice data is encrypted for this channel.
* \a "codecLatencyFactor" Latency of this channel.
* Returns \c A task that represents the asynchronous creation of the channel.
*/
Channel* Connection::createChannel(const CreateChannelOption& option)
{
    api().flushChannelCreation(this, option.parent, TODO_RETURN_CODE);
    return nullptr;
}

/*!
* Send a private text message to a client
* \a "client" The target client.
* \a "message" The text message.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::sendTextMessage(Client* client, const QString& message)
{
    if (utils::has_null(client))
        return;
    if (!utils::is_same_server(this, client))
        return;
    return client->sendTextMessage(message);
}

/*!
* Send a text message to a channel
* \a "channel" The target channel.
* \a "message" The text message.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::sendTextMessage(Channel* channel, const QString& message)
{
    if (utils::has_null(channel))
        return;
    if (!utils::is_same_server(this, channel))
        return;
    return channel->sendTextMessage(message);
}

/*!
* Send a text message to the server
* \a "message" The text message.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::sendTextMessage(const QString& message)
{
    api().requestSendServerTextMsg(this, message, TODO_RETURN_CODE);
}

/*!
* Move a client to a channel.
* \a "client" The client to move.
* \a "channel" The channel to join.
* \a "password" Optional password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::move(Client* client, const Channel* channel, const QString& password)
{
    if (utils::has_null(client))
        return;
    if (!utils::is_same_server(this, client))
        return;
    return client->moveTo(channel, password);
}

/*!
* Move a channel to a new parent channel
* \a "channel" The channel to be moved.
* \a "newParent" The parent channel where the moved channel is to be inserted as child. Use null to insert as top-level channel.
* \a "newChannelOrder" the \sa Channel after which <paramref "channel" is sorted. <see langword="null" meaning its going to be the first \sa "Channel" under <paramref "newParent".
* Returns \c A task that represents the asynchronous operation.
*/
void Connection::move(Channel* channel, Channel* newParent, Channel* newChannelOrder)
{
    if (utils::has_null(channel))
        return;
    if (!utils::is_same_server(this, channel))
        return;
    return channel->moveTo(newParent, newChannelOrder);
}

/*!
* Play a local wave file
* \a "path" Local path of the sound file in WAV format to be played.
* \a "loop" If true, the sound will be looping until the \sa WaveHandle is paused or closed.
* Returns \c a waveHandle that allows controlling the playback.
*/
WaveHandle* Connection::playWaveFile(const QString& path, bool loop)
{
    return api().playWaveFileHandle(this, path, loop);
}

/*!
* Add a client to the whisper allow list.
* \a "client" The client to be added to the whisper allow list.
*/
void Connection::allowWhispersFrom(const Client* client)
{
    if (utils::has_null(client))
        return;
    if (!utils::is_same_server(this, client))
        return;
    api().allowWhispersFrom(client);
}

/*!
* Remove a client from the whisper allow list.
* \a "client" The client to be removed from the whisper allow list.
*/
void Connection::removeFromAllowedWhispersFrom(Client* client)
{
    if (utils::has_null(client))
        return;
    if (!utils::is_same_server(this, client))
        return;
    api().removeFromAllowedWhispersFrom(client);
}

/*!
* With a whisper list set a client can talk to the specified clients and channels bypassing the standard rule that voice is only transmitted to the current channel. Whisper lists can be defined for individual clients.
* To control which client is allowed to whisper to own client,
* the Library implements an internal whisper whitelist mechanism.
* When a client receives a whisper while the whispering client has not yet been added to the whisper allow list,
* the receiving client gets the \sa WhisperIgnoredEvent.
* Note that whisper voice data is not received until the sending client is added to the receivers whisper allow list.
* \a channels list of channels to whisper to, set to null to disable
* \a clients list of clients to whisper to, set to null to disable
*/
void Connection::setWhisperList(const QList<Channel*>& channels, const QList<Client*>& clients)
{
    if (utils::has_null(channels))
        return;
    if (!utils::is_same_server(this, channels))
        return;
    if (utils::has_null(clients))
        return;
    if (!utils::is_same_server(this, clients))
        return;
    api().requestClientSetWhisperList(self(), channels, clients, TODO_RETURN_CODE);
}

/*!
* Returns every client with a matching UniqueId
* \a uniqueIdentifier UniqueId to look for
* Returns \c A task that represents the asynchronous search operation.
*/
QList<Client*> Connection::findClient(const QString& uniqueIdentifier)
{
    QList<Client*> result;
    if (uniqueIdentifier.isEmpty())
        return result;

    api().requestClientIDs(this, uniqueIdentifier, TODO_RETURN_CODE);

    return result;
}

bool Connection::event(QEvent* e)
{
    switch (e->type()) {
    case ConnectStatusChangedEvent::EventId:
        if (auto event = dynamic_cast<ConnectStatusChangedEvent*>(e)) {
            connectStatusChangedEvent(event);
            return true;
        }
    case ServerProtocolVersionEvent::EventId:
        if (auto event = dynamic_cast<ServerProtocolVersionEvent*>(e)) {
            serverProtocolVersionEvent(event);
            return true;
        }
    case NewChannelEvent::EventId:
        if (auto event = dynamic_cast<NewChannelEvent*>(e)) {
            newChannelEvent(event);
            return true;
        }
    case NewChannelCreatedEvent::EventId:
        if (auto event = dynamic_cast<NewChannelCreatedEvent*>(e)) {
            newChannelCreatedEvent(event);
            return true;
        }
    case ChannelDeletedEvent::EventId:
        if (auto event = dynamic_cast<ChannelDeletedEvent*>(e)) {
            channelDeletedEvent(event);
            return true;
        }
    case ChannelMovedEvent::EventId:
        if (auto event = dynamic_cast<ChannelMovedEvent*>(e)) {
            channelMovedEvent(event);
            return true;
        }
    case ChannelUpdatedEvent::EventId:
        if (auto event = dynamic_cast<ChannelUpdatedEvent*>(e)) {
            channelUpdatedEvent(event);
            return true;
        }
    case ChannelEditedEvent::EventId:
        if (auto event = dynamic_cast<ChannelEditedEvent*>(e)) {
            channelEditedEvent(event);
            return true;
        }
    case ClientUpdatedEvent::EventId:
        if (auto event = dynamic_cast<ClientUpdatedEvent*>(e)) {
            clientUpdatedEvent(event);
            return true;
        }
    case ClientMovedEvent::EventId:
        if (auto event = dynamic_cast<ClientMovedEvent*>(e)) {
            clientMovedEvent(event);
            return true;
        }
    case SubscriptionClientMovedEvent::EventId:
        if (auto event = dynamic_cast<SubscriptionClientMovedEvent*>(e)) {
            subscriptionClientMovedEvent(event);
            return true;
        }
    case ClientMoveTimeoutEvent::EventId:
        if (auto event = dynamic_cast<ClientMoveTimeoutEvent*>(e)) {
            clientMoveTimeoutEvent(event);
            return true;
        }
    case ClientMoverMovedEvent::EventId:
        if (auto event = dynamic_cast<ClientMoverMovedEvent*>(e)) {
            clientMoverMovedEvent(event);
            return true;
        }
    case ClientKickFromChannelEvent::EventId:
        if (auto event = dynamic_cast<ClientKickFromChannelEvent*>(e)) {
            clientKickFromChannelEvent(event);
            return true;
        }
    case ClientKickFromServerEvent::EventId:
        if (auto event = dynamic_cast<ClientKickFromServerEvent*>(e)) {
            clientKickFromServerEvent(event);
            return true;
        }
    case ClientIDsReceivedEvent::EventId:
        if (auto event = dynamic_cast<ClientIDsReceivedEvent*>(e)) {
            clientIDsReceivedEvent(event);
            return true;
        }
    case ClientIDsFinishedEvent::EventId:
        if (auto event = dynamic_cast<ClientIDsFinishedEvent*>(e)) {
            clientIDsFinishedEvent(event);
            return true;
        }
    case ServerEditedEvent::EventId:
        if (auto event = dynamic_cast<ServerEditedEvent*>(e)) {
            serverEditedEvent(event);
            return true;
        }
    case ServerUpdatedEvent::EventId:
        if (auto event = dynamic_cast<ServerUpdatedEvent*>(e)) {
            serverUpdatedEvent(event);
            return true;
        }
    case ServerErrorEvent::EventId:
        if (auto event = dynamic_cast<ServerErrorEvent*>(e)) {
            serverErrorEvent(event);
            return true;
        }
    case ServerStopEvent::EventId:
        if (auto event = dynamic_cast<ServerStopEvent*>(e)) {
            serverStopEvent(event);
            return true;
        }
    case TextMessageEvent::EventId:
        if (auto event = dynamic_cast<TextMessageEvent*>(e)) {
            textMessageEvent(event);
            return true;
        }
    case TalkStatusChangeEvent::EventId:
        if (auto event = dynamic_cast<TalkStatusChangeEvent*>(e)) {
            talkStatusChangeEvent(event);
            return true;
        }
    case WhisperIgnoredEvent::EventId:
        if (auto event = dynamic_cast<WhisperIgnoredEvent*>(e)) {
            whisperIgnoredEvent(event);
            return true;
        }
    case ConnectionInfoEvent::EventId:
        if (auto event = dynamic_cast<ConnectionInfoEvent*>(e)) {
            connectionInfoEvent(event);
            return true;
        }
    case ServerConnectionInfoEvent::EventId:
        if (auto event = dynamic_cast<ServerConnectionInfoEvent*>(e)) {
            serverConnectionInfoEvent(event);
            return true;
        }
    case ChannelSubscribedEvent::EventId:
        if (auto event = dynamic_cast<ChannelSubscribedEvent*>(e)) {
            channelSubscribedEvent(event);
            return true;
        }
    case ChannelSubscribesFinishedEvent::EventId:
        if (auto event = dynamic_cast<ChannelSubscribesFinishedEvent*>(e)) {
            channelSubscribesFinishedEvent(event);
            return true;
        }
    case ChannelUnsubscribedEvent::EventId:
        if (auto event = dynamic_cast<ChannelUnsubscribedEvent*>(e)) {
            channelUnsubscribedEvent(event);
            return true;
        }
    case ChannelUnsubscribesFinishedEvent::EventId:
        if (auto event = dynamic_cast<ChannelUnsubscribesFinishedEvent*>(e)) {
            channelUnsubscribesFinishedEvent(event);
            return true;
        }
    case ChannelDescriptionUpdatedEvent::EventId:
        if (auto event = dynamic_cast<ChannelDescriptionUpdatedEvent*>(e)) {
            channelDescriptionUpdatedEvent(event);
            return true;
        }
    case ChannelPasswordChangedEvent::EventId:
        if (auto event = dynamic_cast<ChannelPasswordChangedEvent*>(e)) {
            channelPasswordChangedEvent(event);
            return true;
        }
    case PlaybackShutdownCompletedEvent::EventId:
        if (auto event = dynamic_cast<PlaybackShutdownCompletedEvent*>(e)) {
            playbackShutdownCompletedEvent(event);
            return true;
        }
    case FileTransferStatusReceivedEvent::EventId:
        if (auto event = dynamic_cast<FileTransferStatusReceivedEvent*>(e)) {
            fileTransferStatusReceivedEvent(event);
            return true;
        }
    case FileListReceivedEvent::EventId:
        if (auto event = dynamic_cast<FileListReceivedEvent*>(e)) {
            fileListReceivedEvent(event);
            return true;
        }
    case FileListFinishedEvent::EventId:
        if (auto event = dynamic_cast<FileListFinishedEvent*>(e)) {
            fileListFinishedEvent(event);
            return true;
        }
    case FileInfoReceivedEvent::EventId:
        if (auto event = dynamic_cast<FileInfoReceivedEvent*>(e)) {
            fileInfoReceivedEvent(event);
            return true;
        }
    default:
        break;
    }
    return QObject::event(e);
}

// events
void Connection::connectStatusChangedEvent(ConnectStatusChangedEvent* event)
{
    Debug debug(Q_FUNC_INFO);


    // TODO: event
}
void Connection::serverProtocolVersionEvent(ServerProtocolVersionEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::newChannelEvent(NewChannelEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::newChannelCreatedEvent(NewChannelCreatedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::channelDeletedEvent(ChannelDeletedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::channelMovedEvent(ChannelMovedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::channelUpdatedEvent(ChannelUpdatedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::channelEditedEvent(ChannelEditedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientUpdatedEvent(ClientUpdatedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientMovedEvent(ClientMovedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::subscriptionClientMovedEvent(SubscriptionClientMovedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientMoveTimeoutEvent(ClientMoveTimeoutEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientMoverMovedEvent(ClientMoverMovedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientKickFromChannelEvent(ClientKickFromChannelEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientKickFromServerEvent(ClientKickFromServerEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientIDsReceivedEvent(ClientIDsReceivedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::clientIDsFinishedEvent(ClientIDsFinishedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::serverEditedEvent(ServerEditedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::serverUpdatedEvent(ServerUpdatedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::serverErrorEvent(ServerErrorEvent* event)
{
    // TODO: event

//     if (!returnCodes.contains(event->returnCode))
//         return true;
// 
//     auto task = returnCodes.take(event->returnCode);
//     if (event->error == ReturnCode::Ok) {
// 
//     } else {
// 
//     }
}
void Connection::serverStopEvent(ServerStopEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::textMessageEvent(TextMessageEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::talkStatusChangeEvent(TalkStatusChangeEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::whisperIgnoredEvent(WhisperIgnoredEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::connectionInfoEvent(ConnectionInfoEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::serverConnectionInfoEvent(ServerConnectionInfoEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelSubscribedEvent(ChannelSubscribedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelSubscribesFinishedEvent(ChannelSubscribesFinishedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelUnsubscribedEvent(ChannelUnsubscribedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelUnsubscribesFinishedEvent(ChannelUnsubscribesFinishedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelDescriptionUpdatedEvent(ChannelDescriptionUpdatedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::channelPasswordChangedEvent(ChannelPasswordChangedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::playbackShutdownCompletedEvent(PlaybackShutdownCompletedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::fileTransferStatusReceivedEvent(FileTransferStatusReceivedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::fileListReceivedEvent(FileListReceivedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

void Connection::fileListFinishedEvent(FileListFinishedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}
void Connection::fileInfoReceivedEvent(FileInfoReceivedEvent* event)
{
    Debug debug(Q_FUNC_INFO);
    // TODO: event
}

} // namespace TeamSpeakSdk

#include "moc_connection.cpp"
