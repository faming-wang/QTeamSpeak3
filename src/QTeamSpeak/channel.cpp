#include "channel.h"

#include "library.h"
#include "fileinfo.h"
#include "connection.h"
#include "filetransfer.h"

#include "private/utils_p.h"
#include "private/interfacemanager_p.h"

namespace QTeamSpeak {

class Channel::Private
{
    Channel* q_ptr = nullptr;
public:
    Private(Channel* q) : q_ptr(q) {

    }

    int getInt(ChannelProperty flag)
    {
        return api()->getChannelVariableAsInt(q_ptr, flag);
    }

    quint64 getUInt64(ChannelProperty flag)
    {
        return api()->getChannelVariableAsUInt64(q_ptr, flag);
    }

    QString getString(ChannelProperty flag)
    {
        return api()->getChannelVariableAsString(q_ptr, flag);
    }

    void setInt(ChannelProperty flag, int value)
    {
        api()->setChannelVariableAsInt(q_ptr, flag, value);
        flushChannelUpdates();
    }

    void setUInt64(ChannelProperty flag, quint64 value)
    {
        api()->setChannelVariableAsUInt64(q_ptr, flag, value);
        flushChannelUpdates();
    }

    void setString(ChannelProperty flag, const QString& value)
    {
        api()->setChannelVariableAsString(q_ptr, flag, value);
        flushChannelUpdates();
    }

    void flushChannelUpdates()
    {
        if (q_ptr->id() == 0)
            return;
        // TODO: 
    }

    ID id = 0;
    struct Cache
    {
        QString name;
        QString topic;
    } cached;

};
/*!
* \class Channel
*
* \brief
*/
Channel::Channel(Connection* connection)
    : Object(connection)
    , d(new Private(this))
{

}

Channel::Channel(Connection* connection, ID id, bool waitForProperties)
    : Object(connection)
    , d(new Private(this))
{
    d->id = id;
    refreshProperties(waitForProperties);
}

Channel::~Channel()
{

}

/*!
* ID of the channel
*/
Channel::ID Channel::id() const
{
    return d->id;
}

void Channel::setId(ID id)
{
    d->id = id;
}
/*!
* Server Connection
*/
Connection* Channel::connection() const
{
    return qobject_cast<Connection*>(parent());
}

void Channel::setConnection(Connection* server)
{
    if (parent() != server) {
        setParent(server);
    }
}

/*!
* The parent channel
*/
Channel* Channel::parentChannel() const
{
    return api()->getParentChannelOfChannel(this);
}

/*!
* List of all clients in the channel, if the channel is currently subscribed.
*/
QList<Client*> Channel::clients() const
{
    return api()->getChannelClientList(this);
}

QList<Channel*> Channel::channels() const
{
    return QList<Channel*>();
}

/*!
* Name of the channel
*/
QString Channel::name() const
{
    return d->cached.name;
}

void Channel::setName(const QString& value)
{
    d->setString(ChannelProperty::Name, value);
}

/*!
* Single-line channel topic
*/
QString Channel::topic() const
{
    return d->cached.topic;
}

void Channel::setTopic(const QString& value)
{
    d->setString(ChannelProperty::Topic, value);
}

/*!
* Optional channel description. Can have multiple lines. 
* Needs to be request with \sa getChannelDescription().
*/
QString Channel::description() const
{
    return d->getString(ChannelProperty::Description);
}

void Channel::setDescription(const QString& value)
{
    d->setString(ChannelProperty::Description, value);
}

/*!
* Optional password for password-protected channels.
*/
void Channel::setPassword(const QString& value)
{
    d->setString(ChannelProperty::Password, value);
}

/*!
* Codec used for this channel
*/
CodecType Channel::codec() const
{
    return CodecType(d->getInt(ChannelProperty::Codec));
}

void Channel::setCodec(CodecType value)
{
    d->setInt(ChannelProperty::Codec, Utils::underlay(value));
}

/*!
* Quality of channel codec of this channel. 
* Valid values range from 0 to 10, default is 7. 
* Higher values result in better speech quality but more bandwidth usage
*/
int Channel::codecQuality() const
{
    return d->getInt(ChannelProperty::CodecQuality);
}

void Channel::setCodecQuality(int value)
{
    d->setInt(ChannelProperty::CodecQuality, value);
}

/*!
* Number of maximum clients who can join this channel
*/
int Channel::maxClients() const
{
    return d->getInt(ChannelProperty::Maxclients);
}

void Channel::setMaxClients(int value)
{
    d->setInt(ChannelProperty::Maxclients, value);
}

/*!
* Number of maximum clients who can join this channel and all subchannels
*/
int Channel::maxFamilyClients() const
{
    return d->getInt(ChannelProperty::Maxfamilyclients);
}

void Channel::setMaxFamilyClients(int value)
{
    d->setInt(ChannelProperty::Maxfamilyclients, value);
}

/*!
* \sa order() is the \sa channel() after which this channel is sorted. 
* <see lang word="null" meaning its going to be the first \sa channel() under \sa parent()
*/
Channel* Channel::orderChannel() const
{
    const auto orderId = d->getUInt64(ChannelProperty::Order);
    return connection()->getChannel(orderId);
}

void Channel::setOrder(const Channel* value)
{
    d->setUInt64(ChannelProperty::Order, value ? value->id() : 0);
}

/*!
* Permanent channels will be restored when the server restarts.
*/
bool Channel::isPermanent() const
{
    return d->getInt(ChannelProperty::FlagPermanent) != 0;
}

void Channel::setPermanent(bool value)
{
    d->setInt(ChannelProperty::FlagPermanent, value ? 1 : 0);
}

/*!
* Semi-permanent channels are not automatically deleted when the last user left
* but will not be restored when the server restarts.
*/
bool Channel::isSemiPermanent() const
{
    return d->getInt(ChannelProperty::FlagSemiPermanent) != 0;
}

void Channel::setSemiPermanent(bool value)
{
    d->setInt(ChannelProperty::FlagSemiPermanent, value ? 1 : 0);
}

/*!
* Channel is the default channel. 
* There can only be one default channel per server. 
* New users who did not configure a channel to join on login in ts3client_startConnection will automatically join the default channel.
*/
bool Channel::isDefault() const
{
    return d->getInt(ChannelProperty::FlagDefault) != 0;
}

void Channel::setDefault(bool value)
{
    d->setInt(ChannelProperty::FlagDefault, value ? 1 : 0);
}

/*!
* If set, channel is password protected. 
* The password itself is stored in ChannelPassword
*/
bool Channel::isPasswordProtected() const
{
    return d->getInt(ChannelProperty::FlagPassword) != 0;
}

/*!
* Latency of this channel.
* Allows to increase the packet size resulting in less bandwidth usage at the cost of higher latency. 
* A value of 1 (default) is the best setting for lowest latency and best quality. 
* If bandwidth or network quality are restricted, increasing the latency factor can help stabilize the connection. 
* Higher latency values are only possible for low-quality codec and codec quality settings.
*/
int Channel::codecLatencyFactor() const
{
    return d->getInt(ChannelProperty::CodecLatencyFactor);
}

void Channel::setCodecLatencyFactor(int value)
{
    d->setInt(ChannelProperty::CodecLatencyFactor, value);
}
/*!
* If true, this channel is not using encrypted voice data. 
* If false, voice data is encrypted for this channel.
* Note that channel voice data encryption can be globally disabled or enabled for the virtual server. 
* Changing this flag makes only sense if global voice data encryption is set to be configured per channel.
*/
bool Channel::codecIsUnencrypted() const
{
    return d->getInt(ChannelProperty::CodecIsUnencrypted) != 0;
}

void Channel::setCodecIsUnencrypted(bool value)
{
    d->setInt(ChannelProperty::CodecIsUnencrypted, value ? 1 : 0);
}

std::chrono::seconds Channel::deleteDelay() const
{
    const auto time = d->getInt(ChannelProperty::DeleteDelay);
    return std::chrono::seconds(time);
}

void Channel::setDeleteDelay(const std::chrono::seconds& value)
{
    d->setInt(ChannelProperty::DeleteDelay, int(value.count()));
}

std::chrono::seconds Channel::channelEmptyTime() const
{
    const auto time = api()->getChannelEmptySecs(this); 
    return std::chrono::seconds(time);
}

/*!
* Uploads a local file to the server
* \a "file" Path of the local file, which is to be uploaded.
* \a "overwrite" when false, upload will abort if remote file exists
* \a "resume" If we have a previously halted transfer: true = resume, false = restart transfer
* \a "channelPassword" Optional channel password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous upload operation.
*/
void Channel::sendFile(const FileTransferOption& option)
{
    api()->sendFile(
        this, 
        option.password, 
        option.file.fileName(), 
        option.overwrite, 
        option.resume, 
        option.file.dir().path(), 
        TODO_RETURN_CODE
    );
}

/*!
* Download a file from the server.
* \a "fileName" Filename of the remote file, which is to be downloaded.
* \a "destinationDirectory" Local target directory name where the download file should be saved.
* \a "overwrite" when false, download will abort if local file exists
* \a "resume" If we have a previously halted transfer: true = resume, false = restart transfer
* \a "channelPassword" Optional channel password. Pass empty string or null if unused.
* \a "cancellationToken" The token to monitor for cancellation requests. The default value is \sa "CancellationToken.None"
* Returns \c A task that represents the asynchronous download operation.
*/
void Channel::requestFile(const FileTransferOption& option)
{
    api()->requestFile(
        this, 
        option.password, 
        option.file.fileName(), 
        option.overwrite, 
        option.resume, 
        option.file.dir().path(),
        TODO_RETURN_CODE
    );
}

/*!
* Query list of files in a directory.
* \a  "path" Path inside the channel, defining the subdirectory. Top level path is ??
* \a  "channelPassword" Optional channel password. Pass empty string or null if unused.
* Returns \c A task that returns the list of files contained in path
*/
void Channel::getFileList(const QString& path, const QString& channelPassword)
{
   api()->requestFileList(this, channelPassword, path, TODO_RETURN_CODE);
}

/*!
* Query information of a specified file. The answer from the server will trigger \sa "Connection.FileInfoReceived" with the requested information.
* \a "file" File name we want to request info from, needs to include the full path within the channel, e.g. ?file?for a top-level file or ?dir1/dir2/file?for a file located in a subdirectory.
* \a "channelPassword" Optional channel password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::getFileInfo(const QString& file, const QString& channelPassword)
{
    api()->requestFileInfo(this, channelPassword, file, TODO_RETURN_CODE);
}

/*!
* Create a directory.
* \a path Name of the directory to create. The directory name needs to include the full path within the channel, e.g. ?file?for a top-level file or ?dir1/dir2/file?for a file located in a subdirectory.
* \a password Optional channel password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::mkdir(const QString& path, const QString& password)
{
    api()->requestCreateDirectory(this, password, path, TODO_RETURN_CODE);
}

/*!
* Moves or renames a file. If the source and target channels and paths are the same, the file will simply be renamed.
* \a "file" Old name of the file. The file name needs to include the full path within the channel, e.g. ?file?for a top-level file or ?dir1/dir2/file?for a file located in a subdirectory.
* \a "channelPassword" Optional channel password. Pass empty string or null if unused.
* \a "toFile" New name of the file. The new name needs to include the full path within the channel, e.g. ?file?for a top-level file or ?dir1/dir2/file?for a file located in a subdirectory.
* \a "toChannel" Target channel, to which we want to move the file.
* \a "toChannelPassword" Optional channel password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::moveFile(const QString& file, const QString& toFile, const QString& channelPassword, const Channel* toChannel, const QString& toChannelPassword)
{
    api()->requestRenameFile(
        this, 
        channelPassword, 
        toChannel ? toChannel : this, 
        toChannelPassword,
        file, 
        toFile, 
        TODO_RETURN_CODE
    );
}

/*!
* Delete one or more remote files on the server.
* \a "files" List of files we request to be deleted. The file names need to include the full path within the channel, e.g. ?file?for a top-level file or ?dir1/dir2/file?for a file located in a subdirectory.
* \a "channelPassword" Optional channel password. Pass empty string or null if unused.
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::deleteFile(const QStringList& files, const QString& channelPassword)
{
    api()->requestDeleteFile(this, channelPassword, files, TODO_RETURN_CODE);
}

/*!
* Request updating the channel description
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::getChannelDescription() const
{
    api()->requestChannelDescription(this, TODO_RETURN_CODE);
}

/*!
* Removes the channel from the server
* \a "force" If true, the channel will be deleted even when it is not empty. 
* Clients within the deleted channel are transfered to the default channel. 
* Any contained subchannels are removed as well. 
* If \c false, the server will refuse to delete a channel that is not empty.
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::remove(bool force)
{
    api()->requestChannelDelete(this, force, TODO_RETURN_CODE);
}

/*!
* Send a text message to the channel
* \a "message" The text message
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::sendTextMessage(const QString& message)
{
    api()->requestSendChannelTextMsg(this, message, TODO_RETURN_CODE);
}

/*!
* Move the channel to a new parent channel
* \a "newParent" The parent channel where the moved channel is to be inserted as child. Use null to insert as top-level channel.
* \a "newChannelOrder" the \sa "Channel" after which <see langword="this" \sa "Channel" is sorted. <see langword="null" meaning its going to be the first \sa "Channel" under <paramref name="newParent".
* Returns \c A task that represents the asynchronous operation.
*/
void Channel::moveTo(Channel* newParent, Channel* newChannelOrder)
{
    if (Utils::has_null(newParent))
        return;
    if (!Utils::is_same_server(connection(), newParent, newChannelOrder))
        return;

    api()->requestChannelMove(this, newParent, newChannelOrder, TODO_RETURN_CODE);
}

void Channel::flushUpdates()
{
    d->flushChannelUpdates();
}

void Channel::refreshProperties(bool wait)
{

}

} // namespace QTeamSpeak

