#pragma once

namespace TeamSpeakSdk {

class ConnectionInfo;

class TEAMSPEAKSDK_EXPORT Client
{
public:
    using ID = uint16;

    explicit Client(Connection* connection);
    explicit Client(Connection* connection, ID id);
    ~Client();
    Client(const Client& other) Q_DECL_NOTHROW;
    Client(Client&& other) Q_DECL_NOTHROW;
    Client& operator=(const Client& other) Q_DECL_NOTHROW;
    Client& operator=(Client&& other) Q_DECL_NOTHROW;
    bool operator==(const Client& o) const Q_DECL_NOTHROW;
    inline bool operator!=(const Client& o) const Q_DECL_NOTHROW { return !operator==(o); }
    inline bool compare(const Client& o) const Q_DECL_NOTHROW { return *this == o; }

public:
    ID id() const;
    void setId(ID id);

    Connection* connection() const;
    void setConnection(Connection* server);

    Channel* channel() const;
    QString uniqueIdentifier() const;

    QString nickname() const;
    void setNickname(const QString& value);

    QString version() const;
    QString platform() const;

    bool isTalking() const;

    bool inputMuted() const;
    void setInputMuted(bool value);

    bool outputMuted() const;
    void setOutputMuted(bool value);

    bool isInputDeactivated() const;
    void setIsInputDeactivated(bool value);

    bool outputOnlyMuted() const;
    bool inputHardwareEnabled() const;
    bool outputHardware() const;

    time::seconds idleTime() const;
    QString defaultChannel() const;

    QString metaData() const;
    void setMetaData(const QString& value);

    bool muted() const;
    void setMuted(bool value);

    bool isRecording() const;

    float volumeModificator() const;
    void setVolumeModificator(float value);

public:
    void moveTo(const Channel* channel, const QString& password = QString());
    void kickFromChannel(const QString& kickReason = QString());
    void kickFromServer(const QString& kickReason = QString());
    void sendTextMessage(const QString& message);
    void set3DAttributes(const Vector3D& position);

private:
    class Private;
    Private* d = Q_NULLPTR;

}; // class Client

} // namespace TeamSpeakSdk

