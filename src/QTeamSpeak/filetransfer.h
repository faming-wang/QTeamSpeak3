#pragma once

#include <QTeamSpeak/object.h>

namespace QTeamSpeak {

class Connection;

class FileTransfer : public Object
{
    Q_OBJECT
    Q_PROPERTY(ID id READ id)
    Q_PROPERTY(State status READ status)
    Q_PROPERTY(QString name READ name)
    Q_PROPERTY(QString path READ path)
    Q_PROPERTY(QString remotePath   READ remotePath)
    Q_PROPERTY(quint64 size READ size)
    Q_PROPERTY(quint64 sizeDone READ sizeDone)
    Q_PROPERTY(TransferMode mode READ mode)
    Q_PROPERTY(float currentSpeed READ currentSpeed)
    Q_PROPERTY(float averageSpeed READ averageSpeed)
    Q_PROPERTY(std::chrono::milliseconds runTime READ runTime)
    Q_PROPERTY(quint64 speedLimit READ speedLimit WRITE setSpeedLimit)

public:
    using ID = quint16;
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
    quint64 size() const;
    quint64 sizeDone() const;
    TransferMode mode() const;

    float currentSpeed() const;
    float averageSpeed() const;

    std::chrono::milliseconds runTime();

    quint64 speedLimit() const;
    void setSpeedLimit(quint64 value) const;

public slots:
    void abort(bool deleteUnfinishedFile = false);

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class FileTransfer

} // namespace QTeamSpeak

