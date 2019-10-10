#pragma once

namespace TeamSpeakSdk {

class FileInfo;
class FileTransfer;

class TEAMSPEAKSDK_EXPORT Channel
{
public:
    using ID = uint64;

    explicit Channel(Connection* connection);
    explicit Channel(Connection* connection, ID id, bool waitForProperties = false);
    ~Channel();
    Channel(const Channel& other) Q_DECL_NOTHROW;
    Channel(Channel&& other) Q_DECL_NOTHROW;
    Channel& operator=(const Channel& other) Q_DECL_NOTHROW;
    Channel& operator=(Channel&& other) Q_DECL_NOTHROW;
    bool operator==(const Channel& o) const Q_DECL_NOTHROW;
    inline bool operator!=(const Channel& o) const Q_DECL_NOTHROW { return !operator==(o); }
    inline bool compare(const Channel& o) const Q_DECL_NOTHROW { return *this == o; }
    void swap(Channel&& other);

public: // property 
    ID id() const;
    void setId(ID id);

    Connection* connection() const;
    void setConnection(Connection* server);

    QList<Client*> clients() const;
    QList<Channel*> channels() const;

    Channel* order() const;
    Channel* parent() const;

    void setOrder(const Channel* value);
    void setPassword(const QString& value);

    QString name() const;
    void setName(const QString& value);

    QString topic() const;
    void setTopic(const QString& value);

    QString description() const;
    void setDescription(const QString& value);

    CodecType codec() const;
    void setCodec(CodecType value);

    int codecQuality() const;
    void setCodecQuality(int value);

    int maxClients() const;
    void setMaxClients(int value);

    int maxFamilyClients() const;
    void setMaxFamilyClients(int value);

    bool isPermanent() const;
    void setPermanent(bool value);

    bool isSemiPermanent() const;
    void setSemiPermanent(bool value);

    bool isDefault() const;
    void setDefault(bool value);

    bool isPasswordProtected() const;

    int codecLatencyFactor() const;
    void setCodecLatencyFactor(int value);

    bool codecIsUnencrypted() const;
    void setCodecIsUnencrypted(bool value);

    time::seconds deleteDelay() const;
    void setDeleteDelay(const time::seconds& value);

    time::seconds channelEmptyTime() const;

public:
    void sendFile(const FileTransferOption& option);
    void requestFile(const FileTransferOption& option);

    void getFileList(const QString& path = "/", const QString& channelPassword = QString());
    void getFileInfo(const QString& file, const QString& channelPassword = QString());

    void mkdir(const QString& path, const QString& password = QString());
    void moveFile(const QString& file, const QString& toFile, const QString& password = QString(), const Channel* toChannel = Q_NULLPTR, const QString& toChannelPassword = QString());
    void deleteFile(const QStringList& files, const QString& password = QString());

    void remove(bool force = false);
    void moveTo(Channel* newParent, Channel* newChannelOrder = Q_NULLPTR);
    void sendTextMessage(const QString& message);

    void getChannelDescription() const;
    void refreshProperties(bool wait);
    void flushUpdates();

private:
    class Private;
    Private* d = Q_NULLPTR;

}; // class Channel

} // namespace TeamSpeakSdk

