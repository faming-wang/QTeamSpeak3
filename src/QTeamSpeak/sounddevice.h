#pragma once

#include <QTeamSpeak/namespace.h>

namespace QTeamSpeak {

/*!
* \class ISoundDevice
* \brief A device that can either playback or capture sound.
*/
class ISoundDevice
{
public:
    virtual ~ISoundDevice() {}
    virtual QString id() const = 0;
    virtual QString mode() const = 0;
    virtual QString name() const = 0;
};

inline QDebug operator<<(QDebug dbg, const ISoundDevice& a)
{
    QDebugStateSaver saver(dbg);
    dbg << "{ id: " << a.id()
        << "name: " << a.name()
        << "mode: " << a.mode()
        << " }";
    return dbg;
}

/*!
* \class SoundDevice
* \brief A device that can either playback or capture sound
*/
class SoundDevice : public ISoundDevice
{
public:
    explicit SoundDevice(const QString& mode, const QString& id, const QString& name);

    inline QString id() const override { return _id; }
    inline QString mode() const override { return _mode; }
    inline QString name() const override { return _name; }

    bool operator==(const SoundDevice& other) const Q_DECL_NOTHROW;
    bool operator!=(const SoundDevice& other) const Q_DECL_NOTHROW { return !operator==(other); }

private:
    QString _id;
    QString _mode;
    QString _name;

};

/*!
* \class CustomDevice
* \brief A custom device usable for playback and/or capture
*/
class CustomDevice : public ISoundDevice
{
public:
    explicit CustomDevice(const QString& name, SamplingRate captureRate, int captureChannels, SamplingRate playbackRate, int playbackChannels);
    ~CustomDevice();

    inline QString id() const override { return _id; }
    inline QString mode() const override { return modeName; }
    inline QString name() const override { return _name; }

    inline SamplingRate captureRate() const { return _captureRate; }
    inline SamplingRate playbackRate() const { return _playbackRate; }
    inline int captureChannels() const { return _captureChannels; }
    inline int playbackChannels() const { return _playbackChannels; }

    bool acquireData(QVector<short>& buffer);
    bool processData(QVector<short>& buffer); 

    const static QString modeName;

private:
    QString _id;
    QString _name;

    int _captureChannels;
    int _playbackChannels;
    SamplingRate _captureRate;
    SamplingRate _playbackRate;
};

} // namespace QTeamSpeak

