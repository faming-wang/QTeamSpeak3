#pragma once

namespace TeamSpeakSdk {

class Channel;

class TEAMSPEAKSDK_EXPORT FileInfo
{
public:
    explicit FileInfo(Channel* channel, const QString& path, 
                      const QString& name, uint64 size, 
                      const QDateTime& lastModified, 
                      FileListType type, uint64 incompleteSize);
    ~FileInfo();

    Channel* channel() const;
    QString path() const;
    QString name() const;
    uint64 size() const;

    FileListType type() const;

    QDateTime lastModified() const;
    uint64 incompleteSize() const;

    bool isDir() const;
    bool isFile() const;

private:
    class Private;
    Private* d = Q_NULLPTR;

}; // class FileInfo

} // namespace TeamSpeakSdk

