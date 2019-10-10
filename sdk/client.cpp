#include "client.h"
#include "library.h"
#include "channel.h"
#include "connection.h"
#include "connectioninfo.h"
#include "private/interfacemanager_p.h"

namespace TeamSpeakSdk {

class Client::Private
{
public:
    int getInt(const Client* client, ClientProperty flag)
    {
        return api().getClientVariableAsInt(client, flag);
    }
    bool getBool(const Client* client, ClientProperty flag)
    {
        return getInt(client, flag) != 0;
    }
    uint64 getUInt64(const Client* client, ClientProperty flag)
    {
        return api().getClientVariableAsUInt64(client, flag);
    }
    QString getString(const Client* client, ClientProperty flag, const QString& defaultValue = QString())
    {
        const auto result = api().getClientVariableAsString(client, flag);
        return result.isEmpty() ? defaultValue : result;
    }

    void setInt(Client* client, ClientProperty flag, int value)
    {
        api().setClientSelfVariableAsInt(client->connection(), flag, value);
    }
    void setBool(Client* client, ClientProperty flag, bool value)
    {
        setInt(client, flag, value ? 1 : 0);
    }

    void setString(Client* client, ClientProperty flag, const QString& value, QString& cache)
    {
        if (client != client->connection()->self())
            return;
        api().setClientSelfVariableAsString(client->connection(), flag, value);
        cache = value;
    }

    ID id = 0;
    Connection* connection = Q_NULLPTR;
    struct Cache
    {
        QString nickname;
        QString metaData;
        QString uniqueIdentifier;
    } cached;
};

/*!
* \class Client
*/
Client::Client(Connection* connection)
    : d(new Private)
{
    setConnection(connection);
}

Client::Client(Connection* connection, ID id)
    : Client(connection)
{
    setId(id);
}

Client::~Client()
{
    delete d;
}

Client::Client(const Client& other) Q_DECL_NOTHROW
    : d(new Private)
{
    *d = *other.d;
}

Client::Client(Client&& other) Q_DECL_NOTHROW
{
    *d = *other.d;
}

Client& Client::operator=(const Client& other) Q_DECL_NOTHROW
{
    return *this;
}

Client& Client::operator=(Client&& other) Q_DECL_NOTHROW
{
    return *this;
}

bool Client::operator==(const Client& o) const Q_DECL_NOTHROW
{
    if (this == &o)
        return true;
    return connection() == o.connection() && id() == o.id();
}

/*!
* ID of the client
*/
Client::ID Client::id() const
{
    return d->id;
}

void Client::setId(ID id)
{
    d->id = id;
}

/*!
* Server \sa Connection
*/
Connection* Client::connection() const
{
    return d->connection;
}

void Client::setConnection(Connection* server)
{
    d->connection = server;
}

/*!
* The channel the client is currently joined
*/
Channel* Client::channel() const
{
    return api().getChannelOfClient(this);
}

/*!
* Unique ID for this client. 
* Stays the same after restarting the application,
* so you can use this to identify individual users
*/
QString Client::uniqueIdentifier() const
{
    return d->getString(this, ClientProperty::UniqueIdentifier, d->cached.uniqueIdentifier);
}

/*!
* Nickname used by the client. 
* This value is always automatically updated for visible clients
*/
QString Client::nickname() const
{
    return d->cached.nickname;
}

void Client::setNickname(const QString& value)
{
    d->setString(this, ClientProperty::Nickname, value, d->cached.nickname);
}

/*!
* Application version used by this client. 
* Needs to be requested with \sa requestClientVariables() unless called on own client
*/
QString Client::version() const
{
    return d->getString(this, ClientProperty::Version);
}

/*!
* Operating system used by this client. 
* Needs to be requested with \sa requestClientVariables() unless called on own client.
*/
QString Client::platform() const
{
    return d->getString(this, ClientProperty::Platform);
}

/*!
* Set when the client is currently sending voice data to the server. Always available for visible clients.
*/
bool Client::isTalking() const
{
    return d->getBool(this, ClientProperty::FlagTalking);
}

/*!
* Indicates the mute status of the clients capture device. Always available for visible clients
*/
bool Client::inputMuted() const
{
    return d->getBool(this, ClientProperty::InputMuted);
}

void Client::setInputMuted(bool value)
{
    d->setBool(this, ClientProperty::InputMuted, value);
}

/*!
* Indicates the combined mute status of the clients playback and capture devices. 
* Always available for visible clients
*/
bool Client::outputMuted() const
{
    return d->getBool(this, ClientProperty::OutputMuted);
}

void Client::setOutputMuted(bool value)
{
    d->setBool(this, ClientProperty::OutputMuted, value);
}

/*!
* Indicates the mute status of the clients playback device.
* Always available for visible clients
*/
bool Client::outputOnlyMuted() const
{
    return d->getBool(this, ClientProperty::OutputonlyMuted);
}

/*!
* Set if the clients capture device is not available.
* Always available for visible clients
*/
bool Client::inputHardwareEnabled() const
{
    return d->getBool(this, ClientProperty::InputHardware);
}

/*!
* True if the clients playback device is not available.
* Always available for visible clients
*/
bool Client::outputHardware() const
{
    return d->getBool(this, ClientProperty::OutputHardware);
}

/*!
* Determines if the sound input is deactivated ,
* only usable for \sa Connection::self(), not propagated to the network.
*/
bool Client::isInputDeactivated() const
{
    return d->getBool(this, ClientProperty::InputDeactivated);
}

void Client::setIsInputDeactivated(bool value)
{
    d->setBool(this, ClientProperty::InputDeactivated, value);
}

/*!
* Time the client has been idle. 
* Needs to be requested with \sa requestClientVariables()
*/
time::seconds Client::idleTime() const
{
    const int seconds = d->getInt(this, ClientProperty::IdleTime);
    return time::seconds(seconds);
}

/*!
* Default channel name used in the last \sa Connection::start() call. Only available for own client
*/
QString Client::defaultChannel() const
{
    return d->getString(this, ClientProperty::DefaultChannel);
}

/*!
* Not used by TeamSpeak 3, offers free storage for SDK users. 
* Always available for visible clients
*/
QString Client::metaData() const
{
    return d->getString(this, ClientProperty::MetaData, d->cached.metaData);
}

void Client::setMetaData(const QString& value)
{
    d->setString(this, ClientProperty::MetaData, value, d->cached.metaData);
}

/*!
* Indicates a client has been locally muted. Client-side only
*/
bool Client::muted() const
{
    return d->getBool(this, ClientProperty::IsMuted);
}

void Client::setMuted(bool value)
{
    if (value)
        d->connection->mute({ this });
    else
        d->connection->unmute({ this });
}

/*!
* Indicates a client is currently recording all voice data in his channel
*/
bool Client::isRecording() const
{
    return d->getBool(this, ClientProperty::IsRecording);
}

/*!
* The client volume modifier
*/
float Client::volumeModificator() const
{
    return d->getUInt64(this, ClientProperty::VolumeModificator);
}

void Client::setVolumeModificator(float value)
{
    api().setClientVolumeModifier(this, value);
}

/*!
* Switch the client to a certain channel.
* \a channel the channel to join.
* \a password Optional password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::moveTo(const Channel* channel, const QString& password)
{
    api().requestClientMove(this, channel, password, TODO_RETURN_CODE);
}

/*!
* Kick the client from the channel
* \a kickReason A short message explaining why the client is kicked from the channel.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::kickFromChannel(const QString& kickReason)
{
    api().requestClientKickFromChannel(this, kickReason, TODO_RETURN_CODE);
}

/*!
* Kick the client from the server
* \a kickReason A short message explaining why the client is kicked from the server.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::kickFromServer(const QString& kickReason)
{
    api().requestClientKickFromServer(this, kickReason, TODO_RETURN_CODE);
}

/*!
* Send a private text message to the client.
* \a message The text message
* Returns \c A task that represents the asynchronous operation.
*/
void Client::sendTextMessage(const QString& message)
{
    api().requestSendPrivateTextMsg(this, message, TODO_RETURN_CODE);
}

/*!
* Adjust a position and velocity in 3D space
* \a position position of the given client in 3D space
*/
void Client::set3DAttributes(const Vector3D& position)
{
    api().channelset3DAttributes(this, &position);
}

} // namespace TeamSpeakSdk


