#pragma once

namespace TeamSpeakSdk {

template<ushort offset>
struct TEAMSPEAKSDK_EXPORT Event : public QEvent
{
    enum { EventId = QEvent::User + 3000 + offset};
    Event() : QEvent(static_cast<Type>(EventId)){}
};

struct TEAMSPEAKSDK_EXPORT ConnectStatusChangedEvent : public Event<1>
{
    ConnectStatus newStatus;
    ReturnCode errorNumber;
};

struct TEAMSPEAKSDK_EXPORT ServerProtocolVersionEvent : public Event<2>
{
    int protocolVersion;
};

struct TEAMSPEAKSDK_EXPORT NewChannelEvent : public Event<3>
{
    Channel* channel;
    Channel* channelParent;
};

struct TEAMSPEAKSDK_EXPORT NewChannelCreatedEvent : public Event<4>
{
    Channel* channel;
    Channel* channelParent;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ChannelDeletedEvent : public Event<5>
{
    Channel* channel;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ChannelMovedEvent : public Event<6>
{
    Channel* channel;
    Channel* newChannelParent;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ChannelUpdatedEvent : public Event<7>
{
    Channel* channel;
};

struct TEAMSPEAKSDK_EXPORT ChannelEditedEvent : public Event<8>
{
    Channel* channel;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ClientUpdatedEvent : public Event<9>
{
    Client* client;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ClientMovedEvent : public Event<10>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
    QString moveMessage;
};

struct TEAMSPEAKSDK_EXPORT SubscriptionClientMovedEvent : public Event<11>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
};

struct TEAMSPEAKSDK_EXPORT ClientMoveTimeoutEvent : public Event<12>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
    QString timeoutMessage;
};

struct TEAMSPEAKSDK_EXPORT ClientMoverMovedEvent : public Event<13>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;

    Client* mover;
    QString moverName;
    QString moverUniqueIdentifier;
    QString moveMessage;
};

struct TEAMSPEAKSDK_EXPORT ClientKickFromChannelEvent : public Event<14>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;

    Client* kicker;
    QString kickerName;
    QString kickerUniqueIdentifier;
    QString kickMessage;
};

struct TEAMSPEAKSDK_EXPORT ClientKickFromServerEvent : public Event<15>
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;

    Client* kicker;
    QString kickerName;
    QString kickerUniqueIdentifier;
    QString kickMessage;
};

struct TEAMSPEAKSDK_EXPORT ClientIDsReceivedEvent : public Event<16>
{
    Client* client;
    QString clientName;
    QString uniqueClientIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ClientIDsFinishedEvent : public Event<17>
{
};

struct TEAMSPEAKSDK_EXPORT ServerEditedEvent : public Event<18>
{
    Client* editer;
    QString editerName;
    QString editerUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT ServerUpdatedEvent : public Event<19>
{
    Connection* connection;
};

struct TEAMSPEAKSDK_EXPORT ServerErrorEvent : public Event<20>
{
    ReturnCode error;
    QString returnCode;
    QString errorMessage;
    QString extraMessage;

};

struct TEAMSPEAKSDK_EXPORT ServerStopEvent : public Event<21>
{
    QString shutdownMessage;
};

struct TEAMSPEAKSDK_EXPORT TextMessageEvent : public Event<22>
{
    TargetMode targetMode;
    Client* from;
    Client* to;
    QString message;
    QString fromName;
    QString fromUniqueIdentifier;
};

struct TEAMSPEAKSDK_EXPORT TalkStatusChangeEvent : public Event<23>
{
    Client* client;
    TalkStatus status;
    bool isReceivedWhisper;
};

struct TEAMSPEAKSDK_EXPORT WhisperIgnoredEvent : public Event<24>
{
    Client* client;
};

struct TEAMSPEAKSDK_EXPORT ConnectionInfoEvent : public Event<25>
{
    Client* client;
};

struct TEAMSPEAKSDK_EXPORT ServerConnectionInfoEvent : public Event<26>
{
    Connection* connection;
};

struct TEAMSPEAKSDK_EXPORT ChannelSubscribedEvent : public Event<27>
{
    Channel* channel;
};

struct TEAMSPEAKSDK_EXPORT ChannelSubscribesFinishedEvent : public Event<28>
{
};

struct TEAMSPEAKSDK_EXPORT ChannelUnsubscribedEvent : public Event<29>
{
    Channel* channel;
};

struct TEAMSPEAKSDK_EXPORT ChannelUnsubscribesFinishedEvent : public Event<30>
{
};

struct TEAMSPEAKSDK_EXPORT ChannelDescriptionUpdatedEvent : public Event<31>
{
    Channel* channel;
};

struct TEAMSPEAKSDK_EXPORT ChannelPasswordChangedEvent : public Event<32>
{
    Channel* channel;
};

struct TEAMSPEAKSDK_EXPORT PlaybackShutdownCompletedEvent : public Event<33>
{
};

struct TEAMSPEAKSDK_EXPORT SoundDeviceListChangedEvent : public Event<34>
{
    QString modeID;
    bool playOrCap;
};

struct TEAMSPEAKSDK_EXPORT UserLoggingMessageEvent : public Event<35>
{
    LogLevel logLevel;
    QString logmessage;
    QString logChannel;
    QString logTime;
    QString completeLogString;
};

struct TEAMSPEAKSDK_EXPORT ProvisioningSlotRequestResultEvent : public Event<36>
{

};

struct TEAMSPEAKSDK_EXPORT FileTransferStatusReceivedEvent : public Event<37>
{
    FileTransfer* transfer;
    ReturnCode status;
    QString statusMessage;
    uint64 remotefileSize;
};

struct TEAMSPEAKSDK_EXPORT FileListReceivedEvent : public Event<38>
{
    Channel* channel;
    QString path;
    QString name;
    uint64 size;
    uint64 incompletesize;
    FileListType type;
    QDateTime datetime;
    QString returnCode;

};

struct TEAMSPEAKSDK_EXPORT FileListFinishedEvent : public Event<39>
{
    Channel* channel;
    QString path;
};

struct TEAMSPEAKSDK_EXPORT FileInfoReceivedEvent : public Event<40>
{
    Channel* channel;
    QString name;
    uint64 size;
    QDateTime datetime;
};

} // namespace TeamSpeakSdk

