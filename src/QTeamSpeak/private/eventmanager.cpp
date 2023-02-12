#include "eventmanager_p.h"

#include "interfacemanager_p.h"

#include "event.h"
#include "exception.h"
#include "connection.h"

namespace QTeamSpeak {

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
};

static EventManager* m_instance = nullptr;
static EventManagerPrivate*   d = nullptr;

EventManager* EventManager::instance()
{
    return m_instance;
}

EventManager::~EventManager()
{
    m_instance = nullptr;
    delete d;d = nullptr;
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

void EventManager::onConnectStatusChangeEventWrapper(quint64 serverId, int newStatus, uint errorNumber)
{
    auto server  = Library::getServer(serverId);

    auto event = new ConnectStatusChangedEvent;
    event->newStatus   = static_cast<ConnectStatus>(newStatus);
    event->errorNumber = ReturnCode(errorNumber);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerProtocolVersionEventWrapper(quint64 serverId, int protocolVersion)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerProtocolVersionEvent;
    event->protocolVersion = protocolVersion;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onNewChannelEventWrapper(quint64 serverId, quint64 channelID, quint64 channelParentID)
{
    auto server = Library::getServer(serverId);

    auto event = new NewChannelEvent;
    event->channel       = server->getChannel(channelID);
    event->channelParent = server->getChannel(channelParentID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onNewChannelCreatedEventWrapper(quint64 serverId, quint64 channelID, quint64 channelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new NewChannelCreatedEvent;
    event->channel                 = server->getChannel(channelID);
    event->channelParent           = server->getChannel(channelParentID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = Utils::to_string(invokerName);
    event->invokerUniqueIdentifier = Utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onDelChannelEventWrapper(quint64 serverId, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelDeletedEvent;
    event->channel                 = server->getChannel(channelID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = Utils::to_string(invokerName);
    event->invokerUniqueIdentifier = Utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelMoveEventWrapper(quint64 serverId, quint64 channelID, quint64 newChannelParentID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelMovedEvent;
    event->channel                 = server->getChannel(channelID);
    event->newChannelParent        = server->getChannel(newChannelParentID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = Utils::to_string(invokerName);
    event->invokerUniqueIdentifier = Utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateChannelEventWrapper(quint64 serverId, quint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUpdatedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateChannelEditedEventWrapper(quint64 serverId, quint64 channelID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelEditedEvent;
    event->channel                 = server->getChannel(channelID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = Utils::to_string(invokerName);
    event->invokerUniqueIdentifier = Utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onUpdateClientEventWrapper(quint64 serverId, quint16 clientID, quint16 invokerID, const char* invokerName, const char* invokerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientUpdatedEvent;
    event->client                  = server->getClient(clientID);
    event->invoker                 = server->getClient(invokerID);
    event->invokerName             = Utils::to_string(invokerName);
    event->invokerUniqueIdentifier = Utils::to_string(invokerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* moveMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMovedEvent;
    event->client      = server->getClient(clientID);
    event->oldChannel  = server->getChannel(oldChannelID);
    event->newChannel  = server->getChannel(newChannelID);
    event->visibility  = static_cast<Visibility>(visibility);
    event->moveMessage = Utils::to_string(moveMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveSubscriptionEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility)
{
    auto server = Library::getServer(serverId);

    auto event = new SubscriptionClientMovedEvent;
    event->client     = server->getClient(clientID);
    event->oldChannel = server->getChannel(oldChannelID);
    event->newChannel = server->getChannel(newChannelID);
    event->visibility = static_cast<Visibility>(visibility);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveTimeoutEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, const char* timeoutMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMoveTimeoutEvent;
    event->client         = server->getClient(clientID);
    event->oldChannel     = server->getChannel(oldChannelID);
    event->newChannel     = server->getChannel(newChannelID);
    event->visibility     = static_cast<Visibility>(visibility);
    event->timeoutMessage = Utils::to_string(timeoutMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientMoveMovedEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 moverID, const char* moverName, const char* moverUniqueIdentifier, const char* moveMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientMoverMovedEvent;
    event->client                = server->getClient(clientID);
    event->oldChannel            = server->getChannel(oldChannelID);
    event->newChannel            = server->getChannel(newChannelID);
    event->visibility            = static_cast<Visibility>(visibility);
    event->mover                 = server->getClient(moverID);
    event->moverName             = Utils::to_string(moverName);
    event->moverUniqueIdentifier = Utils::to_string(moverUniqueIdentifier);
    event->moveMessage           = Utils::to_string(moveMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientKickFromChannelEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientKickFromChannelEvent;
    event->client                 = server->getClient(clientID);
    event->oldChannel             = server->getChannel(oldChannelID);
    event->newChannel             = server->getChannel(newChannelID);
    event->visibility             = static_cast<Visibility>(visibility);
    event->kicker                 = server->getClient(kickerID);
    event->kickerName             = Utils::to_string(kickerName);
    event->kickerUniqueIdentifier = Utils::to_string(kickerUniqueIdentifier);
    event->kickMessage            = Utils::to_string(kickMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientKickFromServerEventWrapper(quint64 serverId, quint16 clientID, quint64 oldChannelID, quint64 newChannelID, int visibility, quint16 kickerID, const char* kickerName, const char* kickerUniqueIdentifier, const char* kickMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientKickFromServerEvent;
    event->client                 = server->getClient(clientID);
    event->oldChannel             = server->getChannel(oldChannelID);
    event->newChannel             = server->getChannel(newChannelID);
    event->visibility             = static_cast<Visibility>(visibility);
    event->kicker                 = server->getClient(kickerID);
    event->kickerName             = Utils::to_string(kickerName);
    event->kickerUniqueIdentifier = Utils::to_string(kickerUniqueIdentifier);
    event->kickMessage            = Utils::to_string(kickMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientIDsEventWrapper(quint64 serverId, const char* uniqueClientIdentifier, quint16 clientID, const char* clientName)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientIDsReceivedEvent;
    event->client                 = server->getClient(clientID);
    event->clientName             = Utils::to_string(clientName);
    event->uniqueClientIdentifier = Utils::to_string(uniqueClientIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onClientIDsFinishedEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ClientIDsFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerEditedEventWrapper(quint64 serverId, quint16 editerID, const char* editerName, const char* editerUniqueIdentifier)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerEditedEvent;
    event->editer                 = server->getClient(editerID);
    event->editerName             = Utils::to_string(editerName);
    event->editerUniqueIdentifier = Utils::to_string(editerUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerUpdatedEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerUpdatedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerErrorEventWrapper(quint64 serverId, const char* errorMessage, uint error, const char* returnCode, const char* extraMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerErrorEvent;
    event->error        = static_cast<ReturnCode>(error);
    event->returnCode   = Utils::to_string(returnCode);
    event->errorMessage = Utils::to_string(errorMessage);
    event->extraMessage = Utils::to_string(extraMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerStopEventWrapper(quint64 serverId, const char* shutdownMessage)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerStopEvent;
    event->shutdownMessage = Utils::to_string(shutdownMessage);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onTextMessageEventWrapper(quint64 serverId, quint16 targetMode, quint16 toID, quint16 fromID, const char* fromName, const char* fromUniqueIdentifier, const char* message)
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
        event->to = nullptr;
        break;
    }
    event->message              = Utils::to_string(message);
    event->fromName             = Utils::to_string(fromName);
    event->fromUniqueIdentifier = Utils::to_string(fromUniqueIdentifier);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onTalkStatusChangeEventWrapper(quint64 serverId, int status, int isReceivedWhisper, quint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new TalkStatusChangeEvent;
    event->client            = server->getClient(clientID);
    event->status            = static_cast<TalkStatus>(status);
    event->isReceivedWhisper = isReceivedWhisper != 0;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onIgnoredWhisperEventWrapper(quint64 serverId, quint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new WhisperIgnoredEvent;
    event->client = server->getClient(clientID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onConnectionInfoEventWrapper(quint64 serverId, quint16 clientID)
{
    auto server = Library::getServer(serverId);

    auto event = new ConnectionInfoEvent;
    event->client = server->getClient(clientID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onServerConnectionInfoEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ServerConnectionInfoEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelSubscribeEventWrapper(quint64 serverId, quint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelSubscribedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelSubscribeFinishedEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelSubscribesFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelUnsubscribeEventWrapper(quint64 serverId, quint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUnsubscribedEvent;  
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelUnsubscribeFinishedEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelUnsubscribesFinishedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelDescriptionUpdateEventWrapper(quint64 serverId, quint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelDescriptionUpdatedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onChannelPasswordChangedEventWrapper(quint64 serverId, quint64 channelID)
{
    auto server = Library::getServer(serverId);

    auto event = new ChannelPasswordChangedEvent;
    event->channel = server->getChannel(channelID);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onPlaybackShutdownCompleteEventWrapper(quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new PlaybackShutdownCompletedEvent;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onSoundDeviceListChangedEventWrapper(const char* modeID, int playOrCap)
{
    auto event = new SoundDeviceListChangedEvent;
    event->modeID    = Utils::to_string(modeID);
    event->playOrCap = playOrCap != 0;
    QCoreApplication::postEvent(Library::instance(), event);
}

void EventManager::onUserLoggingMessageEventWrapper(const char* logmessage, int logLevel, const char* logChannel, quint64 logID, const char* logTime, const char* completeLogString)
{
    auto server = Library::getServer(logID);

    auto event = new UserLoggingMessageEvent;
    event->logLevel          = static_cast<LogLevel>(logLevel);
    event->logmessage        = Utils::to_string(logmessage);
    event->logChannel        = Utils::to_string(logChannel);
    event->logTime           = Utils::to_string(logTime);
    event->completeLogString = Utils::to_string(completeLogString);
    QCoreApplication::postEvent(Library::instance(), event);
}

void EventManager::onFileTransferStatusEventWrapper(quint16 transferID, uint status, const char* statusMessage, quint64 remotefileSize, quint64 serverId)
{
    auto server = Library::getServer(serverId);

    auto event = new FileTransferStatusReceivedEvent;
    event->transfer       = server->getTransfer(transferID);
    event->status         = static_cast<ReturnCode>(status);
    event->statusMessage  = Utils::to_string(statusMessage);
    event->remotefileSize = remotefileSize;
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileListEventWrapper(quint64 serverId, quint64 channelID, const char* path, const char* name, quint64 size, quint64 datetime, int type, quint64 incompletesize, const char* returnCode)
{
    auto server = Library::getServer(serverId);

    auto event = new FileListReceivedEvent;
    event->channel        = server->getChannel(channelID);
    event->path           = Utils::to_string(path);
    event->name           = Utils::to_string(name);
    event->size           = size;
    event->incompletesize = incompletesize;
    event->type           = static_cast<FileListType>(type);
    event->datetime       = Utils::to_date_time(datetime);
    event->returnCode     = Utils::to_string(returnCode);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileListFinishedEventWrapper(quint64 serverId, quint64 channelID, const char* path)
{
    auto server = Library::getServer(serverId);

    auto event = new FileListFinishedEvent;
    event->channel = server->getChannel(channelID);
    event->path    = Utils::to_string(path);
    QCoreApplication::postEvent(server, event);
}

void EventManager::onFileInfoEventWrapper(quint64 serverId, quint64 channelID, const char* name, quint64 size, quint64 datetime)
{
    auto server = Library::getServer(serverId);

    auto event = new FileInfoReceivedEvent;
    event->channel  = server->getChannel(channelID);
    event->name     = Utils::to_string(name);
    event->size     = size;
    event->datetime = Utils::to_date_time(datetime);
    QCoreApplication::postEvent(server, event);
}


void EventManager::onEditPlaybackVoiceDataEventWrapper(quint64 serverId, quint16 clientID, short* samples, int sampleCount, int channels)
{
    auto handler = Library::editPlaybackVoiceDataHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client = server->getClient(clientID);
    auto vector = Utils::make_vector<short>(samples, sampleCount);
    auto result = handler(client, vector, channels);
    Utils::copy_vector(result, samples);
}

void EventManager::onEditPostProcessVoiceDataEventWrapper(quint64 serverId, quint16 clientID, short* samples, int sampleCount, int channels, const uint* channelSpeakers, uint* channelFillMask)
{
    auto handler = Library::editPostProcessVoiceDataHandler();
    if (!handler)
        return;

    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client          = server->getClient(clientID);
    auto vector_samples  = Utils::make_vector<short>(samples, sampleCount);
    auto vector_speakers = Utils::make_vector<Speakers>(channelSpeakers, channels);
    auto result = handler(client, vector_samples, vector_speakers, (Speakers*)channelFillMask);
    if (0 != *channelFillMask)
        Utils::copy_vector(result, samples);
}

void EventManager::onEditMixedPlaybackVoiceDataEventWrapper(quint64 serverId, short* samples, int sampleCount, int channels, const uint* channelSpeakers, uint* channelFillMask)
{
    auto handler = Library::editMixedPlaybackVoiceDataHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server          = Library::getServer(serverId);
    auto vector_samples  = Utils::make_vector<short>(samples, sampleCount * channels);
    auto vector_speakers = Utils::make_vector<Speakers>(channelSpeakers, channels);
    auto result = handler(server, vector_samples, vector_speakers, (Speakers*)channelFillMask);
    if (0 != *channelFillMask)
        Utils::copy_vector(result, samples);
}

void EventManager::onEditCapturedVoiceDataEventWrapper(quint64 serverId, short* samples, int sampleCount, int channels, int* bytes)
{
    auto handler = Library::editCapturedVoiceDataHandler();
    if (!handler)
        return;

    // TODO: handler call
    bool edited = (*bytes & 1) == 1;
    bool cancel = (*bytes & 2) == 0;
    auto server = Library::getServer(serverId);
    auto vector_samples = Utils::make_vector<short>(samples, sampleCount);
    auto result = handler(server, vector_samples, channels, edited, cancel);
    if (edited && cancel == false)
        Utils::copy_vector(result, samples);
    *bytes = (edited ? 1 : 0) | (cancel ? 0 : 2);
}

void EventManager::onCustom3dRolloffCalculationClientEventWrapper(quint64 serverId, quint16 clientID, float distance, float* volume)
{
    auto handler = Library::custom3dRolloffCalculationClientHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto client = server->getClient(clientID);
    handler(client, distance, volume);
}

void EventManager::onCustom3dRolloffCalculationWaveEventWrapper(quint64 serverId, quint64 waveHandle, float distance, float* volume)
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
    uint error, quint64 requestHandle, const char* connectionKey)
{
    auto key = Utils::to_string(connectionKey);
}

void EventManager::onCheckServerUniqueIdentifierEventWrapper(quint64 serverId, const char* serverUniqueIdentifier, int* cancelConnect)
{
    auto handler = Library::checkUniqueIdentifierHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto uniqueIdentifier = Utils::to_string(serverUniqueIdentifier);
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

void EventManager::onClientPasswordEncryptEventWrapper(quint64 serverId, const char* plaintext, char* encryptedText, int encryptedTextByteSize)
{
    auto handler = Library::clientPasswordEncryptHandler();
    if (!handler)
        return;
    // TODO: handler call
    auto server = Library::getServer(serverId);
    auto text   = Utils::to_byte(plaintext);
    auto result = handler(server, text, encryptedTextByteSize - 1);
    ::memcpy(encryptedText, result.data(), result.size());
}

} // namespace QTeamSpeak

