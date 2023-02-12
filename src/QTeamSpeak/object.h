#pragma once

#include <QTeamSpeak/event.h>

namespace QTeamSpeak {

class Object : public QObject
{
    Q_OBJECT

public:
    Object(QObject* parent = nullptr);
    ~Object();

protected:
    void customEvent(QEvent* event) override;
    virtual void teamSpeakEvent(Event* event);
    virtual void connectStatusChangedEvent(ConnectStatusChangedEvent* event);
    virtual void serverProtocolVersionEvent(ServerProtocolVersionEvent* event);
    virtual void newChannelEvent(NewChannelEvent* event);
    virtual void newChannelCreatedEvent(NewChannelCreatedEvent* event);
    virtual void channelDeletedEvent(ChannelDeletedEvent* event);
    virtual void channelMovedEvent(ChannelMovedEvent* event);
    virtual void channelUpdatedEvent(ChannelUpdatedEvent* event);
    virtual void channelEditedEvent(ChannelEditedEvent* event);
    virtual void clientUpdatedEvent(ClientUpdatedEvent* event);
    virtual void clientMovedEvent(ClientMovedEvent* event);
    virtual void subscriptionClientMovedEvent(SubscriptionClientMovedEvent* event);
    virtual void clientMoveTimeoutEvent(ClientMoveTimeoutEvent* event);
    virtual void clientMoverMovedEvent(ClientMoverMovedEvent* event);
    virtual void clientKickFromChannelEvent(ClientKickFromChannelEvent* event);
    virtual void clientKickFromServerEvent(ClientKickFromServerEvent* event);
    virtual void clientIDsReceivedEvent(ClientIDsReceivedEvent* event);
    virtual void clientIDsFinishedEvent(ClientIDsFinishedEvent* event);
    virtual void serverEditedEvent(ServerEditedEvent* event);
    virtual void serverUpdatedEvent(ServerUpdatedEvent* event);
    virtual void serverErrorEvent(ServerErrorEvent* event);
    virtual void serverStopEvent(ServerStopEvent* event);
    virtual void textMessageEvent(TextMessageEvent* event);
    virtual void talkStatusChangeEvent(TalkStatusChangeEvent* event);
    virtual void whisperIgnoredEvent(WhisperIgnoredEvent* event);
    virtual void connectionInfoEvent(ConnectionInfoEvent* event);
    virtual void serverConnectionInfoEvent(ServerConnectionInfoEvent* event);
    virtual void channelSubscribedEvent(ChannelSubscribedEvent* event);
    virtual void channelSubscribesFinishedEvent(ChannelSubscribesFinishedEvent* event);
    virtual void channelUnsubscribedEvent(ChannelUnsubscribedEvent* event);
    virtual void channelUnsubscribesFinishedEvent(ChannelUnsubscribesFinishedEvent* event);
    virtual void channelDescriptionUpdatedEvent(ChannelDescriptionUpdatedEvent* event);
    virtual void channelPasswordChangedEvent(ChannelPasswordChangedEvent* event);
    virtual void playbackShutdownCompletedEvent(PlaybackShutdownCompletedEvent* event);
    virtual void soundDeviceListChangedEvent(SoundDeviceListChangedEvent* event);
    virtual void userLoggingMessageEvent(UserLoggingMessageEvent* event);
    virtual void provisioningSlotRequestResultEvent(ProvisioningSlotRequestResultEvent* event);
    virtual void fileTransferStatusReceivedEvent(FileTransferStatusReceivedEvent* event);
    virtual void fileListReceivedEvent(FileListReceivedEvent* event);
    virtual void fileListFinishedEvent(FileListFinishedEvent* event);
    virtual void fileInfoReceivedEvent(FileInfoReceivedEvent* event);
};

} // namespace QTeamSpeak


