#include "interfacemanager_p.h"
#include "interfacemanager_p_p.h"
#include "eventmanager_p.h"
#include "cachemanager_p.h"

#include "client.h"
#include "channel.h"
#include "connection.h"
#include "wavehandle.h"
#include "sounddevice.h"
#include "exception.h"

namespace TeamSpeakSdk {

static InterfaceManager* m_instance = Q_NULLPTR;
static InterfaceManagerPrivate*   d = Q_NULLPTR;

namespace {

bool no_error(ReturnCode error)
{
    return error == ReturnCode::Ok || error == ReturnCode::OkNoUpdate;
}

inline bool freeMemory(void* pointer)
{
    return d->freeMemory(pointer) == ReturnCode::Ok;
}

template<
    class _Pointer, 
    class _Fn, 
    class _Result = std::decay_t<std::result_of_t<_Fn(_Pointer&)>>
> Q_REQUIRED_RESULT
inline decltype(auto) safe_read(_Pointer* pointer, _Fn call)
{
    QList<_Result> result;
    for (int i = 0; pointer[i] != 0; i++)
        result.push_back(call(pointer[i]));
    freeMemory(pointer);
    return result;
}

inline QString safe_read(char* pointer)
{
    const auto result = utils::to_string(pointer);
    freeMemory(pointer);
    return result;
}

inline QStringList safe_read(char** pointer)
{
    QStringList result;
    for (int i = 0; pointer[i] != Q_NULLPTR; ++i) {
        result.push_back(safe_read(pointer[i]));
    }
    freeMemory(pointer);
    return result;
}

inline QList<QPair<QString, QString>> safe_read(char*** pointer)
{
    QList<QPair<QString, QString>> result;
    for (int i = 0; pointer[i] != Q_NULLPTR; ++i) {
        result.push_back(qMakePair(
            safe_read(pointer[i][0]),
            safe_read(pointer[i][1])
        ));
        freeMemory(pointer[i]);
    }
    freeMemory(pointer);
    return result;
}

template <class Call, class ...Args>
inline ReturnCode invoke_method(Call call, Args... args)
{
    return static_cast<ReturnCode>(call(std::forward<Args>(args)...));
}

} // namespace internal

InterfaceManager* InterfaceManager::instance()
{
    return m_instance;
}

InterfaceManager::InterfaceManager(QObject* parent)
    : QObject(parent)
{
    m_instance = this;
}

InterfaceManager::~InterfaceManager()
{
    m_instance = Q_NULLPTR;
    delete d;d = Q_NULLPTR;
}

void InterfaceManager::setLibrary(QLibrary* lib)
{
    delete d;
    d = new InterfaceManagerPrivate;
    d->setLibrary(lib);
}

bool InterfaceManager::initClientLib(LogTypes usedLogTypes, const QString& logFileFolder, const QString& resourcesFolder)
{
    const auto byte_logFileFolder   = utils::to_byte(logFileFolder);
    const auto byte_resourcesFolder = utils::to_byte(resourcesFolder);

    const auto error = invoke_method(
        d->initClientLib,
        EventManager::clientUIFunctions(), 
        EventManager::clientUIFunctionsRare(),
        utils::underlay(usedLogTypes), 
        byte_logFileFolder.data(), 
        byte_resourcesFolder.data()
    );
    return no_error(error);
}

bool InterfaceManager::destroyClientLib()
{
    const auto error = invoke_method(
        d->destroyClientLib
    );
    return no_error(error);
}


QString InterfaceManager::getClientLibVersion()
{
    char* version;
    const auto error = invoke_method(
        d->getClientLibVersion, 
        &version
    );
    return no_error(error) ? safe_read(version) : QString();
}

Library::Version InterfaceManager::getClientLibVersionNumber()
{
    uint64 result;
    const auto error = invoke_method(
        d->getClientLibVersionNumber,
        &result
    );
    return no_error(error) ? static_cast<Library::Version>(result) : static_cast<Library::Version>(0);
}

uint64 InterfaceManager::spawnNewServerConnectionHandler(int port)
{
    uint64 result;
    const auto error = invoke_method(
        d->spawnNewServerConnectionHandler, 
        port, 
        &result
    );
    return no_error(error) ? result : 0;
}

ReturnCode InterfaceManager::destroyServerConnectionHandler(const Connection* server)
{
    const auto error = invoke_method(
        d->destroyServerConnectionHandler, 
        server->id()
    );
    return error;
}

QString InterfaceManager::createIdentity()
{
    char* value;
    const auto error = invoke_method(
        d->createIdentity,
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

QString InterfaceManager::identityStringToUniqueIdentifier(const QString& identityString)
{
    const auto byte_identityString = utils::to_byte(identityString);

    char* value;
    const auto error = invoke_method(
        d->identityStringToUniqueIdentifier,
        byte_identityString.data(), 
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

QList<ISoundDevice*> InterfaceManager::getPlaybackDeviceList(const QString& modeID)
{
    const auto byte_modeID = utils::to_byte(modeID);

    char*** value;
    const auto error = invoke_method(
        d->getPlaybackDeviceList, 
        byte_modeID.data(), 
        &value
    );
    return no_error(error) ? utils::to_list(safe_read(value), [modeID](auto piar) -> ISoundDevice* {
        return new SoundDevice(modeID, piar.second, piar.first);
    }) : QList<ISoundDevice*>();
}

QList<ISoundDevice*> InterfaceManager::getCaptureDeviceList(const QString& modeID)
{
    const auto byte_modeID = utils::to_byte(modeID);

    char*** value;
    const auto error = invoke_method(
        d->getCaptureDeviceList, 
        byte_modeID.data(),
        &value
    );
    return no_error(error) ? utils::to_list(safe_read(value), [modeID](auto piar) -> ISoundDevice* {
        return new SoundDevice(modeID, piar.second, piar.first);
    }) : QList<ISoundDevice*>();
}

QStringList InterfaceManager::getPlaybackModeList()
{
    char** value;
    const auto error = invoke_method(
        d->getPlaybackModeList,
        &value
    );
    return no_error(error) ? safe_read(value) : QStringList();
}

QStringList InterfaceManager::getCaptureModeList()
{
    char** value;
    const auto error = invoke_method(
        d->getCaptureModeList,
        &value
    );
    return no_error(error) ? safe_read(value) : QStringList();
}

bool InterfaceManager::openPlaybackDevice(
    const Connection* server, 
    const ISoundDevice* playbackDevice)
{
    const auto byte_modeID = utils::to_byte(playbackDevice ? playbackDevice->mode() : QString());
    const auto byte_device = utils::to_byte(playbackDevice ? playbackDevice->name() : QString());

    const auto error = invoke_method(
        d->openPlaybackDevice, 
        server->id(), 
        byte_modeID.data(),
        byte_device.data()
    );
    return no_error(error);
}

bool InterfaceManager::openCaptureDevice(
    const Connection* server, 
    const ISoundDevice* captureDevice)
{
    const auto byte_modeID = utils::to_byte(captureDevice->mode());
    const auto byte_device = utils::to_byte(captureDevice->name());

    const auto error = invoke_method(
        d->openCaptureDevice, 
        server->id(), 
        byte_modeID.data(), 
        byte_device.data()
    );
    return no_error(error);
}

QString InterfaceManager::getCurrentPlaybackDeviceName(
    const Connection* server, bool* isDefault)
{
    char* value; 
    int nIsDefault;
    const auto error = invoke_method(
        d->getCurrentPlaybackDeviceName, 
        server->id(),
        &value,
        &nIsDefault
    );
    if (no_error(error)) {
        utils::make_value(isDefault, bool(nIsDefault));
        return safe_read(value);
    } else {
        return QString();
    }
}

QString InterfaceManager::getCurrentCaptureDeviceName(
    const Connection* server, bool* isDefault)
{
    char* value;
    int nIsDefault;
    const auto error = invoke_method(
        d->getCurrentCaptureDeviceName, 
        server->id(),
        &value,
        &nIsDefault
    );

    if (no_error(error)) {
        utils::make_value(isDefault, bool(nIsDefault));
        return safe_read(value);
    } else {
        return QString();
    }
}

QString InterfaceManager::getCurrentPlayBackMode(const Connection* server)
{
    char* value;
    const auto error = invoke_method(
        d->getCurrentPlayBackMode, 
        server->id(),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

QString InterfaceManager::getCurrentCaptureMode(const Connection* server)
{
    char* value;
    const auto error = invoke_method(
        d->getCurrentCaptureMode, 
        server->id(),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

bool InterfaceManager::initiateGracefulPlaybackShutdown(const Connection* server)
{
    const auto error = invoke_method(
        d->initiateGracefulPlaybackShutdown, 
        server->id()
    );
    return no_error(error);
}

bool InterfaceManager::closePlaybackDevice(const Connection* server)
{
    const auto error = invoke_method(
        d->closePlaybackDevice, 
        server->id()
    );
    return no_error(error);
}

bool InterfaceManager::closeCaptureDevice(const Connection* server)
{
    const auto error = invoke_method(
        d->closeCaptureDevice, 
        server->id()
    );
    return no_error(error);
}

bool InterfaceManager::activateCaptureDevice(const Connection* server)
{
    const auto error = invoke_method(
        d->activateCaptureDevice, 
        server->id()
    );
    return no_error(error);
}

WaveHandle* InterfaceManager::playWaveFileHandle(
    const Connection* server, 
    const QString& path, 
    bool loop)
{
    const auto byte_path = utils::to_byte(path);

    uint64 result;
    const auto error = invoke_method(
        d->playWaveFileHandle,
        server->id(), 
        byte_path.data(),
        loop, 
        &result
    );
    return no_error(error) ? server->getWaveHandle(result) : Q_NULLPTR;
}

bool InterfaceManager::pauseWaveFileHandle(const WaveHandle* waveHandle, bool pause)
{
    const auto error = invoke_method(
        d->pauseWaveFileHandle,
        waveHandle->connection()->id(), 
        waveHandle->id(),
        pause
    );
    return no_error(error);
}

bool InterfaceManager::closeWaveFileHandle(const WaveHandle* waveHandle)
{
    const auto error = invoke_method(
        d->closeWaveFileHandle,
        waveHandle->connection()->id(), 
        waveHandle->id());
    return no_error(error);
}

bool InterfaceManager::registerCustomDevice(const CustomDevice* device)
{
    const auto byte_deviceID = utils::to_byte(device->id());
    const auto byte_name     = utils::to_byte(device->name());

    const auto error = invoke_method(
        d->registerCustomDevice,
        byte_deviceID.data(),
        byte_name.data(), 
        utils::underlay(device->captureRate()),
        device->captureChannels(), 
        utils::underlay(device->playbackRate()),
        device->playbackChannels()
    );
    return no_error(error);
}

bool InterfaceManager::unregisterCustomDevice(const CustomDevice* device)
{
    const auto byte_deviceID = utils::to_byte(device->id());

    const auto error = invoke_method(
        d->unregisterCustomDevice, 
        byte_deviceID.data()
    );
    return no_error(error);
}

bool InterfaceManager::processCustomCaptureData(
    const QString& deviceName, 
    QVector<short>& buffer)
{
    const auto byte_deviceName = utils::to_byte(deviceName);

    const auto error = invoke_method(
        d->processCustomCaptureData, 
        byte_deviceName.data(),
        buffer.data(),
        buffer.size()
    );
    return no_error(error);
}

bool InterfaceManager::acquireCustomPlaybackData(
    const QString& deviceName, 
    QVector<short>& buffer)
{
    const auto byte_deviceName = utils::to_byte(deviceName);

    const auto error = invoke_method(
        d->acquireCustomPlaybackData, 
        byte_deviceName.data(),
        buffer.data(),
        buffer.size()
    );
    return no_error(error);
}

bool InterfaceManager::setLocalTestMode(const Connection* server, TestMode value)
{
    const auto error = invoke_method(
        d->setLocalTestMode, 
        server->id(),
        utils::underlay(value)
    );
    return no_error(error);
}

bool InterfaceManager::startVoiceRecording(const Connection* server)
{
    const auto error = invoke_method(
        d->startVoiceRecording, 
        server->id()
    );
    return no_error(error);
}

bool InterfaceManager::stopVoiceRecording(const Connection* server)
{
    const auto error = invoke_method(
        d->stopVoiceRecording, 
        server->id()
    );
    return no_error(error);
}

bool InterfaceManager::allowWhispersFrom(const Client* client)
{
    const auto error = invoke_method(
        d->allowWhispersFrom, 
        client->connection()->id(), 
        client->id());
    return no_error(error);
}

bool InterfaceManager::removeFromAllowedWhispersFrom(const Client* client)
{
    const auto error = invoke_method(
        d->removeFromAllowedWhispersFrom,
        client->connection()->id(),
        client->id()
    );
    return no_error(error);
}

bool InterfaceManager::systemset3DListenerAttributes(
    const Connection* server, 
    const Vector3D* position, 
    const Vector3D* forward, 
    const Vector3D* up)
{
    const auto error = invoke_method(
        d->systemset3DListenerAttributes, 
        server->id(),
        position,
        forward,
        up
    );
    return no_error(error);
}

bool InterfaceManager::set3DWaveAttributes(
    const WaveHandle* waveHandle,
    const Vector3D* position)
{
    const auto error = invoke_method(
        d->set3DWaveAttributes,
        waveHandle->connection()->id(),
        waveHandle->id(),
        position
    );
    return no_error(error);
}

bool InterfaceManager::systemset3DSettings(
    const Connection* server, 
    float distanceFactor, 
    float rolloffScale)
{
    const auto error = invoke_method(
        d->systemset3DSettings, 
        server->id(),
        distanceFactor,
        rolloffScale
    );
    return no_error(error);
}

bool InterfaceManager::channelset3DAttributes(const Client* client, const Vector3D* position)
{
    const auto error = invoke_method(
        d->channelset3DAttributes, 
        client->connection()->id(),
        client->id(),
        position
    );
    return no_error(error);
}

float InterfaceManager::getPreProcessorInfoValueFloat(const Connection* server, const QString& ident)
{
    const auto byte_ident = utils::to_byte(ident);

    float result;
    const auto error = invoke_method(
        d->getPreProcessorInfoValueFloat,
        server->id(),
        byte_ident.data(),
        &result
    );
    return no_error(error) ? result : .0;
}

QString InterfaceManager::getPreProcessorConfigValue(const Connection* server, const QString& ident)
{
    const auto byte_ident = utils::to_byte(ident);

    char* value;
    const auto error = invoke_method(
        d->getPreProcessorConfigValue,
        server->id(),
        byte_ident.data(),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

bool InterfaceManager::setPreProcessorConfigValue(
    const Connection* server, 
    const QString& ident, 
    const QString& value)
{
    const auto byte_ident = utils::to_byte(ident);
    const auto byte_value = utils::to_byte(value);

    const auto error = invoke_method(
        d->setPreProcessorConfigValue,
        server->id(), 
        byte_ident.data(), 
        byte_value.data()
    );
    return no_error(error);
}

float InterfaceManager::getPlaybackConfigValueAsFloat(const Connection* server, const QString& ident)
{
    const auto byte_ident = utils::to_byte(ident);

    float result;
    const auto error = invoke_method(
        d->getPlaybackConfigValueAsFloat,
        server->id(), 
        byte_ident.data(), 
        &result
    );
    return no_error(error) ? result : .0;
}

bool InterfaceManager::setPlaybackConfigValue(
    const Connection* server,
    const QString& ident,
    const QString& value)
{
    const auto byte_ident = utils::to_byte(ident);
    const auto byte_value = utils::to_byte(value);

    const auto error = invoke_method(
        d->setPlaybackConfigValue,
        server->id(), 
        byte_ident.data(), 
        byte_value.data()
    );
    return no_error(error);
}

bool InterfaceManager::setClientVolumeModifier(
    const Client* client,
    float value)
{
    const auto error = invoke_method(
        d->setClientVolumeModifier,
        client->connection()->id(), 
        client->id(), 
        value
    );
    return no_error(error);
}

bool InterfaceManager::logMessage(
    const QString& logMessage,
    LogLevel level,
    const QString& channel,
    const Connection* connection)
{
    const auto byte_message = utils::to_byte(logMessage);
    const auto byte_channel = utils::to_byte(channel);

    const auto error = invoke_method(
        d->logMessage,
        byte_message.data(), 
        level,
        byte_channel.data(), 
        connection ? connection->id() : 0
    );
    return no_error(error);
}

bool InterfaceManager::setLogVerbosity(LogLevel level)
{
    const auto error = invoke_method(
        d->setLogVerbosity, 
        level
    );
    return no_error(error);
}

QString InterfaceManager::getErrorMessage(ReturnCode error)
{
    char* message;
    const auto _error = invoke_method(
        d->getErrorMessage,
        utils::underlay(error),
        &message
    );
    return no_error(error) ? safe_read(message) : QString();
}

ReturnCode InterfaceManager::startConnection(
    const Connection* server,
    const QString& identity,
    const QString& ip,
    uint port,
    const QString& nickname,
    const QStringList& defaultChannelArray,
    const QString& defaultChannelPassword,
    const QString& serverPassword)
{
    const auto byte_identity        = utils::to_byte(identity);
    const auto byte_addres          = utils::to_byte(ip);
    const auto byte_nickname        = utils::to_byte(nickname);
    const auto byte_defaultPassword = utils::to_byte(defaultChannelPassword);
    const auto byte_serverPassword  = utils::to_byte(serverPassword);

    const auto error = invoke_method(
        d->startConnection,
        server->id(), 
        byte_identity.data(), 
        byte_addres.data(), 
        port, 
        byte_nickname.data(), 
        Q_NULLPTR, 
        byte_defaultPassword.data(), 
        byte_serverPassword.data()
    );
    return error;
}

ReturnCode InterfaceManager::startConnection(
    const Connection* server,
    const QString& identity,
    const QString& ip,
    uint port,
    const QString& nickname,
    uint64 defaultChannelID,
    const QString& defaultChannelPassword,
    const QString& serverPassword)
{
    const auto byte_identity        = utils::to_byte(identity);
    const auto byte_addres          = utils::to_byte(ip);
    const auto byte_nickname        = utils::to_byte(nickname);
    const auto byte_defaultPassword = utils::to_byte(defaultChannelPassword);
    const auto byte_serverPassword  = utils::to_byte(serverPassword);

    if (d->startConnectionWithChannelID != Q_NULLPTR)
        return invoke_method(
            d->startConnectionWithChannelID,
            server->id(), 
            byte_identity.data(), 
            byte_addres.data(), 
            port, 
            byte_nickname.data(), 
            defaultChannelID, 
            byte_defaultPassword.data(), 
            byte_serverPassword.data()
        );
    else
        throw std::exception("StartConnection with defaultChannelID requires v3.0.4");
}

ReturnCode InterfaceManager::stopConnection(const Connection* server, const QString& quitMessage)
{
    const auto byte_quitMessage = utils::to_byte(quitMessage);

    return invoke_method(
        d->stopConnection, 
        server->id(), 
        byte_quitMessage.data()
    );
}

ReturnCode InterfaceManager::requestClientMove(
    const Client* client,
    const Channel* channel,
    const QString& password,
    const QString& returnCode)
{
    const auto byte_password   = utils::to_byte(password);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientMove, 
        client->connection()->id(), 
        client->id(), 
        channel->id(), 
        byte_password.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestClientVariables(
    const Client* client,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientVariables,
        client->connection()->id(), 
        client->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestClientKickFromChannel(
    const Client* client,
    const QString& kickReason,
    const QString& returnCode)
{
    const auto byte_kickReason = utils::to_byte(kickReason);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientKickFromChannel, 
        client->connection()->id(), 
        client->id(), 
        byte_kickReason.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestClientKickFromServer(
    const Client* client,
    const QString& kickReason,
    const QString& returnCode)
{
    const auto byte_kickReason = utils::to_byte(kickReason);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientKickFromServer,
        client->connection()->id(), 
        client->id(), 
        byte_kickReason.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestChannelDelete(
    const Channel* channel,
    bool force,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestChannelDelete,
        channel->connection()->id(), 
        channel->id(), 
        force ? 1 : 0, 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestChannelMove(
    const Channel* channel,
    const Channel* newChannelParent,
    const Channel* newChannelOrder,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestChannelMove,
        channel->connection()->id(), 
        channel->id(), 
        newChannelParent->id(), 
        newChannelOrder->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestSendPrivateTextMsg(
    const Client* targetClient,
    const QString& message,
    const QString& returnCode)
{
    const auto byte_message    = utils::to_byte(message);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestSendPrivateTextMsg,
        targetClient->connection()->id(), 
        byte_message.data(), 
        targetClient->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestSendChannelTextMsg(
    const Channel* targetChannel,
    const QString& message,
    const QString& returnCode)
{
    const auto byte_message    = utils::to_byte(message);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestSendChannelTextMsg,
        targetChannel->connection()->id(), 
        byte_message.data(), 
        targetChannel->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestSendServerTextMsg(
    const Connection* targetServer,
    const QString& message,
    const QString& returnCode)
{
    const auto byte_message    = utils::to_byte(message);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestSendServerTextMsg,
        targetServer->id(), 
        byte_message.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestConnectionInfo(
    const Client* client,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestConnectionInfo,
        client->connection()->id(), 
        client->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestClientSetWhisperList(
    const Client* client,
    const QList<Channel*>& channels,
    const QList<Client*>& clients,
    const QString& returnCode)
{
    const auto channelIDArray  = utils::to_array(channels, [](Channel* channel) { return channel->id(); });
    const auto clientIDArray   = utils::to_array(clients, [](Client* client) { return client->id(); });
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientSetWhisperList,
        client->connection()->id(), 
        client->id(), 
        channelIDArray.data(), 
        clientIDArray.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestChannelSubscribe(
    const QList<Channel*>& channels,
    const QString& returnCode)
{
    const auto channelIDArray  = utils::to_array(channels, [](Channel* value){ return value->id(); });
    const auto byte_returnCode = utils::to_byte(returnCode);

    auto server = channels[0]->connection();
    const auto error = invoke_method(
        d->requestChannelSubscribe,
        server->id(), 
        channelIDArray.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestChannelSubscribeAll(
    const Connection* server,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestChannelSubscribeAll,
        server->id(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestChannelUnsubscribe(
    const QList<Channel*>& channels,
    const QString& returnCode)
{
    const auto channelIDArray  = utils::to_array(channels, [](Channel* channel){ return channel->id(); });
    const auto byte_returnCode = utils::to_byte(returnCode);

    auto server = channels[0]->connection();
    const auto error = invoke_method(
        d->requestChannelUnsubscribe, 
        server->id(), 
        channelIDArray.data(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestChannelUnsubscribeAll(
    const Connection* server,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestChannelUnsubscribeAll,
        server->id(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestChannelDescription(
    const Channel* channel,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestChannelDescription,
        channel->connection()->id(), 
        channel->id(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestMuteClients(
    const QList<Client*>& clients,
    const QString& returnCode)
{
    const auto clientIDArray   = utils::to_array(clients, [](Client* client) { return client->id(); });
    const auto byte_returnCode = utils::to_byte(returnCode);

    auto server = clients[0]->connection();
    const auto error = invoke_method(
        d->requestMuteClients,
        server->id(), 
        clientIDArray.data(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestUnmuteClients(
    const QList<Client*>& clients,
    const QString& returnCode)
{
    const auto clientIDArray   = utils::to_array(clients, [](Client* client) { return client->id(); });
    const auto byte_returnCode = utils::to_byte(returnCode);

    auto server = clients[0]->connection();
    const auto error = invoke_method(
        d->requestUnmuteClients,
        server->id(), 
        clientIDArray.data(), 
        byte_returnCode.data()
    );
    return (error);
}

ReturnCode InterfaceManager::requestClientIDs(
    const Connection* server,
    const QString& uniqueIdentifier, 
    const QString& returnCode)
{
    const auto byte_uniqueIdentifier = utils::to_byte(uniqueIdentifier);
    const auto byte_returnCode       = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestClientIDs, 
        server->id(), 
        byte_uniqueIdentifier.data(), 
        byte_returnCode.data()
    );

    return (error);
}

quint16 InterfaceManager::getClientID(const Connection* server)
{
    quint16 result;
    const auto error = invoke_method(
        d->getClientID,
        server->id(), 
        &result
    );
    return no_error(error) ? result : 0;
}

ConnectStatus InterfaceManager::getConnectionStatus(
    const Connection* server)
{
    int result;
    const auto error = invoke_method(
        d->getConnectionStatus,
        server->id(),
        &result
    );
    return no_error(error) ? static_cast<ConnectStatus>(result) : ConnectStatus::Disconnected;
}

uint64 InterfaceManager::getConnectionVariableAsUInt64(
    const Client* client, 
    ConnectionProperty flag)
{
    uint64 result;
    const auto error = invoke_method(
        d->getConnectionVariableAsUInt64,
        client->connection()->id(),
        client->id(),
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : 0;
}

double InterfaceManager::getConnectionVariableAsDouble(
    const Client* client, 
    ConnectionProperty flag)
{
    double result;
    const auto error = invoke_method(
        d->getConnectionVariableAsDouble, 
        client->connection()->id(), 
        client->id(), 
        utils::underlay(flag), 
        &result
    );
    return no_error(error) ? result : .0;
}

QString InterfaceManager::getConnectionVariableAsString(
    const Client* client, 
    ConnectionProperty flag)
{
    char* value;
    const auto error = invoke_method(
        d->getConnectionVariableAsString,
        client->connection()->id(),
        client->id(), 
        utils::underlay(flag), 
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

bool InterfaceManager::cleanUpConnectionInfo(const Client* client)
{
    const auto error = invoke_method(
        d->cleanUpConnectionInfo,
        client->connection()->id(), 
        client->id()
    );
    return no_error(error);
}

int InterfaceManager::getClientSelfVariableAsInt(const Connection* server, ClientProperty flag)
{
    int result;
    const auto error = invoke_method(
        d->getClientSelfVariableAsInt,
        server->id(),
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : -1;
}

QString InterfaceManager::getClientSelfVariableAsString(const Connection* server, ClientProperty flag)
{
    char* result;
    const auto error = invoke_method(
        d->getClientSelfVariableAsString,
        server->id(),
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? safe_read(result) : QString();
}

bool InterfaceManager::setClientSelfVariableAsInt(
    const Connection* server, 
    ClientProperty flag, int value)
{
    const auto error = invoke_method(
        d->setClientSelfVariableAsInt,
        server->id(), 
        utils::underlay(flag), 
        value
    );

    return no_error(error);
}

bool InterfaceManager::setClientSelfVariableAsString(
    const Connection* server,
    ClientProperty flag,
    const QString& value)
{
    const auto byte_value = utils::to_byte(value);

    const auto error = invoke_method(
        d->setClientSelfVariableAsString,
        server->id(), 
        utils::underlay(flag),
        byte_value.data()
    );
    return no_error(error);
}

ReturnCode InterfaceManager::flushClientSelfUpdates(
    const Connection* server,
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->flushClientSelfUpdates,
        server->id(), 
        byte_returnCode.data()
    );

    return (error);
}

int InterfaceManager::getClientVariableAsInt(
    const Client* client,
    ClientProperty flag)
{
    int result;
    const auto error = invoke_method(
        d->getClientVariableAsInt,
        client->connection()->id(), 
        client->id(), 
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : -1;
}

uint64 InterfaceManager::getClientVariableAsUInt64(
    const Client* client,
    ClientProperty flag)
{
    uint64 result;
    const auto error = invoke_method(
        d->getClientVariableAsUInt64,
        client->connection()->id(), 
        client->id(), 
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : 0;
}

QString InterfaceManager::getClientVariableAsString(
    const Client* client,
    ClientProperty flag)
{
    char* value;
    const auto error = invoke_method(
        d->getClientVariableAsString,
        client->connection()->id(),
        client->id(),
        utils::underlay(flag),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

QList<Client*> InterfaceManager::getClientList(const Connection* server)
{
    uint16* value;
    const auto error = invoke_method(
        d->getClientList,
        server->id(), 
        &value
    );

    return no_error(error) ? safe_read(value, [server](uint16 id) {
        return server->getClient(id);
    }): QList<Client*>();
}

Channel* InterfaceManager::getChannelOfClient(const Client* client)
{
    uint64 channelId;
    const auto error = invoke_method(
        d->getChannelOfClient,
        client->connection()->id(),
        client->id(),
        &channelId
    );
    return no_error(error) ? client->connection()->getChannel(channelId) : Q_NULLPTR;
}

int InterfaceManager::getChannelVariableAsInt(const Channel* channel, ChannelProperty flag)
{
    int result;
    const auto error = invoke_method(
        d->getChannelVariableAsInt,
        channel->connection()->id(), 
        channel->id(), 
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : -1;
}

uint64 InterfaceManager::getChannelVariableAsUInt64(
    const Channel* channel, 
    ChannelProperty flag)
{
    uint64 result;
    const auto error = invoke_method(
        d->getChannelVariableAsUInt64,
        channel->connection()->id(),
        channel->id(),
        utils::underlay(flag),
        &result
    );
    return no_error(error) ? result : 0;
}

QString InterfaceManager::getChannelVariableAsString(
    const Channel* channel, 
    ChannelProperty flag)
{
    char* value;
    const auto error = invoke_method(
        d->getChannelVariableAsString,
        channel->connection()->id(),
        channel->id(),
        utils::underlay(flag),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

bool InterfaceManager::setChannelVariableAsInt(
    const Channel* channel, 
    ChannelProperty flag, 
    int value)
{
    const auto error = invoke_method(
        d->setChannelVariableAsInt,
        channel->connection()->id(), 
        channel->id(), 
        utils::underlay(flag),
        value
    );
    return no_error(error);
}

bool InterfaceManager::setChannelVariableAsUInt64(
    const Channel* channel, 
    ChannelProperty flag, 
    uint64 value)
{
    const auto error = invoke_method(
        d->setChannelVariableAsUInt64,
        channel->connection()->id(),
        channel->id(), 
        utils::underlay(flag),
        value
    );
    return no_error(error);
}

bool InterfaceManager::setChannelVariableAsString(
    const Channel* channel, 
    ChannelProperty flag, 
    const QString& value)
{
    const auto byte_value = utils::to_byte(value);

    const auto error = invoke_method(
        d->setChannelVariableAsString,
        channel->connection()->id(), 
        channel->id(), 
        utils::underlay(flag), 
        byte_value.data()
    );
    return no_error(error);
}

ReturnCode InterfaceManager::flushChannelUpdates(
    const Channel* channel, 
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->flushChannelUpdates,
        channel->connection()->id(), 
        channel->id(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::flushChannelCreation(
    const Connection* server, 
    const Channel* parentChannel, 
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->flushChannelCreation,
        server->id(), 
        parentChannel->id(),
        byte_returnCode.data()
    );
    return (error);
}

QList<Channel*> InterfaceManager::getChannelList(const Connection* server)
{
    uint64* value;
    const auto error = invoke_method(
        d->getChannelList,
        server->id(), 
        &value);
    
    return no_error(error) ? safe_read(value, [server](uint64 id) {
        return server->getChannel(id);
    }) : QList<Channel*>();
}

QList<Client*> InterfaceManager::getChannelClientList(const Channel* channel)
{
    quint16* value;
    const auto error = invoke_method(
        d->getChannelClientList,
        channel->connection()->id(), 
        channel->id(), 
        &value
    );

    return no_error(error) ? safe_read(value, [channel](quint16 id) {
        return channel->connection()->getClient(id);
    }) : QList<Client*>();
}

Channel* InterfaceManager::getParentChannelOfChannel(const Channel* channel)
{
    uint64 result;
    const auto error = invoke_method(
        d->getParentChannelOfChannel,
        channel->connection()->id(),
        channel->id(),
        &result
    );
    return no_error(error) ? channel->connection()->getChannel(result) : Q_NULLPTR;
}

int InterfaceManager::getChannelEmptySecs(const Channel* channel)
{
    int result;
    const auto error = invoke_method(
        d->getChannelEmptySecs,
        channel->connection()->id(),
        channel->id(),
        &result
    );
    return no_error(error) ? result : -1;
}

QList<Connection*> InterfaceManager::getServerConnectionHandlerList()
{
    uint64* value;
    const auto error = invoke_method(
        d->getServerConnectionHandlerList,
        &value
    );

    return no_error(error) ? safe_read(value, [](uint64 id) {
        return Library::getServer(id);
    }) : QList<Connection*>();
}

int InterfaceManager::getServerVariableAsInt(const Connection* server, VirtualServerProperty flag)
{
    int result;
    const auto error = invoke_method(
        d->getServerVariableAsInt,
        server->id(), 
        utils::underlay(flag), 
        &result
    );
    return no_error(error) ? result : -1;
}

uint64 InterfaceManager::getServerVariableAsUInt64(const Connection* server, VirtualServerProperty flag)
{
    uint64 result;
    const auto error = invoke_method(
        d->getServerVariableAsUInt64,
        server->id(), 
        utils::underlay(flag), 
        &result
    );
    return no_error(error) ? result : 0;
}

QString InterfaceManager::getServerVariableAsString(const Connection* server, VirtualServerProperty flag)
{
    char* value;
    const auto error = invoke_method(
        d->getServerVariableAsString,
        server->id(),
        utils::underlay(flag), 
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

bool InterfaceManager::requestServerVariables(const Connection* server)
{
    const auto error = invoke_method(
        d->requestServerVariables,
        server->id()
    );
    return no_error(error);
}

QString InterfaceManager::getTransferFileName(const FileTransfer* transfer)
{
    char* value;
    const auto error = invoke_method(
        d->getTransferFileName,
        transfer->id(),
        &value
    );

    return no_error(error) ? safe_read(value) : QString();
}

QString InterfaceManager::getTransferFilePath(const FileTransfer* transfer)
{
    char* value;
    const auto error = invoke_method(
        d->getTransferFilePath,
        transfer->id(),
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

QString InterfaceManager::getTransferFileRemotePath(const FileTransfer* transfer)
{
    char* value;
    const auto error = invoke_method(
        d->getTransferFileRemotePath,
        transfer->id(), 
        &value
    );
    return no_error(error) ? safe_read(value) : QString();
}

uint64 InterfaceManager::getTransferFileSize(const FileTransfer* transfer)
{
    uint64 result;
    const auto error = invoke_method(
        d->getTransferFileSize,
        transfer->id(),
        &result
    );
    return no_error(error) ? result : 0;
}

uint64 InterfaceManager::getTransferFileSizeDone(const FileTransfer* transfer)
{
    uint64 result;
    const auto error = invoke_method(
        d->getTransferFileSizeDone,
        transfer->id(), 
        &result
    );
    return no_error(error) ? result : 0;
}

bool InterfaceManager::isTransferSender(const FileTransfer* transfer)
{
    int result;
    const auto error = invoke_method(
        d->isTransferSender,
        transfer->id(), 
        &result
    );
    return no_error(error) ? result != 0 : false;
}

FileTransfer::State InterfaceManager::getTransferStatus(const FileTransfer* transfer)
{
    int result;
    const auto error = invoke_method(
        d->getTransferStatus,
        transfer->id(),
        &result
    );
    return no_error(error) ? static_cast<FileTransfer::State>(result) : FileTransfer::State::Initializing;
}

float InterfaceManager::getCurrentTransferSpeed(const FileTransfer* transfer)
{
    float result;
    const auto error = invoke_method(
        d->getCurrentTransferSpeed,
        transfer->id(),
        &result
    );
    return no_error(error) ? result : .0;
}

float InterfaceManager::getAverageTransferSpeed(const FileTransfer* transfer)
{
    float result;
    const auto error = invoke_method(
        d->getAverageTransferSpeed,
        transfer->id(),
        &result
    );
    return no_error(error) ? result : .0;
}

uint64 InterfaceManager::getTransferRunTime(const FileTransfer* transfer)
{
    uint64 result;
    const auto error = invoke_method(
        d->getTransferRunTime, 
        transfer->id(),
        &result
    );
    return no_error(error) ? result : 0;
}

FileTransfer* InterfaceManager::sendFile(
    const Channel* channel, 
    const QString& channelPW, 
    const QString& file, 
    bool overwrite, 
    bool resume, 
    const QString& sourceDirectory, 
    const QString& returnCode)
{
    const auto byte_channelPW  = utils::to_byte(channelPW);
    const auto byte_file       = utils::to_byte(file);
    const auto byte_directory  = utils::to_byte(sourceDirectory);
    const auto byte_returnCode = utils::to_byte(returnCode);

    ushort fileId = 0;
    const auto error = invoke_method(
        d->sendFile,
        channel->connection()->id(), 
        channel->id(), 
        byte_channelPW.data(), 
        byte_file.data(), 
        overwrite ? 1 : 0, 
        resume ? 1 : 0, 
        byte_directory.data(), 
        &fileId, 
        byte_returnCode.data()
    );
    return no_error(error) ? channel->connection()->getTransfer(fileId) : Q_NULLPTR;
}

FileTransfer* InterfaceManager::requestFile(
    const Channel* channel, 
    const QString& channelPW, 
    const QString& file, 
    bool overwrite, 
    bool resume, 
    const QString& destinationDirectory, 
    const QString& returnCode)
{
    const auto byte_channelPW  = utils::to_byte(channelPW);
    const auto byte_file       = utils::to_byte(file);
    const auto byte_directory  = utils::to_byte(destinationDirectory);
    const auto byte_returnCode = utils::to_byte(returnCode);

    ushort fileId;
    const auto error = invoke_method(
        d->requestFile,
        channel->connection()->id(), 
        channel->id(), 
        byte_channelPW.data(), 
        byte_file.data(), 
        overwrite ? 1 : 0, 
        resume ? 1 : 0, 
        byte_directory.data(), 
        &fileId, 
        byte_returnCode.data()
    );

    return no_error(error) ? channel->connection()->getTransfer(fileId) : Q_NULLPTR;
}

ReturnCode InterfaceManager::haltTransfer(
    const FileTransfer* transfer, 
    bool deleteUnfinishedFile, 
    const QString& returnCode)
{
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->haltTransfer,
        transfer->connection()->id(),
        transfer->id(),
        deleteUnfinishedFile ? 1 : 0,
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestFileList(
    const Channel* channel, 
    const QString& channelPW, 
    const QString& path, 
    const QString& returnCode)
{
    const auto byte_channelPW  = utils::to_byte(channelPW);
    const auto byte_path       = utils::to_byte(path);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestFileList,
        channel->connection()->id(),
        channel->id(),
        byte_channelPW.data(),
        byte_path.data(),
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestFileInfo(
    const Channel* channel,
    const QString& channelPW,
    const QString& file,
    const QString& returnCode)
{
    const auto byte_channelPW  = utils::to_byte(channelPW);
    const auto byte_file       = utils::to_byte(file);
    const auto byte_returnCode = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestFileInfo,
        channel->connection()->id(), 
        channel->id(), 
        byte_channelPW.data(), 
        byte_file.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestDeleteFile(
    const Channel* channel,
    const QString& channelPW,
    const QStringList& files,
    const QString& returnCode)
{
    const auto byte_channelPW  = utils::to_byte(channelPW);
    const auto byte_returnCode = utils::to_byte(returnCode);
    /// Qt management memory is good
    auto byte_list  = utils::to_array(files, [](auto text) { return utils::to_byte(text); });
    auto byte_files = utils::to_array(byte_list, [](auto byte) { return byte.constData(); });
    const auto error = invoke_method(
        d->requestDeleteFile,
        channel->connection()->id(),
        channel->id(),
        byte_channelPW.data(),
        byte_files.data(),
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestCreateDirectory(
    const Channel* channel,
    const QString& channelPW,
    const QString& directoryPath,
    const QString& returnCode)
{
    const auto byte_channelPW     = utils::to_byte(channelPW);
    const auto byte_directoryPath = utils::to_byte(directoryPath);
    const auto byte_returnCode    = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestCreateDirectory,
        channel->connection()->id(), 
        channel->id(), 
        byte_channelPW.data(), 
        byte_directoryPath.data(), 
        byte_returnCode.data()
    );

    return (error);
}

ReturnCode InterfaceManager::requestRenameFile(
    const Channel* fromChannel,
    const QString& fromChannelPW,
    const Channel* toChannel,
    const QString& toChannelPW,
    const QString& oldFile,
    const QString& newFile,
    const QString& returnCode)
{
    const auto byte_fromChannelPW = utils::to_byte(fromChannelPW);
    const auto byte_toChannelPW   = utils::to_byte(toChannelPW);
    const auto byte_oldFile       = utils::to_byte(oldFile);
    const auto byte_newFile       = utils::to_byte(newFile);
    const auto byte_returnCode    = utils::to_byte(returnCode);

    const auto error = invoke_method(
        d->requestRenameFile,
        fromChannel->connection()->id(), 
        fromChannel->id(), 
        byte_fromChannelPW.data(), 
        toChannel->id(), 
        byte_toChannelPW.data(), 
        byte_oldFile.data(), 
        byte_newFile.data(), 
        byte_returnCode.data()
    );
    return (error);
}

uint64 InterfaceManager::getInstanceSpeedLimitUp()
{
    uint64 result;
    const auto error = invoke_method(
        d->getInstanceSpeedLimitUp,
        &result
    );
    return no_error(error) ? result : 0;
}

uint64 InterfaceManager::getInstanceSpeedLimitDown()
{
    uint64 result;
    const auto error = invoke_method(
        d->getInstanceSpeedLimitDown,
        &result
    );
    return no_error(error) ? result : 0;
}

uint64 InterfaceManager::getServerConnectionHandlerSpeedLimitUp(const Connection* server)
{
    uint64 result;
    const auto error = invoke_method(
        d->getServerConnectionHandlerSpeedLimitUp,
        server->id(),
        &result
    );
    return no_error(error) ? result : 0;
}

uint64 InterfaceManager::getServerConnectionHandlerSpeedLimitDown(const Connection* server)
{
    uint64 result;
    const auto error = invoke_method(
        d->getServerConnectionHandlerSpeedLimitDown,
        server->id(),
        &result
    );
    return no_error(error) ? result : 0;
}

uint64 InterfaceManager::getTransferSpeedLimit(const FileTransfer* transfer)
{
    uint64 result;
    const auto error = invoke_method(
        d->getTransferSpeedLimit,
        transfer->id(),
        &result
    );
    return no_error(error) ? result : 0;
}

bool InterfaceManager::setInstanceSpeedLimitUp(uint64 newLimit)
{
    const auto error = invoke_method(
        d->setInstanceSpeedLimitUp,
        newLimit
    );
    return no_error(error);
}

bool InterfaceManager::setInstanceSpeedLimitDown(uint64 newLimit)
{
    const auto error = invoke_method(
        d->setInstanceSpeedLimitDown,
        newLimit
    );
    return no_error(error);
}

bool InterfaceManager::setServerConnectionHandlerSpeedLimitUp(
    const Connection* server, 
    uint64 newLimit)
{
    const auto error = invoke_method(
        d->setServerConnectionHandlerSpeedLimitUp,
        server->id(),
        newLimit
    );
    return no_error(error);
}

bool InterfaceManager::setServerConnectionHandlerSpeedLimitDown(
    const Connection* server, 
    uint64 newLimit)
{
    const auto error = invoke_method(
        d->setServerConnectionHandlerSpeedLimitDown,
        server->id(),
        newLimit
    );
    return no_error(error);
}

bool InterfaceManager::setTransferSpeedLimit(
    const FileTransfer* transfer,
    uint64 newLimit)
{
    const auto error = invoke_method(
        d->setTransferSpeedLimit,
        transfer->id(),
        newLimit
    );
    return no_error(error);
}

void __init_interface_manager()
{
    (void) new InterfaceManager(qApp);
}

} // namespace TeamSpeakSdk

