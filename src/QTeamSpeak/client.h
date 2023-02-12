#pragma once

#include <QTeamSpeak/object.h>
#include <QTeamSpeak/connectioninfo.h>

namespace QTeamSpeak {

class Channel;
class Connection;

class Client : public Object
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id WRITE setId)
    Q_PROPERTY(QString nickname READ nickname WRITE setNickname)
    Q_PROPERTY(QString version READ version)
    Q_PROPERTY(QString platform READ platform)
    Q_PROPERTY(bool talking READ isTalking)
    Q_PROPERTY(bool recording READ isRecording)
    Q_PROPERTY(bool inputMuted READ inputMuted WRITE setInputMuted)
    Q_PROPERTY(bool outputMuted READ outputMuted WRITE setOutputMuted)
    Q_PROPERTY(bool inputDeactivated READ isInputDeactivated WRITE setIsInputDeactivated)
    Q_PROPERTY(bool outputOnlyMuted READ outputOnlyMuted)
    Q_PROPERTY(bool inputHardwareEnabled READ inputHardwareEnabled)
    Q_PROPERTY(bool outputHardware READ outputHardware)
    Q_PROPERTY(std::chrono::seconds idleTime READ idleTime)
    Q_PROPERTY(QString defaultChannel READ defaultChannel)
    Q_PROPERTY(QString metaData READ metaData WRITE setMetaData)
    Q_PROPERTY(bool muted READ muted WRITE setMuted)
    Q_PROPERTY(float volumeModificator READ volumeModificator WRITE setVolumeModificator)

public:
    using ID = quint16;

    explicit Client(Connection* connection);
    explicit Client(Connection* connection, ID id);
    ~Client();

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
    bool isRecording() const;

    bool inputMuted() const;
    void setInputMuted(bool value);

    bool outputMuted() const;
    void setOutputMuted(bool value);

    bool isInputDeactivated() const;
    void setIsInputDeactivated(bool value);

    bool outputOnlyMuted() const;
    bool inputHardwareEnabled() const;
    bool outputHardware() const;

    std::chrono::seconds idleTime() const;
    QString defaultChannel() const;

    QString metaData() const;
    void setMetaData(const QString& value);

    bool muted() const;
    void setMuted(bool value);

    float volumeModificator() const;
    void setVolumeModificator(float value);

public slots:
    void moveTo(const Channel* channel, const QString& password = QString());
    void kickFromChannel(const QString& kickReason = QString());
    void kickFromServer(const QString& kickReason = QString());
    void sendTextMessage(const QString& message);
    void set3DAttributes(const Vector3D& position);

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class Client

} // namespace QTeamSpeak

