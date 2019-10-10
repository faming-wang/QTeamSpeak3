#include "eventmanager_p.h"
#include "cachemanager_p.h"
#include "interfacemanager_p.h"

#include "client.h"
#include "channel.h"
#include "connection.h"
#include "exception.h"
#include "teamspeakevents.h"

namespace TeamSpeakSdk {

class EventManagerPrivate
{
public:
    EventManagerPrivate()
    {
        memset(&clientUIFunctions, 0, sizeof(struct ClientUIFunctions));
    }

    ~EventManagerPrivate()
    {

    }

    ClientUIFunctions clientUIFunctions;
    // ClientUIFunctionsRare clientUIRareFunctions;
};

static EventManager* m_instance = Q_NULLPTR;
static EventManagerPrivate*   d = Q_NULLPTR;

EventManager* EventManager::instance()
{
    return m_instance;
}

EventManager::~EventManager()
{
    m_instance = Q_NULLPTR;
    delete d;d = Q_NULLPTR;
}

EventManager::EventManager(QObject* parent)
    : QObject(parent)
{
    d = new EventManagerPrivate;
    d->clientUIFunctions.onConnectStatusChangeEvent              = onConnectStatusChangeEventWrapper;
    d->clientUIFunctions.onServerProtocolVersionEvent            = onServerProtocolVersionEventWrapper;
    d->clientUIFunctions.onNewChannelEvent                       = onNewChannelEventWrapper;
    d->clientUIFunctions.onNewChannelCreatedEvent                = onNewChannelCreatedEventWrapper;
    d->clientUIFunctions.onDelChannelEvent                       = onDelChannelEventWrapper;
    d->clientUIFunctions.onChannelMoveEvent                      = onChannelMoveEventWrapper;
    d->clientUIFunctions.onUpdateChannelEvent                    = onUpdateChannelEventWrapper;
    d->clientUIFunctions.onUpdateChannelEditedEvent              = onUpdateChannelEditedEventWrapper;
    d->clientUIFunctions.onUpdateClientEvent                     = onUpdateClientEventWrapper;
    d->clientUIFunctions.onClientMoveEvent                       = onClientMoveEventWrapper;
    d->clientUIFunctions.onClientMoveSubscriptionEvent           = onClientMoveSubscriptionEventWrapper;
    d->clientUIFunctions.onClientMoveTimeoutEvent                = onClientMoveTimeoutEventWrapper;
    d->clientUIFunctions.onClientMoveMovedEvent                  = onClientMoveMovedEventWrapper;
    d->clientUIFunctions.onClientKickFromChannelEvent            = onClientKickFromChannelEventWrapper;
    d->clientUIFunctions.onClientKickFromServerEvent             = onClientKickFromServerEventWrapper;
    d->clientUIFunctions.onClientIDsEvent                        = onClientIDsEventWrapper;
    d->clientUIFunctions.onClientIDsFinishedEvent                = onClientIDsFinishedEventWrapper;
    d->clientUIFunctions.onServerEditedEvent                     = onServerEditedEventWrapper;
    d->clientUIFunctions.onServerUpdatedEvent                    = onServerUpdatedEventWrapper;
    d->clientUIFunctions.onServerErrorEvent                      = onServerErrorEventWrapper;
    d->clientUIFunctions.onServerStopEvent                       = onServerStopEventWrapper;
    d->clientUIFunctions.onTextMessageEvent                      = onTextMessageEventWrapper;
    d->clientUIFunctions.onTalkStatusChangeEvent                 = onTalkStatusChangeEventWrapper;
    d->clientUIFunctions.onIgnoredWhisperEvent                   = onIgnoredWhisperEventWrapper;
    d->clientUIFunctions.onConnectionInfoEvent                   = onConnectionInfoEventWrapper;
    d->clientUIFunctions.onServerConnectionInfoEvent             = onServerConnectionInfoEventWrapper;
    d->clientUIFunctions.onChannelSubscribeEvent                 = onChannelSubscribeEventWrapper;
    d->clientUIFunctions.onChannelSubscribeFinishedEvent         = onChannelSubscribeFinishedEventWrapper;
    d->clientUIFunctions.onChannelUnsubscribeEvent               = onChannelUnsubscribeEventWrapper;
    d->clientUIFunctions.onChannelUnsubscribeFinishedEvent       = onChannelUnsubscribeFinishedEventWrapper;
    d->clientUIFunctions.onChannelDescriptionUpdateEvent         = onChannelDescriptionUpdateEventWrapper;
    d->clientUIFunctions.onChannelPasswordChangedEvent           = onChannelPasswordChangedEventWrapper;
    d->clientUIFunctions.onPlaybackShutdownCompleteEvent         = onPlaybackShutdownCompleteEventWrapper;
    d->clientUIFunctions.onSoundDeviceListChangedEvent           = onSoundDeviceListChangedEventWrapper;
    d->clientUIFunctions.onEditPlaybackVoiceDataEvent            = onEditPlaybackVoiceDataEventWrapper;
    d->clientUIFunctions.onEditPostProcessVoiceDataEvent         = onEditPostProcessVoiceDataEventWrapper;
    d->clientUIFunctions.onEditMixedPlaybackVoiceDataEvent       = onEditMixedPlaybackVoiceDataEventWrapper;
    d->clientUIFunctions.onEditCapturedVoiceDataEvent            = onEditCapturedVoiceDataEventWrapper;
    d->clientUIFunctions.onCustom3dRolloffCalculationClientEvent = onCustom3dRolloffCalculationClientEventWrapper;
    d->clientUIFunctions.onCustom3dRolloffCalculationWaveEvent   = onCustom3dRolloffCalculationWaveEventWrapper;
    d->clientUIFunctions.onUserLoggingMessageEvent               = onUserLoggingMessageEventWrapper;
    d->clientUIFunctions.onProvisioningSlotRequestResultEvent    = onProvisioningSlotRequestResultEventWrapper;
    d->clientUIFunctions.onCheckServerUniqueIdentifierEvent      = onCheckServerUniqueIdentifierEventWrapper;
    d->clientUIFunctions.onFileTransferStatusEvent               = onFileTransferStatusEventWrapper;
    d->clientUIFunctions.onFileListEvent                         = onFileListEventWrapper;
    d->clientUIFunctions.onFileListFinishedEvent                 = onFileListFinishedEventWrapper;
    d->clientUIFunctions.onFileInfoEvent                         = onFileInfoEventWrapper;
    d->clientUIFunctions.onCustomPacketEncryptEvent = onCustomPacketEncryptEventWrapper;
    d->clientUIFunctions.onCustomPacketDecryptEvent = onCustomPacketDecryptEventWrapper;
    d->clientUIFunctions.onClientPasswordEncrypt    = onClientPasswordEncryptEventWrapper;

    m_instance = this;
 }

ClientUIFunctions* EventManager::clientUIFunctions()
{
    return &d->clientUIFunctions;
}

ClientUIFunctionsRare* EventManager::clientUIFunctionsRare()
{
    return nullptr;
}

void EventManager::onConnectStatusChangeEventWrapper(uint64 serverId, int newStatus, uint errorNumber)
{
    auto server  = Library::getServer(serverId);

    auto event = new ConnectStatusChangedEvent;
    event->newStatus   = static_cast<ConnectStatus>(newStatus);
    event->errorNumber = ReturnCode(errorNumber);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerProtocolVersionEventWrapper(uint64 serverId, int protocolVersion)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerProtocolVersionEvent;
    event->protocolVersion = protocolVersion;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onNewChannelEventWrapper(uint64 serverId, uint64 channelID, uint64 channelParentID)
{
    auto server = Library::getServer(serverId);

    auto event = new NewChannelEvent;
    event->channel       = server->getChannel(channelID);
    event->channelParent = server->getChannel(channelParentID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onNewChannelCreatedEventWrapper(uint64 serverId, uint64 channelID, uint64 channelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new NewChannelCreatedEvent;
    event->channel                 = server->getChannel(channelID);
    event->channelParent           = server->getChannel(channelParentID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = utils::to_string(invokerName);
    event->invokerUniqueIdentifier = utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onDelChannelEventWrapper(uint64 serverId, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelDeletedEvent;
    event->channel                 = server->getChannel(channelID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = utils::to_string(invokerName);
    event->invokerUniqueIdentifier = utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelMoveEventWrapper(uint64 serverId, uint64 channelID, uint64 newChannelParentID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelMovedEvent;
    event->channel                 = server->getChannel(channelID);
    event->newChannelParent        = server->getChannel(newChannelParentID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = utils::to_string(invokerName);
    event->invokerUniqueIdentifier = utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateChannelEventWrapper(uint64 serverId, uint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUpdatedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateChannelEditedEventWrapper(uint64 serverId, uint64 channelID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelEditedEvent;
    event->channel                 = server->getChannel(channelID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = utils::to_string(invokerName);
    event->invokerUniqueIdentifier = utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateClientEventWrapper(uint64 serverId, uint16 clientID, uint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientUpdatedEvent;
    event->client                  = server->getClient(clientID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = utils::to_string(invokerName);
    event->invokerUniqueIdentifier = utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* moveMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMovedEvent;
    event->client      = server->getClient(clientID);
    event->oldChannel  = server->getChannel(oldChannelID);
    event->newChannel  = server->getChannel(newChannelID);
    event->visibility  = static_cast<Visibility>(visibility);
    event->moveMessage = utils::to_string(moveMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveSubscriptionEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility)
{
    auto server = Library::getServer(serverId);

    auto event = new SubscriptionClientMovedEvent;
    event->client     = server->getClient(clientID);
    event->oldChannel = server->getChannel(oldChannelID);
    event->newChannel = server->getChannel(newChannelID);
    event->visibility = static_cast<Visibility>(visibility);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveTimeoutEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, const char* timeoutMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMoveTimeoutEvent;
    event->client         = server->getClient(clientID);
    event->oldChannel     = server->getChannel(oldChannelID);
    event->newChannel     = server->getChannel(newChannelID);
    event->visibility     = static_cast<Visibility>(visibility);
    event->timeoutMessage = utils::to_string(timeoutMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveMovedEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMoverMovedEvent;
    event->client                = server->getClient(clientID);
    event->oldChannel            = server->getChannel(oldChannelID);
    event->newChannel            = server->getChannel(newChannelID);
    event->visibility            = static_cast<Visibility>(visibility);
    event->mover                 = server->getClient(moverID);
    event->moverName             = utils::to_string(moverName);
    event->moverUniqueIdentifier = utils::to_string(moverUniqueIdentifier);
    event->moveMessage           = utils::to_string(moveMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientKickFromChannelEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientKickFromChannelEvent;
    event->client                 = server->getClient(clientID);
    event->oldChannel             = server->getChannel(oldChannelID);
    event->newChannel             = server->getChannel(newChannelID);
    event->visibility             = static_cast<Visibility>(visibility);
    event->kicker                 = server->getClient(kickerID);
    event->kickerName             = utils::to_string(kickerName);
    event->kickerUniqueIdentifier = utils::to_string(kickerUniqueIdentifier);
    event->kickMessage            = utils::to_string(kickMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientKickFromServerEventWrapper(uint64 serverId, uint16 clientID, uint64 oldChannelID, uint64 newChannelID, int visibility, uint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientKickFromServerEvent;
    event->client                 = server->getClient(clientID);
    event->oldChannel             = server->getChannel(oldChannelID);
    event->newChannel             = server->getChannel(newChannelID);
    event->visibility             = static_cast<Visibility>(visibility);
    event->kicker                 = server->getClient(kickerID);
    event->kickerName             = utils::to_string(kickerName);
    event->kickerUniqueIdentifier = utils::to_string(kickerUniqueIdentifier);
    event->kickMessage            = utils::to_string(kickMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientIDsEventWrapper(uint64 serverId, const char* uniqueClientIdentifier, uint16 clientID, const char* clientName)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientIDsReceivedEvent;
    event->client                 = server->getClient(clientID);
    event->clientName             = utils::to_string(clientName);
    event->uniqueClientIdentifier = utils::to_string(uniqueClientIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientIDsFinishedEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientIDsFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerEditedEventWrapper(uint64 serverId, uint16 editerID, const char* editerName, const char* editerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerEditedEvent;
    event->editer                 = server->getClient(editerID);
    event->editerName             = utils::to_string(editerName);
    event->editerUniqueIdentifier = utils::to_string(editerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerUpdatedEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerUpdatedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerErrorEventWrapper(uint64 serverId, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerErrorEvent;
    event->error        = static_cast<ReturnCode>(error);
    event->returnCode   = utils::to_string(returnCode);
    event->errorMessage = utils::to_string(errorMessage);
    event->extraMessage = utils::to_string(extraMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerStopEventWrapper(uint64 serverId, const char* shutdownMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerStopEvent;
    event->shutdownMessage = utils::to_string(shutdownMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onTextMessageEventWrapper(uint64 serverId, uint16 targetMode, uint16 toID, uint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message)
{
    auto server = Library::getServer(serverId);

    auto event = new TextMessageEvent;
    event->from       = server->getClient(fromID);
    event->targetMode = static_cast<TargetMode>(targetMode);
    switch (event->targetMode) {
    case TargetMode::Client:
        event->to = server->getClient(toID);
        break;
    case TargetMode::Channel:
    case TargetMode::Server:
    default:
        event->to = Q_NULLPTR;
        break;
    }
    event->message              = utils::to_string(message);
    event->fromName             = utils::to_string(fromName);
    event->fromUniqueIdentifier = utils::to_string(fromUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onTalkStatusChangeEventWrapper(uint64 serverId, int status, int isReceivedWhisper, uint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new TalkStatusChangeEvent;
    event->client            = server->getClient(clientID);
    event->status            = static_cast<TalkStatus>(status);
    event->isReceivedWhisper = isReceivedWhisper != 0;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onIgnoredWhisperEventWrapper(uint64 serverId, uint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new WhisperIgnoredEvent;
    event->client = server->getClient(clientID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onConnectionInfoEventWrapper(uint64 serverId, uint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new ConnectionInfoEvent;
    event->client = server->getClient(clientID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerConnectionInfoEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerConnectionInfoEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelSubscribeEventWrapper(uint64 serverId, uint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelSubscribedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelSubscribeFinishedEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelSubscribesFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelUnsubscribeEventWrapper(uint64 serverId, uint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUnsubscribedEvent;  
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelUnsubscribeFinishedEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUnsubscribesFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelDescriptionUpdateEventWrapper(uint64 serverId, uint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelDescriptionUpdatedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelPasswordChangedEventWrapper(uint64 serverId, uint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelPasswordChangedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onPlaybackShutdownCompleteEventWrapper(uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new PlaybackShutdownCompletedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onSoundDeviceListChangedEventWrapper(const char* modeID, int playOrCap)
{
    auto event = new SoundDeviceListChangedEvent;
    event->modeID    = utils::to_string(modeID);
    event->playOrCap = playOrCap != 0;
    QCoreApplication::postEvent(Library::instance(), event);
}

void EventManager::onUserLoggingMessageEventWrapper(const char* logmessage, int logLevel, const char* logChannel, uint64 logID, const char* logTime, const char* completeLogString)
{
    auto server = Library::getServer(logID);

    auto event = new UserLoggingMessageEvent;
    event->logLevel          = static_cast<LogLevel>(logLevel);
    event->logmessage        = utils::to_string(logmessage);
    event->logChannel        = utils::to_string(logChannel);
    event->logTime           = utils::to_string(logTime);
    event->completeLogString = utils::to_string(completeLogString);
    QCoreApplication::postEvent(Library::instance(), event);
}

void EventManager::onFileTransferStatusEventWrapper(uint16 transferID, uint status, const char* statusMessage, uint64 remotefileSize, uint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new FileTransferStatusReceivedEvent;
    event->transfer       = server->getTransfer(transferID);
    event->status         = static_cast<ReturnCode>(status);
    event->statusMessage  = utils::to_string(statusMessage);
    event->remotefileSize = remotefileSize;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileListEventWrapper(uint64 serverId, uint64 channelID, const char* path, const char* name, uint64 size, uint64 datetime, int type, uint64 incompletesize, const char* returnCode)
{
    auto server = Library::getServer(serverId);

    auto event = new FileListReceivedEvent;
    event->channel        = server->getChannel(channelID);
    event->path           = utils::to_string(path);
    event->name           = utils::to_string(name);
    event->size           = size;
    event->incompletesize = incompletesize;
    event->type           = static_cast<FileListType>(type);
    event->datetime       = utils::to_date_time(datetime);
    event->returnCode     = utils::to_string(returnCode);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileListFinishedEventWrapper(uint64 serverId, uint64 channelID, const char* path)
{
    auto server = Library::getServer(serverId);

    auto event = new FileListFinishedEvent;
    event->channel = server->getChannel(channelID);
    event->path    = utils::to_string(path);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileInfoEventWrapper(uint64 serverId, uint64 channelID, const char* name, uint64 size, uint64 datetime)
{
    auto server = Library::getServer(serverId);

    auto event = new FileInfoReceivedEvent;
    event->channel  = server->getChannel(channelID);
    event->name     = utils::to_string(name);
    event->size     = size;
    event->datetime = utils::to_date_time(datetime);
    QCoreApplication::postEvent(server, event);
}


void EventManager::onEditPlaybackVoiceDataEventWrapper(uint64 serverId, uint16 clientID, short* samples, int sampleCount, int channels)
{
    auto handler = Library::editPlaybackVoiceDataHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client = server->getClient(clientID);
    auto vector = utils::make_vector<short>(samples, sampleCount);
    auto result = handler(client, vector, channels);
    utils::copy_vector(result, samples);
}

void EventManager::onEditPostProcessVoiceDataEventWrapper(
    uint64 serverId, uint16 clientID, 
    short* samples, int sampleCount, 
    int channels, const uint* channelSpeakers, 
    uint* channelFillMask)
{
    auto handler = Library::editPostProcessVoiceDataHandler();
    if (!handler)
        return;

    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client          = server->getClient(clientID);
    auto vector_samples  = utils::make_vector<short>(samples, sampleCount);
    auto vector_speakers = utils::make_vector<Speakers>(channelSpeakers, channels);
    auto result = handler(client, vector_samples, vector_speakers, (Speakers*)channelFillMask);
    if (0 != *channelFillMask)
        utils::copy_vector(result, samples);
}

void EventManager::onEditMixedPlaybackVoiceDataEventWrapper(
    uint64 serverId, short* samples, int sampleCount, int channels, 
    const uint* channelSpeakers, uint* channelFillMask)
{
    auto handler = Library::editMixedPlaybackVoiceDataHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server          = Library::getServer(serverId);
    auto vector_samples  = utils::make_vector<short>(samples, sampleCount * channels);
    auto vector_speakers = utils::make_vector<Speakers>(channelSpeakers, channels);
    auto result = handler(server, vector_samples, vector_speakers, (Speakers*)channelFillMask);
    if (0 != *channelFillMask)
        utils::copy_vector(result, samples);
}

void EventManager::onEditCapturedVoiceDataEventWrapper(uint64 serverId, short* samples, int sampleCount, int channels, int* bytes)
{
    auto handler = Library::editCapturedVoiceDataHandler();
    if (!handler)
        return;

    // TODO: handler call
    bool edited = (*bytes & 1) == 1;
    bool cancel = (*bytes & 2) == 0;
    auto server = Library::getServer(serverId);
    auto vector_samples = utils::make_vector<short>(samples, sampleCount);
    auto result = handler(server, vector_samples, channels, edited, cancel);
    if (edited && cancel == false)
        utils::copy_vector(result, samples);
    *bytes = (edited ? 1 : 0) | (cancel ? 0 : 2);
}

void EventManager::onCustom3dRolloffCalculationClientEventWrapper(uint64 serverId, uint16 clientID, float distance, float* volume)
{
    auto handler = Library::custom3dRolloffCalculationClientHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client = server->getClient(clientID);
    handler(client, distance, volume);
}

void EventManager::onCustom3dRolloffCalculationWaveEventWrapper(uint64 serverId, uint64 waveHandle, float distance, float* volume)
{
    auto handler = Library::custom3dRolloffCalculationWaveHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto wave   = server->getWaveHandle(waveHandle);
    handler(wave, distance, volume);
}

void EventManager::onProvisioningSlotRequestResultEventWrapper(
    uint error, uint64 requestHandle, const char* connectionKey)
{
    auto key = utils::to_string(connectionKey);
}

void EventManager::onCheckServerUniqueIdentifierEventWrapper(uint64 serverId, const char* serverUniqueIdentifier, int* cancelConnect)
{
    auto handler = Library::checkUniqueIdentifierHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto uniqueIdentifier = utils::to_string(serverUniqueIdentifier);
    auto result = handler(server, uniqueIdentifier);
    *cancelConnect = result;
}


#define CUSTOM_CRYPT_KEY 123

void EventManager::onCustomPacketEncryptEventWrapper(char** dataToSend, uint* sizeOfData)
{
    auto handler = Library::customPacketEncryptHandler();
    if (!handler) {
#if defined(CUSTOM_CRYPT_KEY)
        for (uint i = 0; i < *sizeOfData; ++i) {
            (*dataToSend)[i] ^= CUSTOM_CRYPT_KEY;
        }
#endif
    } else {
        // TODO: handler call
    }
}

void EventManager::onCustomPacketDecryptEventWrapper(char** dataReceived, uint* dataReceivedSize)
{
    auto handler = Library::customPacketDecryptHandler();
    if (!handler) {
#if defined(CUSTOM_CRYPT_KEY)
        for (uint i = 0; i < *dataReceivedSize; ++i) {
            (*dataReceived)[i] ^= CUSTOM_CRYPT_KEY;
        }
#endif
    } else {
        // TODO: handler call
    }
   
}

void EventManager::onClientPasswordEncryptEventWrapper(uint64 serverId, const char* plaintext, char* encryptedText, int encryptedTextByteSize)
{
    auto handler = Library::clientPasswordEncryptHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto text   = utils::to_byte(plaintext);
    auto result = handler(server, text, encryptedTextByteSize - 1);
    ::memcpy(encryptedText, result.data(), result.size());
}

void __init_event_manager()
{
    (void) new EventManager(qApp);
}
Q_COREAPP_STARTUP_FUNCTION(__init_event_manager)

} // namespace TeamSpeakSdk

