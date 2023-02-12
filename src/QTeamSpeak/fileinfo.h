#pragma once

#include <QTeamSpeak/namespace.h>

namespace QTeamSpeak {

class Channel;

class FileInfo
{
public:
    explicit FileInfo(Channel* channel, const QString& path, 
                      const QString& name, quint64 size, 
                      const QDateTime& lastModified, 
                      FileListType type, quint64 incompleteSize);
    ~FileInfo();

    Channel* channel() const;
    QString path() const;
    QString name() const;
    quint64 size() const;

    FileListType type() const;

    QDateTime lastModified() const;
    quint64 incompleteSize() const;

    bool isDir() const;
    bool isFile() const;

private:
    class Private;
    std::unique_ptr<Private> d;

}; // class FileInfo

} // namespace QTeamSpeak

