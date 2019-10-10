#include "filetransfer.h"

#include "private/interfacemanager_p.h"

namespace TeamSpeakSdk {

class FileTransfer::Private
{
public:
    ID id = 0;
    Connection* connection = Q_NULLPTR;
};

/*!
* \class FileTransfer
* \brief An ongoing file transfer
*/
FileTransfer::FileTransfer(Connection* connection, ID id)
    : d(new Private)
{
    d->id = id;
    d->connection = connection;
}

FileTransfer::~FileTransfer()
{
    delete d;
}

/*!
* ID of the client
*/
FileTransfer::ID FileTransfer::id() const
{
    return d->id;
}

/*!
* Server Connection
*/
Connection* FileTransfer::connection() const
{
    return d->connection;
}

/*!
* the file name
*/
QString FileTransfer::name() const
{
    return api().getTransferFileName(this);
}

/*!
* the file path
*/
QString FileTransfer::path() const
{
    return api().getTransferFilePath(this);
}

/*!
* the remote path on the server
*/
QString FileTransfer::remotePath() const
{
    return api().getTransferFileRemotePath(this);
}

/*!
* the file size
*/
uint64 FileTransfer::size() const
{
    return api().getTransferFileSize(this);
}

/*!
* the currently transferred file size
*/
uint64 FileTransfer::sizeDone() const
{
    return api().getTransferFileSizeDone(this);
}

/*!
* specifies if the transfer an upload or a download.
*/
TransferMode FileTransfer::mode() const
{
    return api().isTransferSender(this) ? TransferMode::Upload : TransferMode::Download;
}

/*!
* the status of the specified transfer
*/
FileTransfer::State FileTransfer::status() const
{
    return api().getTransferStatus(this);
}

/*!
* the current speed of the transfer
*/
float FileTransfer::currentSpeed() const
{
    return api().getCurrentTransferSpeed(this);
}

/*!
* the average speed of the specified transfer
*/
float FileTransfer::averageSpeed() const
{
    return api().getAverageTransferSpeed(this);
}

/*!
* the time the transfer has used
*/
time::milliseconds FileTransfer::runTime()
{
    return time::milliseconds(api().getTransferRunTime(this));
}

/*!
* To get the speed limit for the transfer in bytes/s:
*/
uint64 FileTransfer::speedLimit() const
{
    return api().getTransferSpeedLimit(this);
}

void FileTransfer::setSpeedLimit(uint64 value) const
{
    api().setTransferSpeedLimit(this, value);
}

/*!
* Abort the transfer
* \a deleteUnfinishedFile true to delete the unfinished file; otherwise, keep file so it can be resumed.
*/
void FileTransfer::abort(bool deleteUnfinishedFile)
{
    api().haltTransfer(this, deleteUnfinishedFile, TODO_RETURN_CODE);
}

} // namespace TeamSpeakSdk

