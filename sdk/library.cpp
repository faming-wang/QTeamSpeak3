#include "library.h"

#include "exception.h"
#include "connection.h"
#include "sounddevice.h"
#include "teamspeakevents.h"

#include "private/cachemanager_p.h"
#include "private/eventmanager_p.h"
#include "private/interfacemanager_p.h"


namespace TeamSpeakSdk {

struct LibraryPrivate
{
    LogTypes usedLogTypes;
    LogLevel logLevel;
    QString nativeBinary;
    QString logFileFolder;
    QString resourcesFolder;

    QList<CustomDevice*> customdevices;
    QHash<Connection::ID, Connection*> servers;

    QLibrary* handle = Q_NULLPTR;

    CustomPacketEncryptHandler   customPacketEncryptHandler;
    CustomPacketDecryptHandler   customPacketDecryptHandler;
    ClientPasswordEncryptHandler clientPasswordEncryptHandler;
    EditPlaybackVoiceDataHandler            editPlaybackVoiceDataHandler;
    EditPostProcessVoiceDataHandler         editPostProcessVoiceDataHandler;
    EditMixedPlaybackVoiceDataHandler       editMixedPlaybackVoiceDataHandler;
    EditCapturedVoiceDataHandler            editCapturedVoiceDataHandler;
    Custom3dRolloffCalculationClientHandler custom3dRolloffCalculationClientHandler;
    Custom3dRolloffCalculationWaveHandler   custom3dRolloffCalculationWaveHandler;
    CheckUniqueIdentifierHandler            checkUniqueIdentifierHandler;

    inline bool releaseHandle()
    {
        bool result = true;
        try {
            api().destroyClientLib();
        } catch (...) {
            result = false;
        }
        try {
            handle->unload();
        } catch (...) {
            result = false;
        }
        return result;
    }
};

static Library* m_instance = Q_NULLPTR;
static LibraryPrivate*   d = Q_NULLPTR;

Library* Library::instance()
{
    return m_instance;
}

/*!
* \class Library
*/
Library::Library(QObject* parent)
    : QObject(parent)
{
    d = new LibraryPrivate;
    m_instance = this;
}

Library::~Library()
{
    destroy();
    m_instance = Q_NULLPTR;
    delete d;d = Q_NULLPTR;
}

/*!
* true if the TeamSpeak library has been loaded and initialized; otherwise, false
*/
bool Library::isInitialized()
{  
    return d->handle != Q_NULLPTR; 
}

/*!
* Creates a new \sa instance()
* \a options Information used to create the instance
*/
bool Library::initialize(const LibraryOption& options, QString* error)
{
    if (d->handle != Q_NULLPTR) {
        utils::make_value(error, tr("Library is already initialized"));
        return false;
    }

    auto temp_handle = std::make_unique<QLibrary>(options.libraryFilePath, m_instance);
    if (!temp_handle->load()) {
        utils::make_value(error, tr("Library File: %1 load faild.").arg(options.libraryFilePath));
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
        api().setLibrary(temp_handle.get());
        api().initClientLib(d->usedLogTypes, d->logFileFolder, d->resourcesFolder);
    } catch (const Exception& e) {
        utils::make_value(error, tr("Initialize faild. error %1").arg(e.message()));
        return false;
    }

    d->handle = temp_handle.release();
    return true;
}

/*!
* Releases the unmanaged resources used by the \sa Library
*/
void Library::destroy()
{
    qDeleteAll(d->customdevices);
    qDeleteAll(d->servers);
    if (d->handle) {
        d->releaseHandle();
    }
    delete d->handle;
    d->handle = Q_NULLPTR;
}

/*!
* Location to the TeamSpeak library binary.
*/
QString Library::nativeBinary()
{
    return d->nativeBinary;
}

/*!
* The library can output log messages \sa log() to a file 
* (located in the logs directory relative to the client executable),
* to stdout or to user defined Handlerbacks.
*/
LogTypes Library::usedLogTypes()
{
    return d->usedLogTypes;
}

/*!
* Defines the location where the logs are written to. Pass null for the default behavior, which is to use a folder Handlered logs in the current working directory.
*/
QString Library::logFileFolder()
{
    return d->logFileFolder;
}

/*!
* Path pointing to the directory where the soundbackends folder is located.
*/
QString Library::resourcesFolder()
{
    return d->resourcesFolder;
}

/*!
* Used to hash the password in the same way it is hashed in the outside data store. 
* Or just return the password to send the clear text to the server.
*/
void Library::setClientPasswordEncryptHandler(const ClientPasswordEncryptHandler& handler)
{
    d->clientPasswordEncryptHandler = handler;
}

ClientPasswordEncryptHandler Library::clientPasswordEncryptHandler()
{
    return d->clientPasswordEncryptHandler;
}

/*!
* Encrypts outgoing data
*/
void Library::setCustomPacketEncryptHandler(const CustomPacketEncryptHandler& handler)
{
    d->customPacketEncryptHandler = handler;
}

CustomPacketEncryptHandler Library::customPacketEncryptHandler()
{
    return d->customPacketEncryptHandler;
}

/*!
* Decrypts incoming data
*/

void Library::setCustomPacketDecryptHandler(const CustomPacketDecryptHandler& handler)
{
    d->customPacketDecryptHandler = handler;
}

CustomPacketDecryptHandler Library::customPacketDecryptHandler()
{
    return d->customPacketDecryptHandler;
}

EditPlaybackVoiceDataHandler Library::editPlaybackVoiceDataHandler()
{
    return d->editPlaybackVoiceDataHandler;
}

void Library::setEditPlaybackVoiceDataHandler(const EditPlaybackVoiceDataHandler& handler)
{
    d->editPlaybackVoiceDataHandler = handler;
}

EditPostProcessVoiceDataHandler Library::editPostProcessVoiceDataHandler()
{
    return d->editPostProcessVoiceDataHandler;
}

void Library::setEditPostProcessVoiceDataHandler(const EditPostProcessVoiceDataHandler& handler)
{
    d->editPostProcessVoiceDataHandler = handler;
}

EditMixedPlaybackVoiceDataHandler Library::editMixedPlaybackVoiceDataHandler()
{
    return d->editMixedPlaybackVoiceDataHandler;
}

void Library::setEditMixedPlaybackVoiceDataHandler(const EditMixedPlaybackVoiceDataHandler& handler)
{
    d->editMixedPlaybackVoiceDataHandler = handler;
}

EditCapturedVoiceDataHandler Library::editCapturedVoiceDataHandler()
{
    return d->editCapturedVoiceDataHandler;
}
void Library::setEditCapturedVoiceDataHandler(const EditCapturedVoiceDataHandler& handler)
{
    d->editCapturedVoiceDataHandler = handler;
}

Custom3dRolloffCalculationClientHandler Library::custom3dRolloffCalculationClientHandler()
{
    return d->custom3dRolloffCalculationClientHandler;
}

void Library::setCustom3dRolloffCalculationClientHandler(const Custom3dRolloffCalculationClientHandler& handler)
{
    d->custom3dRolloffCalculationClientHandler = handler;
}

Custom3dRolloffCalculationWaveHandler Library::custom3dRolloffCalculationWaveHandler()
{
    return d->custom3dRolloffCalculationWaveHandler;
}

void Library::setCustom3dRolloffCalculationWaveHandler(const Custom3dRolloffCalculationWaveHandler& handler)
{
    d->custom3dRolloffCalculationWaveHandler = handler;
}

CheckUniqueIdentifierHandler Library::checkUniqueIdentifierHandler()
{
    return d->checkUniqueIdentifierHandler;
}
void Library::setCheckUniqueIdentifierHandler(const CheckUniqueIdentifierHandler& handler)
{
    d->checkUniqueIdentifierHandler = handler;
}

/*!
* List of all currently existing server connections
*/
QList<Connection*> Library::connections()
{
    return api().getServerConnectionHandlerList();
}

/*!
* Query all available playback modes
* Returns \c a readonly collection of playback modes.
* \sa getCaptureModes()
* \sa getPlaybackDevices()
*/
QStringList Library::getPlaybackModes()
{
    return api().getPlaybackModeList();
}

/*!
* Query all available capture modes
* Returns \c a readonly collection of capture modes.
* \sa getPlaybackModes()
* \sa getCaptureDevices()
*/
QStringList Library::getCaptureModes()
{
    return api().getCaptureModeList();
}

/*!
* Get playback devices available for the given mode, as well as the current operating systems default.
* \a "mode">The playback mode to use. For different modes there might be different devices. 
* Valid modes are returned by \sa getPlaybackModes.
* Returns \c a readonly collection of sound devices.
* The returned devices values can be used to initialize the devices using \sa Connection::openPlayback().
* A list of available modes is returned by \sa getPlaybackModes()
* \sa getPlaybackModes() 
* \sa getCaptureDevices()
*/
QList<ISoundDevice*> Library::getPlaybackDevices(const QString& mode)
{
    return api().getPlaybackDeviceList(mode);
}

/*!
* Get capture devices available for the given mode, as well as the current operating systems default.
* \a "mode">The capture mode to use. For different modes there might be different devices. 
* Valid modes are returned by \sa getCaptureModes().
* Returns \c a readonly collection of sound devices
* The returned devices values can be used to initialize the devices using \sa Connection::openCapture().
* A list of available modes is returned by \sa getCaptureModes()
* \sa getCaptureModes()
* \sa getPlaybackDevices()
*/
QList<ISoundDevice*> Library::getCaptureDevices(const QString& mode)
{
    return api().getCaptureDeviceList(mode);
}

/*!
* List of all currently existing custom devices
*/
QList<CustomDevice*> Library::getCustomDevices()
{
    return d->customdevices;
}

Connection* Library::getServer(Connection::ID id)
{
    return d->servers.contains(id) ? d->servers[id] : nullptr;
}

void Library::addServer(Connection* connection)
{
    removeServer(connection->id());
    d->servers.insert(connection->id(), connection);
}

void Library::removeServer(Connection::ID id)
{
    if (d->servers.contains(id))
        delete d->servers[id];
}

/*!
* To get the upload speed limit for all virtual servers in bytes/s
*/
uint64 Library::speedLimitUp()
{
    return api().getInstanceSpeedLimitUp();
}

void Library::setSpeedLimitUp(uint64 value)
{
    api().setInstanceSpeedLimitUp(value);
}

/*!
* To get the download speed limit for all virtual servers in bytes/s
*/
uint64 Library::speedLimitDown()
{
    return api().getInstanceSpeedLimitDown();

}

void Library::setSpeedLimitDown(uint64 value)
{
    api().setInstanceSpeedLimitDown(value);
}

/*!
* The complete Client Lib version string can be queried with
*/
QString Library::version()
{
    return api().getClientLibVersion();
}

/*!
* Version number, a part of the complete version string
*/
Library::Version Library::versionNumber()
{
    return api().getClientLibVersionNumber();
}

/*!
* To connect to a server, a client application is required to request an identity from the Library.
* This string should be requested only once and then loHandlery stored in the applications configuration.
* The next time the application connects to a server, the identity should be read from the configuration and reused again.
* Returns \c a identity string
*/
QString Library::createIdentity()
{
    return api().createIdentity();
}

/*!
* Generate the unique identifier of a identity
* \a identity a identity string, that was created by \sa createIdentity()
* Returns \c the unique identifier of the identity
*/
QString Library::identityToUniqueIdentifier(const QString& identity)
{
    return api().identityStringToUniqueIdentifier(identity);
}

/*!
* Before connecting to a TeamSpeak 3 server, a new \sa Connection needs to be spawned. 
* With a \sa Connection a connection can be established and dropped multiple times, 
* so for simply reconnecting to the same or another server no new <see cref="Connection" needs to be spawned but existing ones can be reused. However, for using multiple connections simultaneously a new <see cref="Connection" has to be spawned for each connection.
* \a "port">Port the client should bind on. Default is 0 to let the operating system chose any free port.
* Returns \c a new \sa Connection.
*/
Connection* Library::spawnNewConnection(int port)
{
    return new Connection(api().spawnNewServerConnectionHandler(port));
}

/*!
* Instead of opening existing sound devices that TeamSpeak has detected, you can also use our custom capture and playback mechanism to allow you to override the way in which TeamSpeak does capture and playback. 
* When you have opened a custom capture and playback device you must regularly supply new "captured" sound data via \sa CustomDevice::processData() and retrieve data that should be "played back" via \sa CustomDevice::acquireData(). 
* Where exactly this captured sound data comes from and where the playback data goes to is up to you, which allows a lot of cool things to be done with this mechanism.
* A custom device can be opened like any standard device with \sa Connection::openCapture() and \sa Connection::openPlayback().
* \a "name">Displayed name of the custom device. Freely choose a name which identifies your device.
* \a "captureRate">Frequency of the capture device.
* \a "captureChannels">Number of channels of the capture device. This value depends on if the used codec is a mono or stereo codec.
* \a "playbackRate">Frequency of the playback device.
* \a "playbackChannels">Number of channels of the playback device.
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
    api().logMessage(message, severity, channel, connection);
}

/*!
* The minimum severity of log messages that are passed to \sa userLogMessage()
*/
LogLevel Library::logLevel()
{
    return d->logLevel;
}

void Library::setLogLevel(LogLevel value)
{
    api().setLogVerbosity(value);
    d->logLevel = value;
}

/*!
* Gets a descriptive text message for a error-code
* \a error the error-code
* Returns \c a descriptive text message
*/
QString Library::getErrorMessage(ReturnCode error)
{
    return api().getErrorMessage(error);
}

bool Library::event(QEvent* e)
{
    switch (e->type()) {
    case SoundDeviceListChangedEvent::EventId:
        if (auto event = dynamic_cast<SoundDeviceListChangedEvent*>(e)){
            soundDeviceListChangedEvent(event);
            return true;
        }
    case UserLoggingMessageEvent::EventId:
        if (auto event = dynamic_cast<UserLoggingMessageEvent*>(e)) {
            userLoggingMessageEvent(event);
            return true;
        }
    default:
        break;
    }
    return QObject::event(e);
}

void Library::soundDeviceListChangedEvent(SoundDeviceListChangedEvent* event)
{
    Q_UNUSED(event);
}

void Library::userLoggingMessageEvent(UserLoggingMessageEvent* event)
{
    Q_UNUSED(event);
}

void __init_library()
{
  (void) new Library(qApp);
}
Q_COREAPP_STARTUP_FUNCTION(__init_library)

} // namespace TeamSpeakSdk

#include "moc_library.cpp"
