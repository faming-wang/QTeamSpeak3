#pragma once

#include <QTeamSpeak/object.h>
#include <QTeamSpeak/client.h>
#include <QTeamSpeak/channel.h>
#include <QTeamSpeak/wavehandle.h>
#include <QTeamSpeak/sounddevice.h>
#include <QTeamSpeak/preprocessor.h>
#include <QTeamSpeak/filetransfer.h>
#include <QTeamSpeak/eventlistener.h>

namespace QTeamSpeak {

class Connection : public Object
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id)
    Q_PROPERTY(ConnectStatus status READ status)
    Q_PROPERTY(bool voiceRecording READ isVoiceRecording WRITE setVoiceRecording)
    Q_PROPERTY(std::chrono::seconds timeout READ timeout WRITE setTimeout)
    Q_PROPERTY(quint64 speedLimitUp READ speedLimitUp WRITE setSpeedLimitUp)
    Q_PROPERTY(quint64 speedLimitDown READ speedLimitDown WRITE setSpeedLimitDown)
    Q_PROPERTY(TestMode localTestMode READ localTestMode WRITE setLocalTestMode)
    Q_PROPERTY(float volumeModifier READ volumeModifier WRITE setVolumeModifier)
    Q_PROPERTY(float volumeFactorWave READ volumeFactorWave WRITE setVolumeFactorWave)

public:
    using ID = quint64;

    explicit Connection(QObject* parent = nullptr);
    explicit Connection(ID id, QObject* parent = nullptr);
    ~Connection();

public:
    ID id() const;
    Client* self() const;

    QList<Client*> allClients() const;
    QList<Channel*> allChannels() const;
    QList<Channel*> rootChannels() const;

    Client* getClient(Client::ID id) const;
    Channel* getChannel(Channel::ID id) const;
    WaveHandle* getWaveHandle(WaveHandle::ID id) const;
    FileTransfer* getTransfer(FileTransfer::ID id) const;

    QString serverIp() const;
    quint64 serverPort() const;
    ConnectStatus status() const;

    bool isVoiceRecording() const;
    void setVoiceRecording(bool value);

    std::chrono::seconds timeout() const;
    void setTimeout(std::chrono::seconds value);

    ISoundDevice* playbackDevice() const;
    ISoundDevice* captureDevice() const;

    quint64 speedLimitUp() const;
    void setSpeedLimitUp(quint64 value);

    quint64 speedLimitDown() const;
    void setSpeedLimitDown(quint64 value);

    TestMode localTestMode() const;
    void setLocalTestMode(TestMode value);

    float volumeModifier() const;
    void setVolumeModifier(float value);

    float volumeFactorWave() const;
    void setVolumeFactorWave(float value);

    void openPlaybackDevice(ISoundDevice* device = nullptr);
    void closePlaybackDevice();

    void openCaptureDevice(ISoundDevice* device = nullptr);
    void closeCaptureDevice();
    void activateCaptureDevice();

    void set3DListenerAttributes(Vector3D* position, Vector3D* forward, Vector3D* up);
    void set3DSettings(float distanceFactor, float rolloffScale);

    /// server info begin
    QString name() const;
    QString version() const;
    QString platform() const;
    QString uniqueIdentifier() const;
    QString welcomeMessage() const;

    int maxClients() const;
    int clientsOnline() const;
    int channelsOnline() const;

    QDateTime created() const;
    QDateTime uptime() const;

    CodecEncryptionMode codecEncryptionMode() const;
    /// server info end

public slots:
    void start(const ConnectInfo& option, const QStringList& defaultChannels = QStringList(), const QString& defaultChannelPassword = QString());
    void startWithChannelID(const ConnectInfo& option, Channel::ID defaultChannelID = 0, const QString& defaultChannelPassword = QString());
    void stop(const QString& quitMessage = QString());

    void playbackShutdown();

    void subscribeAll();
    void unsubscribeAll();

    void subscribe(const QList<Channel*>& channels);
    void unsubscribe(const QList<Channel*>& channels);

    void mute(const QList<Client*>& clients);
    void unmute(const QList<Client*>& clients);

    void createChannel(const CreateChannelOption& option);

    void sendTextMessage(const QString& message);
    void sendTextMessage(Client* client, const QString& message);
    void sendTextMessage(Channel* channel, const QString& message);

    void move(Client* client, const Channel* channel, const QString& password = QString());
    void move(Channel* channel, Channel* newParent, Channel* newChannelOrder);

    void allowWhispersFrom(const Client* client);
    void removeFromAllowedWhispersFrom(Client* client);
    void setWhisperList(const QList<Channel*>& channels, const QList<Client*>& clients);

    WaveHandle* playWaveFile(const QString& path, bool loop = false);
    QList<Client*> findClient(const QString& uniqueIdentifier);

    void refreshProperties();

    void setEventListener(EventListener* listener);

protected:
    void connectStatusChangedEvent(ConnectStatusChangedEvent* event);
    void serverProtocolVersionEvent(ServerProtocolVersionEvent* event);
    void newChannelEvent(NewChannelEvent* event);
    void newChannelCreatedEvent(NewChannelCreatedEvent* event);
    void channelDeletedEvent(ChannelDeletedEvent* event);
    void channelMovedEvent(ChannelMovedEvent* event);
    void channelUpdatedEvent(ChannelUpdatedEvent* event);
    void channelEditedEvent(ChannelEditedEvent* event);
    void clientUpdatedEvent(ClientUpdatedEvent* event);
    void clientMovedEvent(ClientMovedEvent* event);
    void subscriptionClientMovedEvent(SubscriptionClientMovedEvent* event);
    void clientMoveTimeoutEvent(ClientMoveTimeoutEvent* event);
    void clientMoverMovedEvent(ClientMoverMovedEvent* event);
    void clientKickFromChannelEvent(ClientKickFromChannelEvent* event);
    void clientKickFromServerEvent(ClientKickFromServerEvent* event);
    void clientIDsReceivedEvent(ClientIDsReceivedEvent* event);
    void clientIDsFinishedEvent(ClientIDsFinishedEvent* event);
    void serverEditedEvent(ServerEditedEvent* event);
    void serverUpdatedEvent(ServerUpdatedEvent* event);

    void serverErrorEvent(ServerErrorEvent* event);
    void serverStopEvent(ServerStopEvent* event);
    void textMessageEvent(TextMessageEvent* event);
    void talkStatusChangeEvent(TalkStatusChangeEvent* event);
    void whisperIgnoredEvent(WhisperIgnoredEvent* event);
    void connectionInfoEvent(ConnectionInfoEvent* event);
    void serverConnectionInfoEvent(ServerConnectionInfoEvent* event);

    void channelSubscribedEvent(ChannelSubscribedEvent* event);
    void channelSubscribesFinishedEvent(ChannelSubscribesFinishedEvent* event);
    void channelUnsubscribedEvent(ChannelUnsubscribedEvent* event);
    void channelUnsubscribesFinishedEvent(ChannelUnsubscribesFinishedEvent* event);
    void channelDescriptionUpdatedEvent(ChannelDescriptionUpdatedEvent* event);
    void channelPasswordChangedEvent(ChannelPasswordChangedEvent* event);

    void playbackShutdownCompletedEvent(PlaybackShutdownCompletedEvent* event);

    void fileTransferStatusReceivedEvent(FileTransferStatusReceivedEvent* event);
    void fileListReceivedEvent(FileListReceivedEvent* event);
    void fileListFinishedEvent(FileListFinishedEvent* event);
    void fileInfoReceivedEvent(FileInfoReceivedEvent* event);

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class Connection

} // namespace QTeamSpeak

