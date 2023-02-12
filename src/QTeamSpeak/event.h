#pragma once

#include <QTeamSpeak/namespace.h>

namespace QTeamSpeak {

enum class EventType
{
    ConnectStatusChanged,
    ServerProtocolVersion,

    NewChannel,
    NewChannelCreated,
    ChannelDeleted,
    ChannelMoved,
    ChannelUpdated,
    ChannelEdited,
    ClientUpdated,

    ClientMoved,
    SubscriptionClientMoved,
    ClientMoveTimeout,
    ClientMoverMoved,
    ClientKickFromChannel,
    ClientKickFromServer,
    ClientIDsReceived,
    ClientIDsFinished,

    ServerEdited,
    ServerUpdated,
    ServerError,
    ServerStop,
    TextMessage,
    TalkStatusChange,
    WhisperIgnored,
    ConnectionInfo,
    ServerConnectionInfo,

    ChannelSubscribed,
    ChannelSubscribesFinished,
    ChannelUnsubscribed,
    ChannelUnsubscribesFinished,
    ChannelDescriptionUpdated,
    ChannelPasswordChanged,

    PlaybackShutdownCompleted,
    SoundDeviceListChanged,
    UserLoggingMessage,
    ProvisioningSlotRequestResult,

    FileTransferStatusReceived,
    FileListReceived,
    FileListFinished,
    FileInfoReceived,
};

struct Event : public QEvent
{
    enum { type = QEvent::User + 100 };

    Event() : QEvent(QEvent::Type(type)) { }

    EventType eventType;
};

struct ConnectStatusChangedEvent : public Event
{
    ConnectStatus newStatus;
    ReturnCode errorNumber;
};

struct ServerProtocolVersionEvent : public Event
{
    int protocolVersion;
};

struct NewChannelEvent : public Event
{
    Channel* channel;
    Channel* channelParent;
};

struct NewChannelCreatedEvent : public Event
{
    Channel* channel;
    Channel* channelParent;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct ChannelDeletedEvent : public Event
{
    Channel* channel;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct ChannelMovedEvent : public Event
{
    Channel* channel;
    Channel* newChannelParent;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct ChannelUpdatedEvent : public Event
{
    Channel* channel;
};

struct ChannelEditedEvent : public Event
{
    Channel* channel;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct ClientUpdatedEvent : public Event
{
    Client* client;
    Client* invoker;
    QString invokerName;
    QString invokerUniqueIdentifier;
};

struct ClientMovedEvent : public Event
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
    QString moveMessage;
};

struct SubscriptionClientMovedEvent : public Event
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
};

struct ClientMoveTimeoutEvent : public Event
{
    Client* client;
    Channel* oldChannel;
    Channel* newChannel;
    Visibility visibility;
    QString timeoutMessage;
};

struct ClientMoverMovedEvent : public Event
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

struct ClientKickFromChannelEvent : public Event
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

struct ClientKickFromServerEvent : public Event
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

struct ClientIDsReceivedEvent : public Event
{
    Client* client;
    QString clientName;
    QString uniqueClientIdentifier;
};

struct ClientIDsFinishedEvent : public Event
{
};

struct ServerEditedEvent : public Event
{
    Client* editer;
    QString editerName;
    QString editerUniqueIdentifier;
};

struct ServerUpdatedEvent : public Event
{
    Connection* connection;
};

struct ServerErrorEvent : public Event
{
    ReturnCode error;
    QString returnCode;
    QString errorMessage;
    QString extraMessage;
};

struct ServerStopEvent : public Event
{
    QString shutdownMessage;
};

struct TextMessageEvent : public Event
{
    TargetMode targetMode;
    Client* from;
    Client* to;
    QString message;
    QString fromName;
    QString fromUniqueIdentifier;
};

struct TalkStatusChangeEvent : public Event
{
    Client* client;
    TalkStatus status;
    bool isReceivedWhisper;
};

struct WhisperIgnoredEvent : public Event
{
    Client* client;
};

struct ConnectionInfoEvent : public Event
{
    Client* client;
};

struct ServerConnectionInfoEvent : public Event
{
    Connection* connection;
};

struct ChannelSubscribedEvent : public Event
{
    Channel* channel;
};

struct ChannelSubscribesFinishedEvent : public Event
{
};

struct ChannelUnsubscribedEvent : public Event
{
    Channel* channel;
};

struct ChannelUnsubscribesFinishedEvent : public Event
{
};

struct ChannelDescriptionUpdatedEvent : public Event
{
    Channel* channel;
};

struct ChannelPasswordChangedEvent : public Event
{
    Channel* channel;
};

struct PlaybackShutdownCompletedEvent : public Event
{
};

struct SoundDeviceListChangedEvent : public Event
{
    QString modeID;
    bool playOrCap;
};

struct UserLoggingMessageEvent : public Event
{
    LogLevel logLevel;
    QString logmessage;
    QString logChannel;
    QString logTime;
    QString completeLogString;
};

struct ProvisioningSlotRequestResultEvent : public Event
{

};

struct FileTransferStatusReceivedEvent : public Event
{
    FileTransfer* transfer;
    ReturnCode status;
    QString statusMessage;
    quint64 remotefileSize;
};

struct FileListReceivedEvent : public Event
{
    Channel* channel;
    QString path;
    QString name;
    quint64 size;
    quint64 incompletesize;
    FileListType type;
    QDateTime datetime;
    QString returnCode;

};

struct FileListFinishedEvent : public Event
{
    Channel* channel;
    QString path;
};

struct FileInfoReceivedEvent : public Event
{
    Channel* channel;
    QString name;
    quint64 size;
    QDateTime datetime;
};

} // namespace QTeamSpeak
