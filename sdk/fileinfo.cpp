#include "fileinfo.h"

namespace TeamSpeakSdk {

class FileInfo::Private
{
public:
    Channel* channel = Q_NULLPTR;
    QString path;
    QString name;
    FileListType type;
    QDateTime lastModified;
    uint64 size;
    uint64 incompleteSize;
};

/*!
* \class FileInfo
*
* \brief
*/
FileInfo::FileInfo(Channel* channel, const QString& path, const QString& name, uint64 size, const QDateTime& lastModified, FileListType type, uint64 incompleteSize)
    : d(new Private)
{
    d->channel = channel;
    d->path = path;
    d->name = name;
    d->size = size;
    d->type = type;
    d->lastModified = lastModified;
    d->incompleteSize = incompleteSize;
}

FileInfo::~FileInfo()
{
    delete d;
}

/*!
* \sa Channel for which a \sa FileInfo" was requested.
*/
Channel* FileInfo::channel() const
{
    return d->channel;
}

/*!
* Subdirectory inside the channel for which the FileInfo was requested. ¡°/¡± indicates the root directory is listed.
*/
QString FileInfo::path() const
{
    return d->path;
}

/*!
* File name.
*/
QString FileInfo::name() const
{
    return d->name;
}

/*!
* File size,
*/
uint64 FileInfo::size() const
{
    return d->size;
}

/*!
* The date and time on which the file was last modified.
*/
QDateTime FileInfo::lastModified() const
{
    return d->lastModified;
}

/*!
* Indicates if this entry is a directory or a file.
*/
FileListType FileInfo::type() const
{
    return d->type;
}

/*!
* Indicates if this entry is a directory or a file.
*/
uint64 FileInfo::incompleteSize() const
{
    return d->incompleteSize;
}

bool FileInfo::isDir() const
{
    return d->type == FileListType::Directory;
}

bool FileInfo::isFile() const
{
    return d->type == FileListType::File;
}

} // namespace TeamSpeakSdk

