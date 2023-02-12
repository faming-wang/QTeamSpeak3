#include "library.h"

#include "exception.h"

#include "private/utils_p.h"
#include "private/library_p.h"

namespace QTeamSpeak {

Q_GLOBAL_STATIC(LibraryPrivate, libraryInstance);

Library* Library::instance()
{
    static Library m_instance;
    return &m_instance;
}

Library::~Library()
{

}

/*!
* true if the TeamSpeak library has been loaded and initialized; otherwise, false
*/
bool Library::isInitialized()
{  
    auto d = libraryInstance();
    return d->handle != nullptr; 
}

/*!
* Creates a new \sa instance()
* \a options Information used to create the instance
*/
bool Library::initialize(const LibraryOption& options, QString* error)
{
    auto d = libraryInstance();

    if (d->handle != nullptr) {
        Utils::make_value(error, tr("Library is already initialized"));
        return false;
    }

    auto temp_handle = std::make_unique<QLibrary>(options.libraryFilePath);
    if (!temp_handle->load()) {
        Utils::make_value(error, tr("Library File: %1 load faild.").arg(options.libraryFilePath));
        return false;
    }

    d->nativeBinary    = options.libraryFilePath;
    d->usedLogTypes    = options.usedLogTypes;
    d->logFileFolder   = options.logFileFolder;
    d->resourcesFolder = options.resourcesFolder.isEmpty() ? QFileInfo(d->nativeBinary).absolutePath() : options.resourcesFolder;
    if (!d->resourcesFolder.endsWith(QDir::separator())) {
        d->resourcesFolder += QDir::separator();
        d->resourcesFolder = QDir::toNativeSeparators(d->resourcesFolder);
    }
    try {
        api()->setLibrary(temp_handle.get());
        api()->initClientLib(d->usedLogTypes, d->logFileFolder, d->resourcesFolder);
    } catch (const Exception& e) {
        Utils::make_value(error, tr("Initialize faild. error %1").arg(e.message()));
        return false;
    }

    d->handle.reset(temp_handle.release());

    return true;
}

/*!
* Releases the unmanaged resources used by the \sa Library
*/
void Library::destroy()
{
    auto d = libraryInstance();
    qDeleteAll(d->customdevices);
    qDeleteAll(d->servers);
    if (d->handle) {
        d->releaseHandle();
    }
    d->handle.reset();
}

/*!
* Location to the TeamSpeak library binary.
*/
QString Library::nativeBinary()
{
    auto d = libraryInstance();
    return d->nativeBinary;
}

/*!
* The library can output log messages \sa log() to a file 
* (located in the logs directory relative to the client executable),
* to stdout or to user defined Handlerbacks.
*/
LogTypes Library::usedLogTypes()
{
    auto d = libraryInstance();
    return d->usedLogTypes;
}

/*!
* Defines the location where the logs are written to. Pass null for the default behavior, which is to use a folder Handlered logs in the current working directory.
*/
QString Library::logFileFolder()
{
    auto d = libraryInstance();
    return d->logFileFolder;
}

/*!
* Path pointing to the directory where the soundbackends folder is located.
*/
QString Library::resourcesFolder()
{
    auto d = libraryInstance();
    return d->resourcesFolder;
}

/*!
* Used to hash the password in the same way it is hashed in the outside data store. 
* Or just return the password to send the clear text to the server.
*/
void Library::setClientPasswordEncryptHandler(const ClientPasswordEncryptHandler& handler)
{
    auto d = libraryInstance();
    d->clientPasswordEncryptHandler = handler;
}

ClientPasswordEncryptHandler Library::clientPasswordEncryptHandler()
{
    auto d = libraryInstance();
    return d->clientPasswordEncryptHandler;
}

/*!
* Encrypts outgoing data
*/
void Library::setCustomPacketEncryptHandler(const CustomPacketEncryptHandler& handler)
{
    auto d = libraryInstance();
    d->customPacketEncryptHandler = handler;
}

CustomPacketEncryptHandler Library::customPacketEncryptHandler()
{
    auto d = libraryInstance();
    return d->customPacketEncryptHandler;
}

/*!
* Decrypts incoming data
*/

void Library::setCustomPacketDecryptHandler(const CustomPacketDecryptHandler& handler)
{
    auto d = libraryInstance();
    d->customPacketDecryptHandler = handler;
}

CustomPacketDecryptHandler Library::customPacketDecryptHandler()
{
    auto d = libraryInstance();
    return d->customPacketDecryptHandler;
}

EditPlaybackVoiceDataHandler Library::editPlaybackVoiceDataHandler()
{
    auto d = libraryInstance();
    return d->editPlaybackVoiceDataHandler;
}

void Library::setEditPlaybackVoiceDataHandler(const EditPlaybackVoiceDataHandler& handler)
{
    auto d = libraryInstance();
    d->editPlaybackVoiceDataHandler = handler;
}

EditPostProcessVoiceDataHandler Library::editPostProcessVoiceDataHandler()
{
    auto d = libraryInstance();
    return d->editPostProcessVoiceDataHandler;
}

void Library::setEditPostProcessVoiceDataHandler(const EditPostProcessVoiceDataHandler& handler)
{
    auto d = libraryInstance();
    d->editPostProcessVoiceDataHandler = handler;
}

EditMixedPlaybackVoiceDataHandler Library::editMixedPlaybackVoiceDataHandler()
{
    auto d = libraryInstance();
    return d->editMixedPlaybackVoiceDataHandler;
}

void Library::setEditMixedPlaybackVoiceDataHandler(const EditMixedPlaybackVoiceDataHandler& handler)
{
    auto d = libraryInstance();
    d->editMixedPlaybackVoiceDataHandler = handler;
}

EditCapturedVoiceDataHandler Library::editCapturedVoiceDataHandler()
{
    auto d = libraryInstance();
    return d->editCapturedVoiceDataHandler;
}

void Library::setEditCapturedVoiceDataHandler(const EditCapturedVoiceDataHandler& handler)
{
    auto d = libraryInstance();
    d->editCapturedVoiceDataHandler = handler;
}

Custom3dRolloffCalculationClientHandler Library::custom3dRolloffCalculationClientHandler()
{
    auto d = libraryInstance();
    return d->custom3dRolloffCalculationClientHandler;
}

void Library::setCustom3dRolloffCalculationClientHandler(const Custom3dRolloffCalculationClientHandler& handler)
{
    auto d = libraryInstance();
    d->custom3dRolloffCalculationClientHandler = handler;
}

Custom3dRolloffCalculationWaveHandler Library::custom3dRolloffCalculationWaveHandler()
{
    auto d = libraryInstance();
    return d->custom3dRolloffCalculationWaveHandler;
}

void Library::setCustom3dRolloffCalculationWaveHandler(const Custom3dRolloffCalculationWaveHandler& handler)
{
    auto d = libraryInstance();
    d->custom3dRolloffCalculationWaveHandler = handler;
}

CheckUniqueIdentifierHandler Library::checkUniqueIdentifierHandler()
{
    auto d = libraryInstance();
    return d->checkUniqueIdentifierHandler;
}

void Library::setCheckUniqueIdentifierHandler(const CheckUniqueIdentifierHandler& handler)
{
    auto d = libraryInstance();
    d->checkUniqueIdentifierHandler = handler;
}

/*!
* List of all currently existing server connections
*/
QList<Connection*> Library::connections()
{
    return api()->getServerConnectionHandlerList();
}

/*!
* Query all available playback modes
* Returns \c a readonly collection of playback modes.
* \sa getCaptureModes()
* \sa getPlaybackDevices()
*/
QStringList Library::getPlaybackModes()
{
    return api()->getPlaybackModeList();
}

/*!
* Query all available capture modes
* Returns \c a readonly collection of capture modes.
* \sa getPlaybackModes()
* \sa getCaptureDevices()
*/
QStringList Library::getCaptureModes()
{
    return api()->getCaptureModeList();
}

/*!
* Get playback devices available for the given mode, as well as the current operating systems default.
* \a "mode" The playback mode to use. For different modes there might be different devices. 
* Valid modes are returned by \sa getPlaybackModes.
* Returns \c a readonly collection of sound devices.
* The returned devices values can be used to initialize the devices using \sa Connection::openPlayback().
* A list of available modes is returned by \sa getPlaybackModes()
* \sa getPlaybackModes() 
* \sa getCaptureDevices()
*/
QList<ISoundDevice*> Library::getPlaybackDevices(const QString& mode)
{
    return api()->getPlaybackDeviceList(mode);
}

/*!
* Get capture devices available for the given mode, as well as the current operating systems default.
* \a "mode" The capture mode to use. For different modes there might be different devices. 
* Valid modes are returned by \sa getCaptureModes().
* Returns \c a readonly collection of sound devices
* The returned devices values can be used to initialize the devices using \sa Connection::openCapture().
* A list of available modes is returned by \sa getCaptureModes()
* \sa getCaptureModes()
* \sa getPlaybackDevices()
*/
QList<ISoundDevice*> Library::getCaptureDevices(const QString& mode)
{
    return api()->getCaptureDeviceList(mode);
}

/*!
* List of all currently existing custom devices
*/
QList<CustomDevice*> Library::getCustomDevices()
{
    auto d = libraryInstance();
    return d->customdevices;
}

Connection* Library::getServer(Connection::ID id)
{
    auto d = libraryInstance();
    return d->servers.contains(id) ? d->servers[id] : nullptr;
}

void Library::addServer(Connection* connection)
{
    auto d = libraryInstance();
    removeServer(connection->id());
    d->servers.insert(connection->id(), connection);
}

void Library::removeServer(Connection::ID id)
{
    auto d = libraryInstance();
    if (d->servers.contains(id))
        delete d->servers[id];
}

/*!
* To get the upload speed limit for all virtual servers in bytes/s
*/
quint64 Library::speedLimitUp()
{
    return api()->getInstanceSpeedLimitUp();
}

void Library::setSpeedLimitUp(quint64 value)
{
    api()->setInstanceSpeedLimitUp(value);
}

/*!
* To get the download speed limit for all virtual servers in bytes/s
*/
quint64 Library::speedLimitDown()
{
    return api()->getInstanceSpeedLimitDown();

}

void Library::setSpeedLimitDown(quint64 value)
{
    api()->setInstanceSpeedLimitDown(value);
}

/*!
* The complete Client Lib version string can be queried with
*/
QString Library::version()
{
    return api()->getClientLibVersion();
}

/*!
* Version number, a part of the complete version string
*/
Library::Version Library::versionNumber()
{
    return api()->getClientLibVersionNumber();
}

/*!
* To connect to a server, a client application is required to request an identity from the Library.
* This string should be requested only once and then loHandlery stored in the applications configuration.
* The next time the application connects to a server, the identity should be read from the configuration and reused again.
* Returns \c a identity string
*/
QString Library::createIdentity()
{
    return api()->createIdentity();
}

/*!
* Generate the unique identifier of a identity
* \a identity a identity string, that was created by \sa createIdentity()
* Returns \c the unique identifier of the identity
*/
QString Library::identityToUniqueIdentifier(const QString& identity)
{
    return api()->identityStringToUniqueIdentifier(identity);
}

/*!
* Before connecting to a TeamSpeak 3 server, a new \sa Connection needs to be spawned. 
* With a \sa Connection a connection can be established and dropped multiple times, 
* so for simply reconnecting to the same or another server no new <see cref="Connection" needs to be spawned but existing ones can be reused. However, for using multiple connections simultaneously a new <see cref="Connection" has to be spawned for each connection.
* \a "port" Port the client should bind on. Default is 0 to let the operating system chose any free port.
* Returns \c a new \sa Connection.
*/
Connection* Library::spawnNewConnection(int port)
{
    return new Connection(api()->spawnNewServerConnectionHandler(port));
}

/*!
* Instead of opening existing sound devices that TeamSpeak has detected, you can also use our custom capture and playback mechanism to allow you to override the way in which TeamSpeak does capture and playback. 
* When you have opened a custom capture and playback device you must regularly supply new "captured" sound data via \sa CustomDevice::processData() and retrieve data that should be "played back" via \sa CustomDevice::acquireData(). 
* Where exactly this captured sound data comes from and where the playback data goes to is up to you, which allows a lot of cool things to be done with this mechanism.
* A custom device can be opened like any standard device with \sa Connection::openCapture() and \sa Connection::openPlayback().
* \a "name" Displayed name of the custom device. Freely choose a name which identifies your device.
* \a "captureRate" Frequency of the capture device.
* \a "captureChannels" Number of channels of the capture device. This value depends on if the used codec is a mono or stereo codec.
* \a "playbackRate" Frequency of the playback device.
* \a "playbackChannels" Number of channels of the playback device.
* Implementing own custom devices is for special use cases and entirely optional.
* Returns \c a new CustomDevice
*/
CustomDevice* Library::createCustomDevice(const QString& name, SamplingRate captureRate, int captureChannels, SamplingRate playbackRate, int playbackChannels)
{
    return new CustomDevice(name, captureRate, captureChannels, playbackRate, playbackChannels);
}

/*!
* Basic logging function.
* \a "severity" The level of the message.
* \a "message" Text written to log.
* \a "connection" Identify the current server connection when using multiple connections. Pass null if unused.
* \a "channel" Custom text to categorize the message channel (i.e. "Client", "Sound").
* Log messages can be printed to stdout, 
* logged to a file logs/ts3clientd->[date]d->d->[time].log and sent to user-defined Handlerbacks. 
* The log output behavior is defined when initializing the client library using <see cref="".
* Unless user-defined logging is used, program execution will halt on a log message with severity <see cref="LogLevel.Critical"
*/
void Library::log(const QString& message, LogLevel severity, const QString& channel, const Connection* connection)
{
    api()->logMessage(message, severity, channel, connection);
}

/*!
* The minimum severity of log messages that are passed to \sa userLogMessage()
*/
LogLevel Library::logLevel()
{
    auto d = libraryInstance();
    return d->logLevel;
}

void Library::setLogLevel(LogLevel value)
{
    auto d = libraryInstance();
    api()->setLogVerbosity(value);
    d->logLevel = value;
}

/*!
* Gets a descriptive text message for a error-code
* \a error the error-code
* Returns \c a descriptive text message
*/
QString Library::getErrorMessage(ReturnCode error)
{
    return api()->getErrorMessage(error);
}

void Library::soundDeviceListChangedEvent(SoundDeviceListChangedEvent* event)
{

}

void Library::userLoggingMessageEvent(UserLoggingMessageEvent* event)
{

}

} // namespace QTeamSpeak
