#pragma once

#include <QTeamSpeak/object.h>

namespace QTeamSpeak {

class FileInfo;
class FileTransfer;

class Channel : public Object
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id WRITE setId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString topic READ topic WRITE setTopic)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(CodecType codec READ codec WRITE setCodec)
    Q_PROPERTY(int codecQuality READ codecQuality WRITE setCodecQuality)
    Q_PROPERTY(int maxClients READ maxClients WRITE setMaxClients)
    Q_PROPERTY(int maxFamilyClients READ maxFamilyClients WRITE setMaxFamilyClients)
    Q_PROPERTY(bool isPermanent READ isPermanent WRITE setPermanent)
    Q_PROPERTY(bool isSemiPermanent READ isSemiPermanent WRITE setSemiPermanent)
    Q_PROPERTY(bool isDefault READ isDefault WRITE setDefault)
    Q_PROPERTY(bool isPasswordProtected READ isPasswordProtected)
    Q_PROPERTY(int codecLatencyFactor READ codecLatencyFactor WRITE setCodecLatencyFactor)
    Q_PROPERTY(bool codecIsUnencrypted READ codecIsUnencrypted WRITE setCodecIsUnencrypted)
    Q_PROPERTY(std::chrono::seconds deleteDelay READ deleteDelay WRITE setDeleteDelay)
    Q_PROPERTY(std::chrono::seconds channelEmptyTime READ channelEmptyTime)

public:
    using ID = quint64;

    explicit Channel(Connection* connection);
    explicit Channel(Connection* connection, ID id, bool waitForProperties = false);
    ~Channel();

public: // property 
    ID id() const;
    void setId(ID id);

    Connection* connection() const;
    void setConnection(Connection* server);

    QList<Client*> clients() const;
    QList<Channel*> channels() const;

    Channel* orderChannel() const;
    Channel* parentChannel() const;

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

    std::chrono::seconds deleteDelay() const;
    void setDeleteDelay(const std::chrono::seconds& value);

    std::chrono::seconds channelEmptyTime() const;

public slots:
    void sendFile(const FileTransferOption& option);
    void requestFile(const FileTransferOption& option);

    void getFileList(const QString& path = "/", const QString& channelPassword = QString());
    void getFileInfo(const QString& file, const QString& channelPassword = QString());

    void mkdir(const QString& path, const QString& password = QString());
    void moveFile(const QString& file, const QString& toFile, const QString& password = QString(), const Channel* toChannel = nullptr, const QString& toChannelPassword = QString());
    void deleteFile(const QStringList& files, const QString& password = QString());

    void remove(bool force = false);
    void moveTo(Channel* newParent, Channel* newChannelOrder = nullptr);
    void sendTextMessage(const QString& message);

    void getChannelDescription() const;
    void refreshProperties(bool wait);
    void flushUpdates();

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class Channel

} // namespace QTeamSpeak

