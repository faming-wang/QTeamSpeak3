#pragma once

namespace TeamSpeakSdk {

class Connection;

class TEAMSPEAKSDK_EXPORT FileTransfer
{
public:
    using ID = uint16;
    enum class State : int
    {
        Initializing = 0, // Transfer is being initialized.
        Active          , // File is being transfered.
        Finished        , // Transfer finished.
    };

    explicit FileTransfer(Connection* connection, ID id);
    ~FileTransfer();
    Connection* connection() const;

    ID id() const;
    State status() const;

    QString name() const;
    QString path() const;
    QString remotePath() const;
    uint64 size() const;
    uint64 sizeDone() const;
    TransferMode mode() const;

    float currentSpeed() const;
    float averageSpeed() const;

    time::milliseconds runTime();

    uint64 speedLimit() const;
    void setSpeedLimit(uint64 value) const;

    void abort(bool deleteUnfinishedFile = false);

private:
    class Private;
    Private* const d = Q_NULLPTR;

}; // class FileTransfer

} // namespace TeamSpeakSdk

