#include "client.h"
#include "library.h"
#include "channel.h"
#include "connection.h"
#include "connectioninfo.h"
#include "private/interfacemanager_p.h"

namespace QTeamSpeak {

class Client::Private
{
    Client* q_ptr = nullptr;
public:
    Private(Client* q) : q_ptr(q) {

    }

    int getInt(ClientProperty flag)
    {
        return api()->getClientVariableAsInt(q_ptr, flag);
    }

    void setInt(ClientProperty flag, int value)
    {
        api()->setClientSelfVariableAsInt(q_ptr->connection(), flag, value);
    }

    bool getBool(ClientProperty flag)
    {
        return getInt(flag) != 0;
    }

    void setBool(ClientProperty flag, bool value)
    {
        setInt(flag, value ? 1 : 0);
    }

    QString getString(ClientProperty flag, const QString& defaultValue = QString())
    {
        const auto result = api()->getClientVariableAsString(q_ptr, flag);
        return result.isEmpty() ? defaultValue : result;
    }

    void setString(ClientProperty flag, const QString& value, QString& cache)
    {
        if (q_ptr != q_ptr->connection()->self())
            return;
        api()->setClientSelfVariableAsString(q_ptr->connection(), flag, value);
        cache = value;
    }

    quint64 getUInt64(ClientProperty flag)
    {
        return api()->getClientVariableAsUInt64(q_ptr, flag);
    }

public:
    ID id = 0;

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
    : Object(connection)
    , d(new Private(this))
{

}

Client::Client(Connection* connection, ID id)
    : Object(connection)
    , d(new Private(this))
{
    d->id = id;
}

Client::~Client()
{

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
    return qobject_cast<Connection*>(parent());
}

void Client::setConnection(Connection* server)
{
    if (parent() != server) {
        setParent(server);
    }
}

/*!
* The channel the client is currently joined
*/
Channel* Client::channel() const
{
    return api()->getChannelOfClient(this);
}

/*!
* Unique ID for this client. 
* Stays the same after restarting the application,
* so you can use this to identify individual users
*/
QString Client::uniqueIdentifier() const
{
    return d->getString(ClientProperty::UniqueIdentifier, d->cached.uniqueIdentifier);
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
    d->setString(ClientProperty::Nickname, value, d->cached.nickname);
}

/*!
* Application version used by this client. 
* Needs to be requested with \sa requestClientVariables() unless called on own client
*/
QString Client::version() const
{
    return d->getString(ClientProperty::Version);
}

/*!
* Operating system used by this client. 
* Needs to be requested with \sa requestClientVariables() unless called on own client.
*/
QString Client::platform() const
{
    return d->getString(ClientProperty::Platform);
}

/*!
* Set when the client is currently sending voice data to the server. Always available for visible clients.
*/
bool Client::isTalking() const
{
    return d->getBool(ClientProperty::FlagTalking);
}

/*!
* Indicates the mute status of the clients capture device. Always available for visible clients
*/
bool Client::inputMuted() const
{
    return d->getBool(ClientProperty::InputMuted);
}

void Client::setInputMuted(bool value)
{
    d->setBool(ClientProperty::InputMuted, value);
}

/*!
* Indicates the combined mute status of the clients playback and capture devices. 
* Always available for visible clients
*/
bool Client::outputMuted() const
{
    return d->getBool(ClientProperty::OutputMuted);
}

void Client::setOutputMuted(bool value)
{
    d->setBool(ClientProperty::OutputMuted, value);
}

/*!
* Indicates the mute status of the clients playback device.
* Always available for visible clients
*/
bool Client::outputOnlyMuted() const
{
    return d->getBool(ClientProperty::OutputonlyMuted);
}

/*!
* Set if the clients capture device is not available.
* Always available for visible clients
*/
bool Client::inputHardwareEnabled() const
{
    return d->getBool(ClientProperty::InputHardware);
}

/*!
* True if the clients playback device is not available.
* Always available for visible clients
*/
bool Client::outputHardware() const
{
    return d->getBool(ClientProperty::OutputHardware);
}

/*!
* Determines if the sound input is deactivated ,
* only usable for \sa Connection::self(), not propagated to the network.
*/
bool Client::isInputDeactivated() const
{
    return d->getBool(ClientProperty::InputDeactivated);
}

void Client::setIsInputDeactivated(bool value)
{
    d->setBool(ClientProperty::InputDeactivated, value);
}

/*!
* Time the client has been idle. 
* Needs to be requested with \sa requestClientVariables()
*/
std::chrono::seconds Client::idleTime() const
{
    const int seconds = d->getInt(ClientProperty::IdleTime);
    return std::chrono::seconds(seconds);
}

/*!
* Default channel name used in the last \sa Connection::start() call. Only available for own client
*/
QString Client::defaultChannel() const
{
    return d->getString(ClientProperty::DefaultChannel);
}

/*!
* Not used by TeamSpeak 3, offers free storage for SDK users. 
* Always available for visible clients
*/
QString Client::metaData() const
{
    return d->getString(ClientProperty::MetaData, d->cached.metaData);
}

void Client::setMetaData(const QString& value)
{
    d->setString(ClientProperty::MetaData, value, d->cached.metaData);
}

/*!
* Indicates a client has been locally muted. Client-side only
*/
bool Client::muted() const
{
    return d->getBool(ClientProperty::IsMuted);
}

void Client::setMuted(bool value)
{
    if (value)
        connection()->mute({ this });
    else
        connection()->unmute({ this });
}

/*!
* Indicates a client is currently recording all voice data in his channel
*/
bool Client::isRecording() const
{
    return d->getBool(ClientProperty::IsRecording);
}

/*!
* The client volume modifier
*/
float Client::volumeModificator() const
{
    return d->getUInt64(ClientProperty::VolumeModificator);
}

void Client::setVolumeModificator(float value)
{
    api()->setClientVolumeModifier(this, value);
}

/*!
* Switch the client to a certain channel.
* \a channel the channel to join.
* \a password Optional password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::moveTo(const Channel* channel, const QString& password)
{
    api()->requestClientMove(this, channel, password, TODO_RETURN_CODE);
}

/*!
* Kick the client from the channel
* \a kickReason A short message explaining why the client is kicked from the channel.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::kickFromChannel(const QString& kickReason)
{
    api()->requestClientKickFromChannel(this, kickReason, TODO_RETURN_CODE);
}

/*!
* Kick the client from the server
* \a kickReason A short message explaining why the client is kicked from the server.
* Returns \c A task that represents the asynchronous operation.
*/
void Client::kickFromServer(const QString& kickReason)
{
    api()->requestClientKickFromServer(this, kickReason, TODO_RETURN_CODE);
}

/*!
* Send a private text message to the client.
* \a message The text message
* Returns \c A task that represents the asynchronous operation.
*/
void Client::sendTextMessage(const QString& message)
{
    api()->requestSendPrivateTextMsg(this, message, TODO_RETURN_CODE);
}

/*!
* Adjust a position and velocity in 3D space
* \a position position of the given client in 3D space
*/
void Client::set3DAttributes(const Vector3D& position)
{
    api()->channelset3DAttributes(this, &position);
}

} // namespace QTeamSpeak


