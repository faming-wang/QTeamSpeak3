#include "object.h"

namespace QTeamSpeak {

Object::Object(QObject* parent)
    : QObject(parent)
{

}

Object::~Object()
{

}

void Object::customEvent(QEvent* event)
{
    if (event->type() == Event::type) {
        teamSpeakEvent(static_cast<Event*>(event));
    }
}

void Object::teamSpeakEvent(Event* event)
{
    switch (event->eventType) {
    case EventType::ConnectStatusChanged:
        connectStatusChangedEvent(static_cast<ConnectStatusChangedEvent*>(event));
        break;
    case EventType::ServerProtocolVersion:
        serverProtocolVersionEvent(static_cast<ServerProtocolVersionEvent*>(event));
        break;
    case EventType::NewChannel:
        newChannelEvent(static_cast<NewChannelEvent*>(event));
        break;
    case EventType::NewChannelCreated:
        newChannelCreatedEvent(static_cast<NewChannelCreatedEvent*>(event));
        break;
    case EventType::ChannelDeleted:
        channelDeletedEvent(static_cast<ChannelDeletedEvent*>(event));
        break;
    case EventType::ChannelMoved:
        channelMovedEvent(static_cast<ChannelMovedEvent*>(event));
        break;
    case EventType::ChannelUpdated:
        channelUpdatedEvent(static_cast<ChannelUpdatedEvent*>(event));
        break;
    case EventType::ChannelEdited:
        channelEditedEvent(static_cast<ChannelEditedEvent*>(event));
        break;
    case EventType::ClientUpdated:
        clientUpdatedEvent(static_cast<ClientUpdatedEvent*>(event));
        break;
    case EventType::ClientMoved:
        clientMovedEvent(static_cast<ClientMovedEvent*>(event));
        break;
    case EventType::SubscriptionClientMoved:
        subscriptionClientMovedEvent(static_cast<SubscriptionClientMovedEvent*>(event));
        break;
    case EventType::ClientMoveTimeout:
        clientMoveTimeoutEvent(static_cast<ClientMoveTimeoutEvent*>(event));
        break;
    case EventType::ClientMoverMoved:
        clientMoverMovedEvent(static_cast<ClientMoverMovedEvent*>(event));
        break;
    case EventType::ClientKickFromChannel:
        clientKickFromChannelEvent(static_cast<ClientKickFromChannelEvent*>(event));
        break;
    case EventType::ClientKickFromServer:
        clientKickFromServerEvent(static_cast<ClientKickFromServerEvent*>(event));
        break;
    case EventType::ClientIDsReceived:
        clientIDsReceivedEvent(static_cast<ClientIDsReceivedEvent*>(event));
        break;
    case EventType::ClientIDsFinished:
        clientIDsFinishedEvent(static_cast<ClientIDsFinishedEvent*>(event));
        break;
    case EventType::ServerEdited:
        serverEditedEvent(static_cast<ServerEditedEvent*>(event));
        break;
    case EventType::ServerUpdated:
        serverUpdatedEvent(static_cast<ServerUpdatedEvent*>(event));
        break;
    case EventType::ServerError:
        connectStatusChangedEvent(static_cast<ConnectStatusChangedEvent*>(event));
        break;
    case EventType::ServerStop:
        connectStatusChangedEvent(static_cast<ConnectStatusChangedEvent*>(event));
        break;
    case EventType::TextMessage:
        textMessageEvent(static_cast<TextMessageEvent*>(event));
        break;
    case EventType::TalkStatusChange:
        talkStatusChangeEvent(static_cast<TalkStatusChangeEvent*>(event));
        break;
    case EventType::WhisperIgnored:
        whisperIgnoredEvent(static_cast<WhisperIgnoredEvent*>(event));
        break;
    case EventType::ConnectionInfo:
        connectionInfoEvent(static_cast<ConnectionInfoEvent*>(event));
        break;
    case EventType::ServerConnectionInfo:
        serverConnectionInfoEvent(static_cast<ServerConnectionInfoEvent*>(event));
        break;
    case EventType::ChannelSubscribed:
        channelSubscribedEvent(static_cast<ChannelSubscribedEvent*>(event));
        break;
    case EventType::ChannelSubscribesFinished:
        channelSubscribesFinishedEvent(static_cast<ChannelSubscribesFinishedEvent*>(event));
        break;
    case EventType::ChannelUnsubscribed:
        channelUnsubscribedEvent(static_cast<ChannelUnsubscribedEvent*>(event));
        break;
    case EventType::ChannelUnsubscribesFinished:
        channelUnsubscribesFinishedEvent(static_cast<ChannelUnsubscribesFinishedEvent*>(event));
        break;
    case EventType::ChannelDescriptionUpdated:
        channelDescriptionUpdatedEvent(static_cast<ChannelDescriptionUpdatedEvent*>(event));
        break;
    case EventType::ChannelPasswordChanged:
        channelPasswordChangedEvent(static_cast<ChannelPasswordChangedEvent*>(event));
        break;
    case EventType::PlaybackShutdownCompleted:
        playbackShutdownCompletedEvent(static_cast<PlaybackShutdownCompletedEvent*>(event));
        break;
    case EventType::SoundDeviceListChanged:
        soundDeviceListChangedEvent(static_cast<SoundDeviceListChangedEvent*>(event));
        break;
    case EventType::UserLoggingMessage:
        userLoggingMessageEvent(static_cast<UserLoggingMessageEvent*>(event));
        break;
    case EventType::ProvisioningSlotRequestResult:
        provisioningSlotRequestResultEvent(static_cast<ProvisioningSlotRequestResultEvent*>(event));
        break;
    case EventType::FileTransferStatusReceived:
        fileTransferStatusReceivedEvent(static_cast<FileTransferStatusReceivedEvent*>(event));
        break;
    case EventType::FileListReceived:
        fileListReceivedEvent(static_cast<FileListReceivedEvent*>(event));
        break;
    case EventType::FileListFinished:
        fileListFinishedEvent(static_cast<FileListFinishedEvent*>(event));
        break;
    case EventType::FileInfoReceived:
        fileInfoReceivedEvent(static_cast<FileInfoReceivedEvent*>(event));
        break;
    default:
        break;
    }
}

void Object::connectStatusChangedEvent(ConnectStatusChangedEvent* event) { }
void Object::serverProtocolVersionEvent(ServerProtocolVersionEvent* event){ }
void Object::newChannelEvent(NewChannelEvent* event){ }
void Object::newChannelCreatedEvent(NewChannelCreatedEvent* event){ }
void Object::channelDeletedEvent(ChannelDeletedEvent* event){ }
void Object::channelMovedEvent(ChannelMovedEvent* event){ }
void Object::channelUpdatedEvent(ChannelUpdatedEvent* event){ }
void Object::channelEditedEvent(ChannelEditedEvent* event){ }
void Object::clientUpdatedEvent(ClientUpdatedEvent* event){ }
void Object::clientMovedEvent(ClientMovedEvent* event){ }
void Object::subscriptionClientMovedEvent(SubscriptionClientMovedEvent* event){ }
void Object::clientMoveTimeoutEvent(ClientMoveTimeoutEvent* event){ }
void Object::clientMoverMovedEvent(ClientMoverMovedEvent* event){ }
void Object::clientKickFromChannelEvent(ClientKickFromChannelEvent* event){ }
void Object::clientKickFromServerEvent(ClientKickFromServerEvent* event){ }
void Object::clientIDsReceivedEvent(ClientIDsReceivedEvent* event){ }
void Object::clientIDsFinishedEvent(ClientIDsFinishedEvent* event){ }
void Object::serverEditedEvent(ServerEditedEvent* event){ }
void Object::serverUpdatedEvent(ServerUpdatedEvent* event){ }
void Object::serverErrorEvent(ServerErrorEvent* event){ }
void Object::serverStopEvent(ServerStopEvent* event){ }
void Object::textMessageEvent(TextMessageEvent* event){ }
void Object::talkStatusChangeEvent(TalkStatusChangeEvent* event){ }
void Object::whisperIgnoredEvent(WhisperIgnoredEvent* event){ }
void Object::connectionInfoEvent(ConnectionInfoEvent* event){ }
void Object::serverConnectionInfoEvent(ServerConnectionInfoEvent* event){ }
void Object::channelSubscribedEvent(ChannelSubscribedEvent* event){ }
void Object::channelSubscribesFinishedEvent(ChannelSubscribesFinishedEvent* event){ }
void Object::channelUnsubscribedEvent(ChannelUnsubscribedEvent* event){ }
void Object::channelUnsubscribesFinishedEvent(ChannelUnsubscribesFinishedEvent* event){ }
void Object::channelDescriptionUpdatedEvent(ChannelDescriptionUpdatedEvent* event){ }
void Object::channelPasswordChangedEvent(ChannelPasswordChangedEvent* event){ }
void Object::playbackShutdownCompletedEvent(PlaybackShutdownCompletedEvent* event){ }
void Object::soundDeviceListChangedEvent(SoundDeviceListChangedEvent* event){ }
void Object::userLoggingMessageEvent(UserLoggingMessageEvent* event){ }
void Object::provisioningSlotRequestResultEvent(ProvisioningSlotRequestResultEvent* event){ }
void Object::fileTransferStatusReceivedEvent(FileTransferStatusReceivedEvent* event){ }
void Object::fileListReceivedEvent(FileListReceivedEvent* event){ }
void Object::fileListFinishedEvent(FileListFinishedEvent* event){ }
void Object::fileInfoReceivedEvent(FileInfoReceivedEvent* event){ }

} // namespace QTeamSpeak
