#include "sounddevice.h"

#include "private/interfacemanager_p.h"

namespace TeamSpeakSdk {

SoundDevice::SoundDevice(const QString& mode, const QString& id, const QString& name)
    : _mode(mode)
    , _id(id)
    , _name(name)
{}

bool SoundDevice::operator==(const SoundDevice& other) const Q_DECL_NOTHROW
{
    return _id == other._id 
        && _mode == other._mode
        ;
}

const QString CustomDevice::modeName = "custom";

/*!
* Creates a new CustomDevice
* \a name human-readable name
* \a captureRate sampling rate of the capture
* \a captureChannels amount of channels to capture, can be 1 or 2
* \a playbackRate sampling rate of the playback
* \a playbackChannels amount of channels of the playback, can be 1 or 2
*/
CustomDevice::CustomDevice(const QString& name, SamplingRate captureRate, int captureChannels, SamplingRate playbackRate, int playbackChannels)
{
    _id               = QUuid::createUuid().toString();
    _name             = name;
    _playbackRate     = playbackRate;
    _playbackChannels = playbackChannels;
    _captureRate      = captureRate;
    _captureChannels  = captureChannels;
    api().registerCustomDevice(this);
}

CustomDevice::~CustomDevice()
{
    try {
        api().unregisterCustomDevice(this);
    } catch (...) {
        // Library might be already be disposed
    }
}

/*!
* Retrieve playback data from the Library
* \a buffer Buffer containing the playback data retrieved from the Library.
* \a samples The number of samples to acquire
* Returns \c true if playback data is available; otherwise, false.
*/
bool CustomDevice::acquireData(QVector<short>& buffer)
{
    return api().acquireCustomPlaybackData(_id, buffer);
}

/*!
* Send the samples from your device to the Library
* \a buffer sample buffer containing the data to be send
* \a samples The number of samples to send
*/
bool CustomDevice::processData(QVector<short>& buffer)
{
    return api().processCustomCaptureData(_id, buffer);
}

} // namespace TeamSpeakSdk

